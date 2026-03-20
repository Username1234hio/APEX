// ============================================================
// APEX-1 — norm_unit.sv
// Normalization Unit: LayerNorm, RMSNorm, GroupNorm
//
// LayerNorm: y = (x - mean) / sqrt(var + eps) * gamma + beta
//   Two-pass: pass1 = mean, pass2 = var → normalize
//
// RMSNorm:   y = x / sqrt(mean(x²) + eps) * gamma
//   Single-pass: accumulate x², then normalize
//   (No mean subtraction — computationally cheaper, used in LLaMA)
//
// GroupNorm:  LayerNorm applied per group of channels
//
// All modes use FP32 accumulation for mean/variance stability.
// BF16 input/output. 32 BF16 lanes (512-bit bus).
// ============================================================
import apex1_pkg::*;

module norm_unit (
  input  logic              clk,
  input  logic              rst_n,

  // Dispatch
  input  logic              op_valid,
  input  norm_fn_t          norm_fn,
  input  logic [23:0]       src_addr,     // Input tensor in SPAD
  input  logic [23:0]       gamma_addr,   // Scale (gamma) in SPAD
  input  logic [23:0]       beta_addr,    // Shift (beta) in SPAD (LayerNorm only)
  input  logic [23:0]       dst_addr,     // Output in SPAD
  input  logic [15:0]       num_elements, // Elements in normalization group
  input  logic [15:0]       num_groups,   // Groups (GroupNorm) or rows (LayerNorm)
  output logic              done,

  // Scratchpad
  output logic [SPAD_ADDR_W-1:0] spad_rd_addr,
  output logic              spad_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_rd_data,
  input  logic              spad_rd_valid,

  output logic [SPAD_ADDR_W-1:0] spad_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_wr_data,
  output logic              spad_wr_en
);

  localparam int LANES = 32;              // BF16 lanes per bus beat
  localparam real EPS  = 1.0e-5;         // Epsilon for numerical stability
  localparam logic [31:0] EPS_FP32 = 32'h358637BD; // 1e-5 in FP32

  // ── BF16 → FP32 expansion ────────────────────────────────
  function automatic logic [31:0] to_fp32(input logic [15:0] b);
    return {b, 16'h0000};
  endfunction

  // ── FP32 square (approximate behavioral) ─────────────────
  function automatic logic [31:0] fp32_sq(input logic [31:0] x);
    // x² : double the exponent, square the mantissa
    logic [7:0] exp_x;
    logic [22:0] man_x;
    exp_x = x[30:23];
    man_x = x[22:0];
    return {1'b0, 8'(2*exp_x - 127), man_x};  // Simplified
  endfunction

  // ── FP32 reciprocal square root (rsqrt approx) ───────────
  function automatic logic [31:0] fp32_rsqrt(input logic [31:0] x);
    // Initial approximation using magic number (Quake-style)
    // Real impl: Newton-Raphson iteration in 2 steps
    logic [31:0] half_x = {x[31], x[30:1]};  // x/2
    logic [31:0] approx  = 32'h5F3759DF - {1'b0, x[31:1]};  // Magic constant
    // One Newton step: approx * (1.5 - half_x * approx²)
    return approx;  // Behavioral placeholder
  endfunction

  // ── FSM ───────────────────────────────────────────────────
  typedef enum logic [2:0] {
    NM_IDLE,
    NM_PASS1,        // Accumulate sum (LayerNorm) or sum-of-squares (RMSNorm)
    NM_COMPUTE_STATS,// Compute mean/variance from accumulated sums
    NM_PASS2,        // Normalize and scale
    NM_WRITE,
    NM_DONE
  } nm_state_t;

  nm_state_t state;

  // Accumulators (FP32)
  logic [31:0] acc_sum;      // Sum of x (for mean in LayerNorm)
  logic [31:0] acc_sum_sq;   // Sum of x² (for variance)
  logic [31:0] mean_fp32;
  logic [31:0] inv_std_fp32;

  logic [23:0] rd_ptr, wr_ptr, gamma_ptr, beta_ptr;
  logic [15:0] elem_left;
  logic [15:0] group_cnt;

  // Lane arrays
  logic [15:0] lane_in   [LANES];
  logic [15:0] lane_gamma[LANES];
  logic [15:0] lane_beta [LANES];
  logic [15:0] lane_out  [LANES];
  logic [31:0] xf_tmp;          // temp for fp32 conversion in normalize loop

  always_comb begin
    for (int i = 0; i < LANES; i++)
      lane_in[i] = spad_rd_data[i*16 +: 16];
  end

  // Normalize — behavioral passthrough (replace with full FP32 pipeline for tape-out)
  always_comb begin
    for (int i = 0; i < LANES; i++) begin
      xf_tmp = to_fp32(lane_in[i]);
      lane_out[i] = xf_tmp[31:16];
    end
  end

  // Pack output lanes
  always_comb begin
    for (int i = 0; i < LANES; i++)
      spad_wr_data[i*16 +: 16] = lane_out[i];
  end

  // ── Main FSM ──────────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      state       <= NM_IDLE;
      done        <= 1'b0;
      spad_rd_en  <= 1'b0;
      spad_wr_en  <= 1'b0;
      acc_sum     <= '0;
      acc_sum_sq  <= '0;
      group_cnt   <= '0;
    end else begin
      done       <= 1'b0;
      spad_rd_en <= 1'b0;
      spad_wr_en <= 1'b0;

      unique case (state)
        NM_IDLE: begin
          if (op_valid) begin
            rd_ptr    <= src_addr;
            wr_ptr    <= dst_addr;
            gamma_ptr <= gamma_addr;
            beta_ptr  <= beta_addr;
            elem_left <= num_elements;
            group_cnt <= '0;
            acc_sum   <= '0;
            acc_sum_sq<= '0;
            state     <= NM_PASS1;
          end
        end

        NM_PASS1: begin
          // Read input data and accumulate statistics
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= rd_ptr;
          if (spad_rd_valid) begin
            for (int i = 0; i < LANES; i++) begin
              acc_sum    <= acc_sum + to_fp32(lane_in[i]);
              acc_sum_sq <= acc_sum_sq + fp32_sq(to_fp32(lane_in[i]));
            end
            rd_ptr    <= rd_ptr + (SPAD_DATA_W/8);
            elem_left <= (elem_left > LANES) ? elem_left - LANES : '0;
            if (elem_left <= LANES)
              state <= NM_COMPUTE_STATS;
          end
        end

        NM_COMPUTE_STATS: begin
          mean_fp32    = {acc_sum[31],
                          8'(acc_sum[30:23] - 8'($clog2(num_elements))),
                          acc_sum[22:0]};
          inv_std_fp32 = fp32_rsqrt({acc_sum_sq[31],
                          8'(acc_sum_sq[30:23] - 8'($clog2(num_elements))),
                          acc_sum_sq[22:0]} + EPS_FP32);
          if (norm_fn == NORM_RMS) mean_fp32 = '0;
          rd_ptr    <= src_addr;
          elem_left <= num_elements;
          state     <= NM_PASS2;
        end

        NM_PASS2: begin
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= rd_ptr;
          if (spad_rd_valid) begin
            rd_ptr    <= rd_ptr + (SPAD_DATA_W/8);
            elem_left <= (elem_left > LANES) ? elem_left - LANES : '0;
            // Output normalization happens combinationally (lane_out)
            state     <= NM_WRITE;
          end
        end

        NM_WRITE: begin
          spad_wr_en   <= 1'b1;
          spad_wr_addr <= wr_ptr;
          wr_ptr       <= wr_ptr + (SPAD_DATA_W/8);
          if (elem_left == '0) begin
            group_cnt <= group_cnt + 1;
            if (group_cnt >= num_groups - 1)
              state <= NM_DONE;
            else begin
              // Next group: reset accumulators
              acc_sum    <= '0;
              acc_sum_sq <= '0;
              elem_left  <= num_elements;
              state      <= NM_PASS1;
            end
          end else begin
            state <= NM_PASS2;
          end
        end

        NM_DONE: begin
          done  <= 1'b1;
          state <= NM_IDLE;
        end

        default: state <= NM_IDLE;
      endcase
    end
  end

endmodule
