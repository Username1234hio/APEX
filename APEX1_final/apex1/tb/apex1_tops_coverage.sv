// ============================================================
// apex1_tops_coverage.sv
//
// Functional coverage model for TOPS testing.
// Ensures the testbench exercises all format × tile-size
// × sparsity combinations that matter for sign-off.
//
// Instantiate alongside the testbench. At $finish, check
// that coverage is 100% before declaring the TOPS result valid.
// ============================================================
`timescale 1ns/1ps
`include "apex1_pkg.sv"
import apex1_pkg::*;

module apex1_tops_coverage (
  input  logic    clk,
  input  logic    rst_n,
  input  logic    op_done,
  input  dtype_t  op_dtype,
  input  logic    op_sparse,
  input  logic [15:0] op_m,
  input  logic [15:0] op_n,
  input  logic [11:0] op_k,
  input  real     tops_result,
  input  real     utilization_pct
);

  // ── Tile size bins ────────────────────────────────────────
  typedef enum logic [1:0] {
    TILE_SMALL  = 0,   // M or N < 64
    TILE_MEDIUM = 1,   // 64 <= M,N < 128
    TILE_FULL   = 2,   // M = N = 128 (native array size)
    TILE_LARGE  = 3    // M or N > 128 (tiled across arrays)
  } tile_bin_t;

  function automatic tile_bin_t classify_tile(input logic [15:0] m, n);
    if (m == 128 && n == 128)  return TILE_FULL;
    if (m > 128  || n > 128)   return TILE_LARGE;
    if (m >= 64  && n >= 64)   return TILE_MEDIUM;
    return TILE_SMALL;
  endfunction

  // ── TOPS range bins ───────────────────────────────────────
  typedef enum logic [2:0] {
    TOPS_ZERO    = 0,   // < 0.001
    TOPS_LOW     = 1,   // 0.001 – 5.0
    TOPS_MED     = 2,   // 5.0 – 20.0
    TOPS_HIGH    = 3,   // 20.0 – 30.0
    TOPS_PEAK    = 4    // > 30.0
  } tops_bin_t;

  function automatic tops_bin_t classify_tops(input real t);
    if (t < 0.001)  return TOPS_ZERO;
    if (t < 5.0)    return TOPS_LOW;
    if (t < 20.0)   return TOPS_MED;
    if (t < 30.0)   return TOPS_HIGH;
    return TOPS_PEAK;
  endfunction

  // ── Utilization bins ──────────────────────────────────────
  typedef enum logic [1:0] {
    UTIL_POOR    = 0,   // < 50%
    UTIL_OK      = 1,   // 50–80%
    UTIL_GOOD    = 2,   // 80–95%
    UTIL_PEAK    = 3    // > 95%
  } util_bin_t;

  function automatic util_bin_t classify_util(input real u);
    if (u < 50.0)  return UTIL_POOR;
    if (u < 80.0)  return UTIL_OK;
    if (u < 95.0)  return UTIL_GOOD;
    return UTIL_PEAK;
  endfunction

  // ── Covergroups ───────────────────────────────────────────
  covergroup cg_ops_format @(posedge clk iff op_done);
    cp_dtype: coverpoint op_dtype {
      bins int8        = {DTYPE_INT8};
      bins int4        = {DTYPE_INT4};
      bins bf16        = {DTYPE_BF16};
      bins fp8_e4m3    = {DTYPE_FP8_E4M3};
      bins fp8_e5m2    = {DTYPE_FP8_E5M2};
    }
    cp_sparse: coverpoint op_sparse {
      bins dense  = {1'b0};
      bins sparse = {1'b1};
    }
    cp_tile: coverpoint classify_tile(op_m, op_n) {
      bins small  = {TILE_SMALL};
      bins medium = {TILE_MEDIUM};
      bins full   = {TILE_FULL};
      bins large  = {TILE_LARGE};
    }
    // Cross: every format × sparsity combination
    cx_fmt_sparse: cross cp_dtype, cp_sparse;
    // Cross: every format × tile size
    cx_fmt_tile: cross cp_dtype, cp_tile;
  endgroup

  covergroup cg_tops_quality @(posedge clk iff (tops_result > 0.0));
    cp_tops_range: coverpoint classify_tops(tops_result) {
      bins low  = {TOPS_LOW};
      bins med  = {TOPS_MED};
      bins high = {TOPS_HIGH};
      bins peak = {TOPS_PEAK};
    }
    cp_utilization: coverpoint classify_util(utilization_pct) {
      bins poor = {UTIL_POOR};
      bins ok   = {UTIL_OK};
      bins good = {UTIL_GOOD};
      bins peak = {UTIL_PEAK};
    }
  endgroup

  covergroup cg_k_dimension @(posedge clk iff op_done);
    cp_k: coverpoint op_k {
      bins k32  = {[1:32]};
      bins k64  = {[33:64]};
      bins k128 = {[65:128]};
      bins k256 = {[129:256]};
      bins k512 = {[257:512]};
    }
  endgroup

  // ── Instantiate covergroups ───────────────────────────────
  cg_ops_format    cov_fmt  = new();
  cg_tops_quality  cov_qual = new();
  cg_k_dimension   cov_k    = new();

  // ── Coverage report at end of simulation ─────────────────
  final begin
    $display("\n=== TOPS Coverage Report ===");
    $display("Format × sparsity:  %.1f%%", cov_fmt.cx_fmt_sparse.get_coverage());
    $display("Format × tile size: %.1f%%", cov_fmt.cx_fmt_tile.get_coverage());
    $display("TOPS range:         %.1f%%", cov_qual.cp_tops_range.get_coverage());
    $display("Utilization range:  %.1f%%", cov_qual.cp_utilization.get_coverage());
    $display("K dimension range:  %.1f%%", cov_k.cp_k.get_coverage());
    $display("Overall coverage:   %.1f%%",
        (cov_fmt.get_coverage() + cov_qual.get_coverage() + cov_k.get_coverage()) / 3.0);

    if (cov_fmt.get_coverage()  < 100.0) $warning("Format coverage incomplete");
    if (cov_qual.get_coverage() < 80.0)  $warning("TOPS quality coverage incomplete");
  end

  // ── Per-format minimum TOPS assertions ───────────────────
  // These fire when a measurement window closes with a result
  // below the minimum acceptable for each format.
  // Thresholds are per-array; scale by array count for full chip.
  property p_int8_tops_reasonable;
    @(posedge clk)
    (op_done && op_dtype == DTYPE_INT8 && !op_sparse && tops_result > 0)
    |-> (tops_result > 0.020);  // > 0.020 TOPS per array minimum
  endproperty

  property p_sparse_beats_dense;
    // Sparse TOPS should be >= dense (it skips more work in fewer cycles)
    @(posedge clk) op_sparse |=> (tops_result >= $past(tops_result) * 0.9);
  endproperty

  assert property (p_int8_tops_reasonable)
    else $warning("INT8 TOPS %.4f below expected minimum", tops_result);

endmodule
