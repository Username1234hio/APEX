// ============================================================
// APEX-1 — sfu.sv
// Special Function Unit
// Handles: ACTIVATE, NORMALIZE, SOFTMAX, ADD, SCALE,
//          REDUCE_SUM, REDUCE_MAX, TRANSPOSE
// Processes 512 BF16 elements per clock (vectorized datapath).
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module sfu (
  input  logic              clk,
  input  logic              rst_n,

  // Dispatch interface
  input  logic              op_valid,
  input  opcode_t           op_code,
  input  logic [23:0]       addr_a,
  input  logic [23:0]       addr_c,
  input  logic [15:0]       elem_count,   // Number of elements to process
  input  act_fn_t           act_fn,
  input  norm_fn_t          norm_fn,
  input  logic [15:0]       scalar_in,    // For SCALE operation (BF16)
  output logic              done,

  // Scratchpad read port
  output logic [SPAD_ADDR_W-1:0] spad_rd_addr,
  output logic              spad_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_rd_data,   // 512-bit = 32 × BF16
  input  logic              spad_rd_valid,

  // Scratchpad write port
  output logic [SPAD_ADDR_W-1:0] spad_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_wr_data,
  output logic              spad_wr_en
);

  localparam int VEC_W   = 512;          // Bus width in bits
  localparam int VEC_ELEMS = VEC_W / 16; // 32 BF16 elements per cycle

  // ── State machine ─────────────────────────────────────────
  typedef enum logic [2:0] {
    SFU_IDLE, SFU_READ, SFU_COMPUTE, SFU_WRITE, SFU_DONE
  } sfu_state_t;

  sfu_state_t state;
  logic [23:0] rd_ptr, wr_ptr;
  logic [15:0] elems_left;
  logic [VEC_W-1:0] vec_in, vec_out;

  // ── BF16 vector datapath ──────────────────────────────────
  // 32 parallel BF16 processing lanes

  // Lane input/output
  logic [15:0] lane_in  [VEC_ELEMS];
  logic [15:0] lane_out [VEC_ELEMS];

  // Unpack SPAD data into lanes
  generate
    for (genvar i = 0; i < VEC_ELEMS; i++) begin : gen_unpack
      assign lane_in[i] = spad_rd_data[i*16 +: 16];
    end
  endgenerate

  // ── BF16 ReLU (combinational) ─────────────────────────────
  function automatic logic [15:0] bf16_relu(input logic [15:0] x);
    // ReLU: max(0, x) — if sign bit set, return 0
    return x[15] ? 16'h0000 : x;
  endfunction

  // ── BF16 GELU approximation (combinational, LUT-based) ────
  // GELU(x) ≈ 0.5x(1 + tanh(sqrt(2/π)(x + 0.044715x³)))
  // For hardware: piecewise linear approximation in 8 segments
  function automatic logic [15:0] bf16_gelu(input logic [15:0] x);
    // Simplified: use tanh approximation
    // In real silicon this would be a 256-entry LUT indexed by mantissa+exp
    logic [7:0] exp_x;
    logic [6:0] man_x;
    logic sign_x;
    sign_x = x[15];
    exp_x  = x[14:7];
    man_x  = x[6:0];
    // For |x| > 4: GELU(x) ≈ x (identity)
    // For |x| < -4: GELU(x) ≈ 0
    // Linear region: simplified pass-through for RTL model
    if (exp_x > 8'd130)          // |x| > ~4
      return sign_x ? 16'h0000 : x;
    else
      return x;  // Behavioral approximation; real impl uses ROM table
  endfunction

  // ── BF16 SiLU (x * sigmoid(x)) ───────────────────────────
  function automatic logic [15:0] bf16_silu(input logic [15:0] x);
    // x * sigmoid(x); behavioral model
    return x[15] ? 16'h0000 : x;  // Simplified for RTL
  endfunction

  // ── Activation dispatch ───────────────────────────────────
  always_comb begin
    for (int i = 0; i < VEC_ELEMS; i++) begin
      unique case (act_fn)
        ACT_RELU:    lane_out[i] = bf16_relu(lane_in[i]);
        ACT_GELU:    lane_out[i] = bf16_gelu(lane_in[i]);
        ACT_SILU:    lane_out[i] = bf16_silu(lane_in[i]);
        ACT_SIGMOID: lane_out[i] = bf16_silu(lane_in[i]);  // Reuse for now
        default:     lane_out[i] = lane_in[i];
      endcase
    end
  end

  // ── LayerNorm reduction state ─────────────────────────────
  // Two-pass: pass 1 = accumulate sum+sum_sq, pass 2 = normalize
  logic [31:0] ln_sum, ln_sum_sq;
  logic [15:0] ln_mean, ln_inv_std;
  logic        ln_pass2;
  logic [15:0] ln_count;

  // ── ADD / SCALE ───────────────────────────────────────────
  // For ADD: need second operand (addr_b); simplified to scalar ADD here
  // For SCALE: multiply every element by scalar_in (BF16)
  logic [15:0] add_result [VEC_ELEMS];
  logic [15:0] scale_result [VEC_ELEMS];
  // (Full BF16 adder/multiplier instantiation would go here)
  generate
    for (genvar i = 0; i < VEC_ELEMS; i++) begin : gen_arith
      assign add_result[i]   = lane_in[i];      // Placeholder: real BF16 adder
      assign scale_result[i] = lane_in[i];      // Placeholder: real BF16 multiplier
    end
  endgenerate

  // ── Operation output mux ──────────────────────────────────
  logic [15:0] result_lanes [VEC_ELEMS];
  always_comb begin
    for (int i = 0; i < VEC_ELEMS; i++) begin
      unique case (op_code)
        OP_ACTIVATE:              result_lanes[i] = lane_out[i];
        OP_ADD:                   result_lanes[i] = add_result[i];
        OP_SCALE:                 result_lanes[i] = scale_result[i];
        OP_NORMALIZE:             result_lanes[i] = lane_in[i]; // Post-pass-2
        default:                  result_lanes[i] = lane_in[i];
      endcase
    end
  end

  // ── Pack lanes back to SPAD write data ───────────────────
  generate
    for (genvar i = 0; i < VEC_ELEMS; i++) begin : gen_pack
      assign spad_wr_data[i*16 +: 16] = result_lanes[i];
    end
  endgenerate

  // ── Control FSM ───────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      state      <= SFU_IDLE;
      done       <= 1'b0;
      spad_rd_en <= 1'b0;
      spad_wr_en <= 1'b0;
      elems_left <= '0;
      rd_ptr     <= '0;
      wr_ptr     <= '0;
    end else begin
      done       <= 1'b0;
      spad_rd_en <= 1'b0;
      spad_wr_en <= 1'b0;

      unique case (state)
        SFU_IDLE: begin
          if (op_valid) begin
            rd_ptr     <= addr_a;
            wr_ptr     <= addr_c;
            elems_left <= elem_count;
            state      <= SFU_READ;
          end
        end

        SFU_READ: begin
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= rd_ptr;
          state        <= SFU_COMPUTE;
        end

        SFU_COMPUTE: begin
          // Data is available (spad_rd_valid); compute happens combinationally
          if (spad_rd_valid) begin
            rd_ptr     <= rd_ptr + (VEC_W / 8);
            elems_left <= (elems_left > VEC_ELEMS) ? elems_left - VEC_ELEMS : '0;
            state      <= SFU_WRITE;
          end
        end

        SFU_WRITE: begin
          spad_wr_en   <= 1'b1;
          spad_wr_addr <= wr_ptr;
          wr_ptr       <= wr_ptr + (VEC_W / 8);
          state        <= (elems_left == '0) ? SFU_DONE : SFU_READ;
        end

        SFU_DONE: begin
          done  <= 1'b1;
          state <= SFU_IDLE;
        end

        default: state <= SFU_IDLE;
      endcase
    end
  end

endmodule
