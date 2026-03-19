// ============================================================
// APEX-1 — fp8_mul.sv
// FP8 × FP8 → FP32 multiplier (combinational)
// Supports E4M3 (fmt=0) and E5M2 (fmt=1) formats.
//   E4M3: 1 sign, 4 exponent, 3 mantissa  (bias=7)
//   E5M2: 1 sign, 5 exponent, 2 mantissa  (bias=15)
// ============================================================
module fp8_mul (
  input  logic [7:0]  a,
  input  logic [7:0]  b,
  input  logic        fmt,     // 0=E4M3, 1=E5M2
  output logic [31:0] result
);

  // Unpack based on format
  logic        sign_a, sign_b;
  logic [4:0]  exp_a, exp_b;
  logic [2:0]  man_a, man_b;
  logic [4:0]  bias;

  always_comb begin
    sign_a = a[7];
    sign_b = b[7];
    if (!fmt) begin
      // E4M3
      exp_a  = {1'b0, a[6:3]};
      exp_b  = {1'b0, b[6:3]};
      man_a  = a[2:0];
      man_b  = b[2:0];
      bias   = 5'd7;
    end else begin
      // E5M2
      exp_a  = a[6:2];
      exp_b  = b[6:2];
      man_a  = {a[1:0], 1'b0};
      man_b  = {b[1:0], 1'b0};
      bias   = 5'd15;
    end
  end

  logic sign_r;
  assign sign_r = sign_a ^ sign_b;

  // Zero detection
  logic a_zero, b_zero;
  assign a_zero = (exp_a == '0) && (man_a == '0);
  assign b_zero = (exp_b == '0) && (man_b == '0);

  // Full mantissa with implicit 1
  logic [3:0] mant_a_full, mant_b_full;
  assign mant_a_full = {1'b1, man_a};
  assign mant_b_full = {1'b1, man_b};

  // 4×4 mantissa product = 8 bits
  logic [7:0] mant_product;
  assign mant_product = mant_a_full * mant_b_full;

  // Exponent: convert to FP32 bias (127)
  logic [8:0] exp_a_fp32, exp_b_fp32;
  assign exp_a_fp32 = {4'b0, exp_a} - {4'b0, bias} + 9'd127;
  assign exp_b_fp32 = {4'b0, exp_b} - {4'b0, bias} + 9'd127;

  logic [9:0] exp_sum;
  assign exp_sum = exp_a_fp32 + exp_b_fp32 - 10'd127;

  // Normalize mantissa to 23-bit FP32 mantissa field
  logic [22:0] mant_out;
  logic [7:0]  exp_out;
  always_comb begin
    if (mant_product[7]) begin
      mant_out = {mant_product[6:0], 16'b0};
      exp_out  = exp_sum[7:0] + 8'd1;
    end else begin
      mant_out = {mant_product[5:0], 17'b0};
      exp_out  = exp_sum[7:0];
    end
  end

  always_comb begin
    if (a_zero || b_zero)
      result = {sign_r, 31'b0};
    else
      result = {sign_r, exp_out, mant_out};
  end

endmodule
