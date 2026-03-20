// ============================================================
// APEX-1 — mac_cell.sv
// Single MAC cell. Supports INT8, INT4 (dual-packed), BF16, FP8.
// OPT-5: INT4 dual-packing — two INT4 MACs share one cell,
//        doubling effective INT4 throughput vs INT8.
// OPT-1: bf16_mul has PIPELINE_STAGES=1 for 2 GHz timing.
// ============================================================
import apex1_pkg::*;

module mac_cell #(
  parameter int ACC_W          = 32,  // Accumulator width (FP32)
  parameter int BF16_PIPE_STGS = 1    // OPT-1: pipeline stages in bf16_mul
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

  // Intermediate wires replacing automatic locals
  wire signed [7:0]  mac_a8 = signed'(act_reg[7:0]);
  wire signed [7:0]  mac_w8 = signed'(wgt_reg[7:0]);
  wire signed [15:0] mac_p8 = mac_a8 * mac_w8;
  wire signed [3:0]  mac_a4 = signed'(act_reg[3:0]);
  wire signed [3:0]  mac_w4 = signed'(wgt_reg[3:0]);
  wire signed [7:0]  mac_p4 = mac_a4 * mac_w4;

  // OPT-5: INT4 dual-packed multiply
  // Upper and lower nibbles of each 16-bit word hold two separate INT4 values.
  // Both pairs multiply and accumulate simultaneously — 2× throughput vs INT8.
  wire signed [3:0]  mac_a4_lo = signed'(act_reg[3:0]);
  wire signed [3:0]  mac_w4_lo = signed'(wgt_reg[3:0]);
  wire signed [3:0]  mac_a4_hi = signed'(act_reg[7:4]);
  wire signed [3:0]  mac_w4_hi = signed'(wgt_reg[7:4]);
  wire signed [7:0]  mac_p4_lo = mac_a4_lo * mac_w4_lo;
  wire signed [7:0]  mac_p4_hi = mac_a4_hi * mac_w4_hi;
  // Sign-extend both 8-bit products to 9 bits before adding to avoid overflow
  wire signed [8:0]  mac_p4_sum = signed'(9'(mac_p4_lo)) + signed'(9'(mac_p4_hi));

  always_comb begin
    unique case (dtype)
      DTYPE_INT8:   product = ACC_W'(signed'(mac_p8));
      // OPT-5: dual INT4 — sum of two packed 4-bit MACs per cell per cycle
      DTYPE_INT4:   product = ACC_W'(signed'(mac_p4_sum));
      DTYPE_BF16:   product = bf16_product;
      DTYPE_FP8_E4M3,
      DTYPE_FP8_E5M2: product = fp8_product;
      default:      product = '0;
    endcase
  end

  // OPT-1: bf16_mul with pipeline stage for 2 GHz
  logic [ACC_W-1:0] bf16_product;
  bf16_mul #(.PIPELINE_STAGES(BF16_PIPE_STGS)) u_bf16_mul (
    .clk   (clk),
    .rst_n (rst_n),
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
