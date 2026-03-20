// ============================================================
// APEX-1 — bf16_mul.sv
// BF16 × BF16 → FP32 multiplier.
// OPT-1: PIPELINE_STAGES parameter adds register stages to
// cut the critical path and enable 2 GHz on TSMC N3E.
// PIPELINE_STAGES=0: combinational (1 GHz target)
// PIPELINE_STAGES=1: one flop between multiply and normalize
//                    (breaks the mantissa multiply + normalize
//                     + exponent add chain, targets 2 GHz)
// The systolic array drain timing must account for the added
// latency: ROWS + COLS + PIPELINE_STAGES drain cycles.
// ============================================================
module bf16_mul #(
  parameter int PIPELINE_STAGES = 1   // OPT-1: 1 for 2 GHz, 0 for combinational
)(
  input  logic        clk,            // Only used when PIPELINE_STAGES > 0
  input  logic        rst_n,
  input  logic [15:0] a,
  input  logic [15:0] b,
  output logic [31:0] result
);

  // Unpack BF16
  logic        sign_a, sign_b;
  logic [7:0]  exp_a, exp_b;
  logic [6:0]  man_a, man_b;

  assign sign_a = a[15];
  assign exp_a  = a[14:7];
  assign man_a  = a[6:0];

  assign sign_b = b[15];
  assign exp_b  = b[14:7];
  assign man_b  = b[6:0];

  // Result sign
  logic sign_r;
  assign sign_r = sign_a ^ sign_b;

  // Handle special cases: zero, inf, NaN
  logic a_zero, b_zero, a_inf, b_inf, a_nan, b_nan;
  assign a_zero = (exp_a == 8'h00) && (man_a == 7'h00);
  assign b_zero = (exp_b == 8'h00) && (man_b == 7'h00);
  assign a_inf  = (exp_a == 8'hFF) && (man_a == 7'h00);
  assign b_inf  = (exp_b == 8'hFF) && (man_b == 7'h00);
  assign a_nan  = (exp_a == 8'hFF) && (man_a != 7'h00);
  assign b_nan  = (exp_b == 8'hFF) && (man_b != 7'h00);

  // Mantissa with implicit leading 1 (for normal numbers)
  logic [7:0]  mant_a_full, mant_b_full;
  assign mant_a_full = {1'b1, man_a};  // 8 bits
  assign mant_b_full = {1'b1, man_b};

  // Mantissa product: 8×8 = 16 bits
  logic [15:0] mant_product;
  assign mant_product = mant_a_full * mant_b_full;

  // Exponent sum (biased), subtract one bias: (ea-127)+(eb-127)+127 = ea+eb-127
  logic [9:0]  exp_sum;
  assign exp_sum = {2'b00, exp_a} + {2'b00, exp_b} - 10'd127;

  // Normalize: if MSB of product is set, shift right and add 1 to exponent
  logic [22:0] mant_normalized;
  logic [7:0]  exp_normalized;

  always_comb begin
    if (mant_product[15]) begin
      mant_normalized = {mant_product[14:0], 8'b0};  // Already normalized, shift to 23-bit mantissa
      exp_normalized  = exp_sum[7:0] + 8'd1;
    end else begin
      mant_normalized = {mant_product[13:0], 9'b0};
      exp_normalized  = exp_sum[7:0];
    end
  end

  // Assemble FP32 result (combinational)
  logic [31:0] result_comb;
  always_comb begin
    if (a_nan || b_nan)
      result_comb = 32'h7FC00000;
    else if ((a_inf && b_zero) || (b_inf && a_zero))
      result_comb = 32'h7FC00000;
    else if (a_inf || b_inf)
      result_comb = {sign_r, 8'hFF, 23'h0};
    else if (a_zero || b_zero)
      result_comb = {sign_r, 31'h0};
    else if (exp_sum[9] || exp_sum == 0)
      result_comb = {sign_r, 8'hFF, 23'h0};
    else
      result_comb = {sign_r, exp_normalized, mant_normalized};
  end

  // OPT-1: Optional pipeline register to cut critical path for 2 GHz
  generate
    if (PIPELINE_STAGES >= 1) begin : gen_pipe
      always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) result <= '0;
        else        result <= result_comb;
      end
    end else begin : gen_comb
      assign result = result_comb;
    end
  endgenerate

endmodule
