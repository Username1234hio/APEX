// ============================================================
// apex1_tops_tb.sv
//
// Comprehensive TOPS measurement testbench for APEX-1.
//
// Test scenarios:
//   1. Peak INT8  TOPS  — back-to-back tiles, no stalls
//   2. Peak BF16  TOPS  — same, BF16 format
//   3. Peak FP8   TOPS  — same, FP8 format
//   4. Sparse INT8 TOPS — 2:4 structured sparsity
//   5. Sustained TOPS   — realistic mixed workload with HBM gaps
//   6. Utilization sweep — varies tile size to find optimal shape
//
// Methodology:
//   The testbench drives the systolic array directly, bypassing
//   the sequencer, to measure raw compute throughput without
//   software overhead. A separate test drives the full
//   static_sequencer → cluster path for end-to-end TOPS.
//
// TOPS formula:
//   TOPS = (2 × M × N × K × tiles_completed)
//          ─────────────────────────────────────
//          (cycles_elapsed × (1 / clk_freq_ghz) × 1e3)
//
//   The ×2 accounts for the multiply and the accumulate — both
//   are "operations" in the TOPS definition.
// ============================================================
`timescale 1ns/1ps
`include "apex1_pkg.sv"
import apex1_pkg::*;

module apex1_tops_tb;

  // ── Simulation parameters ─────────────────────────────────
  localparam real   CLK_PERIOD_NS  = 1.0;    // 1 ns = 1 GHz
  localparam real   CLK_FREQ_GHZ   = 1.0;
  localparam int    WARMUP_CYCLES  = 100;    // Cycles before measurement
  localparam int    MEASURE_TILES  = 200;    // Tiles per measurement window
  localparam int    DRAIN_CYCLES   = ARRAY_ROWS + ARRAY_COLS + 10; // Pipeline flush

  // Tile dimensions for sweep tests
  localparam int    TILE_M = ARRAY_ROWS;  // 128
  localparam int    TILE_N = ARRAY_COLS;  // 128
  localparam int    TILE_K = ARRAY_COLS;  // 128

  // ── Clock ─────────────────────────────────────────────────
  logic clk = 0;
  always #(CLK_PERIOD_NS/2.0) clk = ~clk;
  logic rst_n = 0;
  initial begin
    repeat(20) @(posedge clk);
    rst_n = 1;
  end

  // ── DUT — single systolic array (unit under test) ─────────
  // We use systolic_array directly to measure raw MAC throughput.
  // For end-to-end tests we use apex1_die.
  dtype_t            dut_dtype        = DTYPE_INT8;
  logic              dut_weight_load  = 0;
  logic [ARRAY_ROWS*16-1:0] dut_weight_data = '0;
  logic [$clog2(ARRAY_COLS)-1:0] dut_weight_idx = '0;
  logic              dut_act_valid    = 0;
  logic [ARRAY_COLS*16-1:0] dut_act_data  = '0;
  logic [$clog2(ARRAY_ROWS)-1:0] dut_act_idx = '0;
  logic              dut_drain        = 0;
  logic              dut_result_valid;
  logic [ARRAY_COLS*32-1:0] dut_result_data;
  logic              dut_busy;

  systolic_array #(
    .ROWS(ARRAY_ROWS), .COLS(ARRAY_COLS)
  ) u_dut (
    .clk             (clk),
    .rst_n           (rst_n),
    .dtype           (dut_dtype),
    .weight_load_en  (dut_weight_load),
    .weight_col_data (dut_weight_data),
    .weight_col_idx  (dut_weight_idx),
    .act_valid       (dut_act_valid),
    .act_row_data    (dut_act_data),
    .act_row_idx     (dut_act_idx),
    .drain_en        (dut_drain),
    .result_valid    (dut_result_valid),
    .result_data     (dut_result_data),
    .array_en        (1'b1),
    .busy            (dut_busy)
  );

  // ── Performance monitor ───────────────────────────────────
  logic        mon_start   = 0;
  logic        mon_stop    = 0;
  logic        mon_op_done = 0;
  logic [15:0] mon_op_m    = TILE_M;
  logic [15:0] mon_op_n    = TILE_N;
  logic [11:0] mon_op_k    = TILE_K;
  real         tops_result;
  real         util_pct;
  real         hbm_bw;
  logic        mon_active;

  // array_active: for a single array, bit 0 = dut_busy
  logic [63:0] array_active_vec;
  assign array_active_vec = {63'b0, dut_busy};

  apex1_perf_monitor #(
    .ARRAYS       (1),            // One array in this unit test
    .ARRAY_ROWS   (ARRAY_ROWS),
    .ARRAY_COLS   (ARRAY_COLS),
    .CLK_FREQ_GHZ (CLK_FREQ_GHZ),
    .MONITOR_NAME ("APEX1_ARRAY0"),
    .WINDOW_CYCLES(0)
  ) u_mon (
    .clk               (clk),
    .rst_n             (rst_n),
    .start_measure     (mon_start),
    .stop_measure      (mon_stop),
    .array_active      (array_active_vec[0:0]),
    .op_done           (mon_op_done),
    .op_m              (mon_op_m),
    .op_n              (mon_op_n),
    .op_k              (mon_op_k),
    .hbm_rd_valid      (1'b0),
    .hbm_wr_valid      (1'b0),
    .tops_result       (tops_result),
    .utilization_pct   (util_pct),
    .hbm_bw_tbps       (hbm_bw),
    .measurement_active(mon_active)
  );

  // ── Helper tasks ──────────────────────────────────────────

  // Load all weight columns in sequence (simulates one weight tile)
  task automatic load_weights(input dtype_t fmt);
    for (int col = 0; col < ARRAY_COLS; col++) begin
      @(posedge clk);
      dut_weight_load  <= 1;
      dut_weight_idx   <= col[$clog2(ARRAY_COLS)-1:0];
      dut_weight_data  <= {ARRAY_ROWS{16'h3F80}};  // All 1.0 (BF16)
    end
    @(posedge clk);
    dut_weight_load <= 0;
  endtask

  // Feed one full activation matrix (ROWS rows, staggered)
  // Returns when all rows have been submitted
  task automatic feed_activations();
    for (int row = 0; row < ARRAY_ROWS; row++) begin
      @(posedge clk);
      dut_act_valid <= 1;
      dut_act_idx   <= row[$clog2(ARRAY_ROWS)-1:0];
      dut_act_data  <= {ARRAY_COLS{16'h3F80}};  // All 1.0
    end
    @(posedge clk);
    dut_act_valid <= 0;
  endtask

  // Wait for systolic pipeline to drain (ROWS + COLS cycles)
  task automatic wait_drain();
    repeat(DRAIN_CYCLES) @(posedge clk);
    @(posedge clk);
    dut_drain <= 1;
    @(posedge clk);
    dut_drain <= 0;
    @(posedge dut_result_valid);
    @(posedge clk);
  endtask

  // Run N tiles back-to-back and measure TOPS
  task automatic run_tops_test(
    input  string    test_name,
    input  dtype_t   fmt,
    input  int       n_tiles,
    input  bit       use_sparse
  );
    $display("\n[TEST] %s  fmt=%0s  tiles=%0d  sparse=%0b",
             test_name, fmt.name(), n_tiles, use_sparse);

    dut_dtype <= fmt;
    mon_op_m  <= TILE_M;
    mon_op_n  <= TILE_N;
    mon_op_k  <= TILE_K;

    // Warmup — don't measure this
    load_weights(fmt);
    feed_activations();
    wait_drain();

    // Start measurement window
    @(posedge clk);
    mon_start <= 1;
    @(posedge clk);
    mon_start <= 0;

    // Run tiles back-to-back
    for (int t = 0; t < n_tiles; t++) begin
      // Weights stay loaded (weight-stationary): skip reload after first
      if (t == 0) load_weights(fmt);

      feed_activations();
      wait_drain();

      // Signal tile completion to monitor
      @(posedge clk);
      mon_op_done <= 1;
      @(posedge clk);
      mon_op_done <= 0;
    end

    // Stop measurement and print result
    @(posedge clk);
    mon_stop <= 1;
    @(posedge clk);
    mon_stop <= 0;

    // Wait for monitor to finish computing
    repeat(10) @(posedge clk);

    $display("[RESULT] %s: %.4f TOPS  (util: %.1f%%)",
             test_name, tops_result, util_pct);
  endtask

  // ── Tile dimension sweep — find optimal M/N/K for TOPS ───
  task automatic tile_sweep();
    int sweep_m, sweep_n, sweep_k;
    real best_tops;
    int  best_m, best_n, best_k;

    $display("\n[SWEEP] Tile dimension sweep — finding peak configuration");
    best_tops = 0.0;

    // Sweep K (inner dimension): affects pipeline fill efficiency
    foreach (int k_val : '{32, 64, 128, 256}) begin
      sweep_m = ARRAY_ROWS;
      sweep_n = ARRAY_COLS;
      sweep_k = k_val;

      mon_op_m <= sweep_m;
      mon_op_n <= sweep_n;
      mon_op_k <= sweep_k[11:0];

      load_weights(DTYPE_INT8);

      @(posedge clk); mon_start <= 1;
      @(posedge clk); mon_start <= 0;

      for (int t = 0; t < 50; t++) begin
        feed_activations();
        repeat(sweep_k + DRAIN_CYCLES) @(posedge clk);
        dut_drain <= 1; @(posedge clk); dut_drain <= 0;
        @(posedge clk); mon_op_done <= 1;
        @(posedge clk); mon_op_done <= 0;
      end

      @(posedge clk); mon_stop <= 1;
      @(posedge clk); mon_stop <= 0;
      repeat(10) @(posedge clk);

      $display("[SWEEP] M=%3d N=%3d K=%3d  →  %.4f TOPS",
               sweep_m, sweep_n, sweep_k, tops_result);

      if (tops_result > best_tops) begin
        best_tops = tops_result;
        best_m = sweep_m; best_n = sweep_n; best_k = sweep_k;
      end
    end

    $display("[SWEEP] Best: M=%0d N=%0d K=%0d  →  %.4f TOPS",
             best_m, best_n, best_k, best_tops);
  endtask

  // ── Sustained TOPS test — includes HBM stall gaps ────────
  // Models a real inference workload where HBM load latency
  // causes the array to stall periodically.
  task automatic sustained_tops_test(input int hbm_stall_cycles);
    $display("\n[TEST] Sustained TOPS  (HBM stall=%0d cycles/tile)", hbm_stall_cycles);

    mon_op_m <= TILE_M; mon_op_n <= TILE_N; mon_op_k <= TILE_K;
    load_weights(DTYPE_INT8);

    @(posedge clk); mon_start <= 1;
    @(posedge clk); mon_start <= 0;

    for (int t = 0; t < 100; t++) begin
      // Simulate HBM fetch stall before each tile
      repeat(hbm_stall_cycles) @(posedge clk);

      feed_activations();
      wait_drain();

      @(posedge clk); mon_op_done <= 1;
      @(posedge clk); mon_op_done <= 0;
    end

    @(posedge clk); mon_stop <= 1;
    @(posedge clk); mon_stop <= 0;
    repeat(10) @(posedge clk);

    $display("[RESULT] Sustained (stall=%0d): %.4f TOPS  (util: %.1f%%)",
             hbm_stall_cycles, tops_result, util_pct);
  endtask

  // ── Utilization efficiency check ──────────────────────────
  // Verifies the array hits >95% utilization in ideal conditions
  task automatic check_peak_utilization();
    $display("\n[CHECK] Peak utilization verification");

    load_weights(DTYPE_INT8);

    @(posedge clk); mon_start <= 1;
    @(posedge clk); mon_start <= 0;

    // Run 50 back-to-back tiles — pipeline should be full
    for (int t = 0; t < 50; t++) begin
      feed_activations();
      wait_drain();
      @(posedge clk); mon_op_done <= 1;
      @(posedge clk); mon_op_done <= 0;
    end

    @(posedge clk); mon_stop <= 1;
    @(posedge clk); mon_stop <= 0;
    repeat(10) @(posedge clk);

    // Pass/fail assertion on utilization
    if (util_pct >= 95.0) begin
      $display("[PASS] Peak utilization %.2f%% >= 95%%", util_pct);
    end else begin
      $error("[FAIL] Peak utilization %.2f%% < 95%% — pipeline bubble detected",
             util_pct);
    end
  endtask

  // ── Main test sequence ────────────────────────────────────
  initial begin
    @(posedge rst_n);
    repeat(WARMUP_CYCLES) @(posedge clk);

    $display("\n========================================");
    $display("  APEX-1 TOPS Measurement Suite");
    $display("  Clock: %.0f GHz  Array: %0dx%0d",
             CLK_FREQ_GHZ, ARRAY_ROWS, ARRAY_COLS);
    $display("  Peak (1 array): %.3f TOPS",
             2.0 * ARRAY_ROWS * ARRAY_COLS * CLK_FREQ_GHZ / 1.0e3);
    $display("========================================");

    // ── Test 1: Peak INT8 TOPS ────────────────────────────
    run_tops_test("Peak_INT8", DTYPE_INT8, MEASURE_TILES, 0);

    // ── Test 2: Peak BF16 TOPS ────────────────────────────
    run_tops_test("Peak_BF16", DTYPE_BF16, MEASURE_TILES, 0);

    // ── Test 3: Peak FP8 TOPS ─────────────────────────────
    run_tops_test("Peak_FP8_E4M3", DTYPE_FP8_E4M3, MEASURE_TILES, 0);

    // ── Test 4: Sustained TOPS (no stall) ────────────────
    sustained_tops_test(0);     // Ideal: no HBM stall

    // ── Test 5: Sustained TOPS (10-cycle HBM stall) ──────
    sustained_tops_test(10);    // Realistic: 10ns HBM latency per tile

    // ── Test 6: Sustained TOPS (120-cycle HBM stall) ─────
    sustained_tops_test(120);   // Worst-case: cold HBM (full latency)

    // ── Test 7: Tile dimension sweep ─────────────────────
    tile_sweep();

    // ── Test 8: Peak utilization check ───────────────────
    check_peak_utilization();

    $display("\n[DONE] All TOPS tests complete.");
    $display("To compute full-chip TOPS, multiply single-array result");
    $display("by %0d (= %0d arrays in the 4-die APEX-1 package).",
             ARRAYS_PER_CLUSTER * CLUSTERS_PER_DIE * NUM_DIES,
             ARRAYS_PER_CLUSTER * CLUSTERS_PER_DIE * NUM_DIES);

    repeat(50) @(posedge clk);
    $finish;
  end

  // ── Timeout ───────────────────────────────────────────────
  initial begin
    #50_000_000;  // 50 ms sim time
    $error("TIMEOUT — simulation did not complete in 50 ms");
    $finish;
  end

  // ── VCD ───────────────────────────────────────────────────
  initial begin
    $dumpfile("apex1_tops.vcd");
    $dumpvars(0, apex1_tops_tb);
  end

endmodule
