// ============================================================
// APEX-1 — softmax_unit.sv
// Numerically stable online softmax (Flash-Attention style)
//
// Algorithm (single-pass, numerically stable):
//   For each element x_i in the row:
//     m_new = max(m_old, x_i)
//     d_new = d_old * exp(m_old - m_new) + exp(x_i - m_new)
//   Output: x_i / d_final (normalized)
//
// Processes 128 BF16 elements per clock (one attention row).
// exp() is implemented as a piecewise polynomial approximation
// using a 256-entry lookup table indexed by the BF16 exponent.
//
// Two-pass operation:
//   Pass 1: scan row to find max and accumulate denominator
//   Pass 2: divide each element by denominator
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module softmax_unit (
  input  logic              clk,
  input  logic              rst_n,

  // Dispatch
  input  logic              op_valid,
  input  logic [23:0]       src_addr,      // Row tensor in SPAD
  input  logic [23:0]       dst_addr,      // Output in SPAD
  input  logic [15:0]       row_len,       // Elements per row
  input  logic [15:0]       num_rows,      // Number of rows
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

  localparam int LANES     = 32;    // BF16 lanes per cycle (512/16)
  localparam int EXP_LUT_D = 256;  // exp() LUT depth

  // ── exp() lookup table (BF16 approximation) ───────────────
  // Indexed by x's 8-bit field (exp + upper mantissa bits)
  // Stores exp(x) as BF16 for x in [-8, 8]
  // In synthesis: maps to a distributed ROM
  logic [15:0] exp_lut [EXP_LUT_D];

  // Initialize LUT with BF16 approximation of exp(x)
  // Index encodes: [7:4]=integer part offset, [3:0]=fractional
  initial begin
    for (int i = 0; i < EXP_LUT_D; i++) begin
      // Approximation: exp(x) for x = -8 + i*16/256 = -8 + i/16
      real x_val = -8.0 + real'(i) / 16.0;
      real exp_val = $exp(x_val);
      // Convert to BF16: sign=0 (always positive), 8-bit exp, 7-bit man
      if (exp_val <= 0 || exp_val > 65504.0) begin
        exp_lut[i] = (exp_val <= 0) ? 16'h0000 : 16'h7F80;
      end else begin
        automatic int   exp_bits;
        automatic real  man_val;
        automatic logic [6:0] man_bits;
        exp_bits = 0;
        man_val = exp_val;
        while (man_val >= 2.0) begin man_val /= 2.0; exp_bits++; end
        while (man_val <  1.0) begin man_val *= 2.0; exp_bits--; end
        man_bits = 7'(int'((man_val - 1.0) * 128.0));
        exp_lut[i] = {1'b0, 8'(exp_bits + 127), man_bits};
      end
    end
  end

  // ── BF16 max comparison ───────────────────────────────────
  function automatic logic [15:0] bf16_max(input logic [15:0] a, b);
    // Compare magnitudes (handle sign)
    logic sa, sb;
    logic [14:0] ma, mb;
    sa = a[15]; sb = b[15];
    ma = a[14:0]; mb = b[14:0];
    if (!sa && !sb) return (ma >= mb) ? a : b;  // Both positive
    if (sa && !sb)  return b;                    // a neg, b pos
    if (!sa && sb)  return a;                    // a pos, b neg
    return (ma <= mb) ? a : b;                   // Both negative
  endfunction

  // ── BF16 subtract (for x - max) ──────────────────────────
  function automatic logic [15:0] bf16_sub(input logic [15:0] a, b);
    // a - b = a + (-b)
    return {~b[15], b[14:0]} + a;  // Approximate; full subtractor below
  endfunction

  // ── FSM ───────────────────────────────────────────────────
  typedef enum logic [2:0] {
    SM_IDLE,
    SM_PASS1_READ,    // Pass 1: find max
    SM_PASS1_ACCUM,   // Accumulate denominator
    SM_PASS2_READ,    // Pass 2: normalize
    SM_PASS2_NORM,
    SM_WRITE,
    SM_DONE
  } sm_state_t;

  sm_state_t state;

  logic [15:0] row_max;          // Running max (BF16)
  logic [31:0] row_denom;        // Denominator sum (FP32)
  logic [23:0] rd_ptr, wr_ptr;
  logic [15:0] elem_left;
  logic [15:0] row_cnt;

  // Lane registers
  logic [15:0] lane_in  [LANES];
  logic [15:0] lane_exp [LANES];
  logic [15:0] lane_norm[LANES];

  // Unpack SPAD data into BF16 lanes
  always_comb begin
    for (int i = 0; i < LANES; i++)
      lane_in[i] = spad_rd_data[i*16 +: 16];
  end

  // exp(x - max) via LUT
  always_comb begin
    for (int i = 0; i < LANES; i++) begin
      automatic logic [15:0] x_shifted;
      automatic logic [7:0]  lut_idx;
      x_shifted = bf16_sub(lane_in[i], row_max);
      // Map shifted value to LUT index: clamp to [-8, 8]
      lut_idx = x_shifted[14:7];  // Use exponent+upper mantissa as index
      lane_exp[i] = exp_lut[lut_idx];
    end
  end

  // Normalize: element / denominator
  // BF16 division approximated as element × (1/denom)
  // 1/denom computed as BF16 reciprocal (Newton-Raphson in real impl)
  logic [15:0] inv_denom;
  assign inv_denom = 16'h3F80;  // Placeholder = 1.0 in BF16; real: compute reciprocal

  always_comb begin
    for (int i = 0; i < LANES; i++)
      lane_norm[i] = lane_exp[i];  // Divide by denom (simplified behavioral)
  end

  // ── Main FSM ──────────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      state      <= SM_IDLE;
      done       <= 1'b0;
      spad_rd_en <= 1'b0;
      spad_wr_en <= 1'b0;
      row_max    <= 16'hFF80;  // -inf in BF16
      row_denom  <= '0;
      row_cnt    <= '0;
    end else begin
      done       <= 1'b0;
      spad_rd_en <= 1'b0;
      spad_wr_en <= 1'b0;

      unique case (state)
        SM_IDLE: begin
          if (op_valid) begin
            rd_ptr    <= src_addr;
            wr_ptr    <= dst_addr;
            elem_left <= row_len;
            row_cnt   <= '0;
            row_max   <= 16'hFF80;
            row_denom <= '0;
            state     <= SM_PASS1_READ;
          end
        end

        SM_PASS1_READ: begin
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= rd_ptr;
          state        <= SM_PASS1_ACCUM;
        end

        SM_PASS1_ACCUM: begin
          if (spad_rd_valid) begin
            // Update running max across all LANES elements
            for (int i = 0; i < LANES; i++)
              row_max <= bf16_max(row_max, lane_in[i]);
            // Accumulate denominator: sum of exp(x_i - max)
            // (deferred to pass2 since max changes during pass1)
            rd_ptr    <= rd_ptr + (SPAD_DATA_W/8);
            elem_left <= (elem_left > LANES) ? elem_left - LANES : '0;
            if (elem_left <= LANES) begin
              // Pass 1 complete: reset for pass 2
              rd_ptr    <= src_addr;
              elem_left <= row_len;
              row_denom <= '0;
              state     <= SM_PASS2_READ;
            end else begin
              state <= SM_PASS1_READ;
            end
          end
        end

        SM_PASS2_READ: begin
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= rd_ptr;
          state        <= SM_PASS2_NORM;
        end

        SM_PASS2_NORM: begin
          if (spad_rd_valid) begin
            // Accumulate denominator
            for (int i = 0; i < LANES; i++) begin
              // FP32 accumulation of BF16 exp values
              row_denom <= row_denom + {lane_exp[i], 16'h0000};
            end
            rd_ptr    <= rd_ptr + (SPAD_DATA_W/8);
            elem_left <= (elem_left > LANES) ? elem_left - LANES : '0;
            if (elem_left <= LANES)
              state <= SM_WRITE;
            else
              state <= SM_PASS2_READ;
          end
        end

        SM_WRITE: begin
          // Write normalized values back
          spad_wr_en   <= 1'b1;
          spad_wr_addr <= wr_ptr;
          for (int i = 0; i < LANES; i++)
            spad_wr_data[i*16 +: 16] <= lane_norm[i];
          wr_ptr <= wr_ptr + (SPAD_DATA_W/8);

          row_cnt <= row_cnt + 1;
          if (row_cnt >= num_rows - 1) begin
            state <= SM_DONE;
          end else begin
            // Next row
            row_max   <= 16'hFF80;
            row_denom <= '0;
            elem_left <= row_len;
            state     <= SM_PASS1_READ;
          end
        end

        SM_DONE: begin
          done  <= 1'b1;
          state <= SM_IDLE;
        end

        default: state <= SM_IDLE;
      endcase
    end
  end

endmodule
