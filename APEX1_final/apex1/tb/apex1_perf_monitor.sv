// ============================================================
// apex1_perf_monitor.sv
//
// Reusable performance monitor. Attach to any APEX-1 cluster
// or to the full die. Measures:
//   - Total MAC operations completed
//   - Clock cycles elapsed in the measurement window
//   - TOPS (computed as real, printed in $display)
//   - MAC utilization % (actual vs theoretical peak)
//   - Memory bandwidth (if hbm_bytes_transferred is driven)
//
// Usage:
//   1. Assert start_measure for one cycle to begin a window.
//   2. Assert stop_measure  for one cycle to end the window.
//   3. Read tops_result (real) or watch $display output.
//
// The monitor is purely passive — it never drives DUT signals.
// ============================================================
`ifndef APEX1_PERF_MONITOR_SV
`define APEX1_PERF_MONITOR_SV

`timescale 1ns/1ps

module apex1_perf_monitor #(
  // ── Hardware constants (must match RTL) ──────────────────
  parameter int    ARRAYS          = 64,      // Total systolic arrays in scope
  parameter int    ARRAY_ROWS      = 128,     // Rows per array
  parameter int    ARRAY_COLS      = 128,     // Cols per array
  parameter real   CLK_FREQ_GHZ    = 1.0,     // Clock frequency in GHz
  parameter string MONITOR_NAME    = "APEX1", // Label in $display output
  parameter int    WINDOW_CYCLES   = 0        // 0 = manual start/stop
                                              // >0 = auto-window every N cycles
)(
  input  logic        clk,
  input  logic        rst_n,

  // ── Measurement window control ────────────────────────────
  input  logic        start_measure,   // Pulse: begin window, zero counters
  input  logic        stop_measure,    // Pulse: end window, print result

  // ── Per-array activity probes ─────────────────────────────
  // Each bit = 1 when that array performed a MAC this cycle.
  // For systolic arrays: assert for the duration of a tile computation.
  input  logic [ARRAYS-1:0]  array_active,

  // ── Completed-operation probes ────────────────────────────
  // Pulse these when a MATMUL/CONV tile fully completes.
  // The monitor adds 2*M*N*K operations (multiply + accumulate per MAC).
  input  logic        op_done,         // Tile completion pulse
  input  logic [15:0] op_m,            // M dimension of completed tile
  input  logic [15:0] op_n,            // N dimension
  input  logic [11:0] op_k,            // K dimension

  // ── Memory bandwidth probes ───────────────────────────────
  input  logic        hbm_rd_valid,    // HBM read data valid this cycle
  input  logic        hbm_wr_valid,    // HBM write valid this cycle
  // Bytes per HBM burst beat (HBM3e: 64B per 512-bit beat)
  parameter int HBM_BYTES_PER_BEAT = 64,

  // ── Outputs (readable by parent testbench) ────────────────
  output real         tops_result,     // TOPS in the last window
  output real         utilization_pct, // MAC utilization %
  output real         hbm_bw_tbps,     // HBM bandwidth in TB/s
  output logic        measurement_active
);

  // ── Derived constants ─────────────────────────────────────
  localparam longint MACS_PER_CYCLE_PEAK =
      longint'(ARRAYS) * longint'(ARRAY_ROWS) * longint'(ARRAY_COLS);
  // Peak OPS/cycle = MACs/cycle × 2 (multiply + add)
  localparam longint OPS_PER_CYCLE_PEAK = MACS_PER_CYCLE_PEAK * 2;

  // ── Internal counters (64-bit to avoid overflow) ──────────
  longint unsigned total_ops;       // Accumulated MAC ops (×2 for TOPS)
  longint unsigned total_cycles;    // Cycles in window
  longint unsigned active_mac_cycles; // Cycle-weighted active MACs
  longint unsigned hbm_rd_beats;
  longint unsigned hbm_wr_beats;

  // ── Auto-window counter ───────────────────────────────────
  int unsigned auto_window_cnt;
  logic        auto_trigger;
  generate
    if (WINDOW_CYCLES > 0) begin : gen_auto_window
      always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) auto_window_cnt <= 0;
        else        auto_window_cnt <= (auto_window_cnt == WINDOW_CYCLES-1) ? 0
                                       : auto_window_cnt + 1;
      end
      assign auto_trigger = (auto_window_cnt == WINDOW_CYCLES-1);
    end else begin
      assign auto_trigger = 1'b0;
    end
  endgenerate

  // ── Measurement FSM ───────────────────────────────────────
  typedef enum logic [1:0] { MON_IDLE, MON_RUNNING, MON_DONE } mon_state_t;
  mon_state_t mon_state;
  assign measurement_active = (mon_state == MON_RUNNING);

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      mon_state        <= MON_IDLE;
      total_ops        <= '0;
      total_cycles     <= '0;
      active_mac_cycles<= '0;
      hbm_rd_beats     <= '0;
      hbm_wr_beats     <= '0;
      tops_result      <= 0.0;
      utilization_pct  <= 0.0;
      hbm_bw_tbps      <= 0.0;
    end else begin
      unique case (mon_state)

        MON_IDLE: begin
          if (start_measure || auto_trigger) begin
            total_ops         <= '0;
            total_cycles      <= '0;
            active_mac_cycles <= '0;
            hbm_rd_beats      <= '0;
            hbm_wr_beats      <= '0;
            mon_state         <= MON_RUNNING;
          end
        end

        MON_RUNNING: begin
          // Count every clock in the window
          total_cycles <= total_cycles + 1;

          // Accumulate ops when a tile completes
          // 2 ops per MAC element (multiply + accumulate)
          if (op_done) begin
            total_ops <= total_ops + 2 * longint'(op_m) * longint'(op_n) * longint'(op_k);
          end

          // Track active MAC utilization
          // Count the number of active arrays this cycle
          begin
            automatic int active_count = 0;
            for (int i = 0; i < ARRAYS; i++)
              if (array_active[i]) active_count++;
            active_mac_cycles <= active_mac_cycles +
              longint'(active_count) * longint'(ARRAY_ROWS) * longint'(ARRAY_COLS);
          end

          // HBM bandwidth tracking
          if (hbm_rd_valid) hbm_rd_beats <= hbm_rd_beats + 1;
          if (hbm_wr_valid) hbm_wr_beats <= hbm_wr_beats + 1;

          // Stop condition
          if (stop_measure || auto_trigger) begin
            mon_state <= MON_DONE;
          end
        end

        MON_DONE: begin
          // ── Compute TOPS ──────────────────────────────────
          // TOPS = total_ops / (total_cycles × (1/CLK_FREQ_GHZ × 1e-9))
          //      = total_ops × CLK_FREQ_GHZ / total_cycles / 1e12
          if (total_cycles > 0) begin
            tops_result <= real'(total_ops) * CLK_FREQ_GHZ
                           / real'(total_cycles) / 1.0e12;

            // ── Utilization ───────────────────────────────
            // Theoretical peak MAC-cycles = total_cycles × MACS_PER_CYCLE_PEAK
            utilization_pct <= (real'(active_mac_cycles) /
                                (real'(total_cycles) * real'(MACS_PER_CYCLE_PEAK))) * 100.0;

            // ── HBM bandwidth ─────────────────────────────
            // TB/s = (beats × bytes_per_beat) / (cycles / clk_freq_ghz × 1e9) / 1e12
            begin
              automatic longint total_bytes = (hbm_rd_beats + hbm_wr_beats) * HBM_BYTES_PER_BEAT;
              automatic real    elapsed_ns  = real'(total_cycles) / (CLK_FREQ_GHZ * 1.0e9);
              // elapsed_ns is in nanoseconds; convert to seconds for TB/s
              hbm_bw_tbps <= real'(total_bytes) / (elapsed_ns * 1.0e9) / 1.0e12;
            end
          end

          // ── Print results ──────────────────────────────
          $display("");
          $display("╔══════════════════════════════════════════════╗");
          $display("║  %s Performance Report", MONITOR_NAME);
          $display("╠══════════════════════════════════════════════╣");
          $display("║  Window cycles  : %0d", total_cycles);
          $display("║  Total ops      : %0d", total_ops);
          $display("║  TOPS (measured): %.4f", tops_result);
          $display("║  Peak TOPS      : %.4f",
              real'(OPS_PER_CYCLE_PEAK) * CLK_FREQ_GHZ / 1.0e12);
          $display("║  MAC utilization: %.2f%%", utilization_pct);
          $display("║  HBM bandwidth  : %.3f TB/s", hbm_bw_tbps);
          $display("╚══════════════════════════════════════════════╝");
          $display("");

          mon_state <= MON_IDLE;
        end

        default: mon_state <= MON_IDLE;
      endcase
    end
  end

  // ── Assertions ────────────────────────────────────────────
  // Check op dimensions are non-zero when op_done fires
  property p_op_dims_nonzero;
    @(posedge clk) op_done |-> (op_m > 0 && op_n > 0 && op_k > 0);
  endproperty
  assert property (p_op_dims_nonzero)
    else $error("[%s] op_done with zero dimension: M=%0d N=%0d K=%0d",
                MONITOR_NAME, op_m, op_n, op_k);

  // Check we don't overflow 64-bit counters (warn at 90%)
  property p_no_counter_overflow;
    @(posedge clk) measurement_active |->
      (total_ops < 64'hE666_6666_6666_6666);
  endproperty
  assert property (p_no_counter_overflow)
    else $warning("[%s] total_ops approaching 64-bit overflow", MONITOR_NAME);

endmodule
`endif
