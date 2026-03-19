// ============================================================
// APEX-1 — bf16_mul.sv
// BF16 × BF16 → FP32 multiplier (combinational)
// BF16 format: 1 sign, 8 exponent, 7 mantissa (truncated FP32)
// Result is FP32 (32-bit) for accumulation precision.
// ============================================================
module bf16_mul (
  input  logic [15:0] a,       // BF16 operand A
  input  logic [15:0] b,       // BF16 operand B
  output logic [31:0] result   // FP32 product
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

  // Assemble FP32 result with special case handling
  always_comb begin
    if (a_nan || b_nan)
      result = 32'h7FC00000;               // Quiet NaN
    else if ((a_inf && b_zero) || (b_inf && a_zero))
      result = 32'h7FC00000;               // NaN: inf × 0
    else if (a_inf || b_inf)
      result = {sign_r, 8'hFF, 23'h0};     // Inf
    else if (a_zero || b_zero)
      result = {sign_r, 31'h0};            // Zero
    else if (exp_sum[9] || exp_sum == 0)   // Overflow or underflow
      result = {sign_r, 8'hFF, 23'h0};
    else
      result = {sign_r, exp_normalized, mant_normalized};
  end

endmodule
