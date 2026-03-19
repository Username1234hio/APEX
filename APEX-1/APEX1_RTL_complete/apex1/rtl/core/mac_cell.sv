// ============================================================
// APEX-1 — mac_cell.sv
// Single multiply-accumulate cell in the systolic array.
// Supports INT8, BF16, FP8 (E4M3/E5M2) modes.
// Data flows: activations rightward, weights downward,
// accumulator stays in-place and drains when drain_en asserted.
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module mac_cell #(
  parameter int ACC_W = 32   // Accumulator width (FP32)
)(
  input  logic              clk,
  input  logic              rst_n,

  // Data format select
  input  dtype_t            dtype,

  // Activation input (flows rightward: west→east)
  input  logic [15:0]       act_in,     // BF16 / INT8 (lower 8 bits used for INT8)
  output logic [15:0]       act_out,    // Pass-through to east neighbor

  // Weight input (flows downward: north→south)
  input  logic [15:0]       wgt_in,
  output logic [15:0]       wgt_out,    // Pass-through to south neighbor

  // Accumulator drain (flows eastward out of array)
  input  logic              drain_en,   // Drain accumulator this cycle
  input  logic [ACC_W-1:0]  drain_in,   // Partial sum from west
  output logic [ACC_W-1:0]  drain_out,  // Partial sum to east / output

  // Power gate (clock enable)
  input  logic              cell_en
);

  // ── Pipeline registers ──────────────────────────────────
  logic [15:0]   act_reg, wgt_reg;
  logic [ACC_W-1:0] acc;

  // ── Stage 1: Register inputs ────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      act_reg <= '0;
      wgt_reg <= '0;
    end else if (cell_en) begin
      act_reg <= act_in;
      wgt_reg <= wgt_in;
      act_out <= act_in;   // Propagate eastward
      wgt_out <= wgt_in;   // Propagate southward
    end
  end

  // ── Stage 2–3: Multiply & Accumulate ───────────────────
  // Combinational multiply with registered accumulate
  logic [ACC_W-1:0] product;

  always_comb begin
    unique case (dtype)
      DTYPE_INT8: begin
        // INT8 × INT8 → 32-bit accumulator
        automatic logic signed [7:0]  a8 = act_reg[7:0];
        automatic logic signed [7:0]  w8 = wgt_reg[7:0];
        automatic logic signed [15:0] p  = a8 * w8;
        product = ACC_W'(signed'(p));
      end
      DTYPE_INT4: begin
        // INT4 × INT4 — lower nibbles
        automatic logic signed [3:0]  a4 = act_reg[3:0];
        automatic logic signed [3:0]  w4 = wgt_reg[3:0];
        automatic logic signed [7:0]  p  = a4 * w4;
        product = ACC_W'(signed'(p));
      end
      DTYPE_BF16: begin
        // BF16: 1 sign + 8 exp + 7 mantissa
        // Multiply by converting to FP32, multiply, store FP32 result
        // Full BF16 FP multiply: handled by bf16_mul submodule output
        product = bf16_product;   // See BF16 multiplier instantiation below
      end
      DTYPE_FP8_E4M3,
      DTYPE_FP8_E5M2: begin
        product = fp8_product;    // See FP8 multiplier instantiation below
      end
      default: product = '0;
    endcase
  end

  // BF16 multiplier (combinational)
  logic [ACC_W-1:0] bf16_product;
  bf16_mul u_bf16_mul (
    .a     (act_reg),
    .b     (wgt_reg),
    .result(bf16_product)
  );

  // FP8 multiplier (combinational)
  logic [ACC_W-1:0] fp8_product;
  fp8_mul u_fp8_mul (
    .a     (act_reg[7:0]),
    .b     (wgt_reg[7:0]),
    .fmt   (dtype == DTYPE_FP8_E4M3 ? 1'b0 : 1'b1),
    .result(fp8_product)
  );

  // ── Accumulator register ────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      acc <= '0;
    end else if (cell_en) begin
      if (drain_en)
        acc <= '0;           // Clear after drain
      else
        acc <= acc + product;
    end
  end

  // ── Drain path ──────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      drain_out <= '0;
    end else if (cell_en) begin
      if (drain_en)
        drain_out <= acc + drain_in;  // Chain partial sums rightward
      else
        drain_out <= drain_in;        // Pass-through when not draining
    end
  end

endmodule
