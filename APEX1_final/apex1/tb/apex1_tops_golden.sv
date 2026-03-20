// ============================================================
// apex1_tops_golden.sv
//
// Golden reference model for TOPS verification.
//
// This module independently computes the expected TOPS based
// purely on the instruction stream observed on the dispatch
// bus — it never looks inside the DUT. Its result is compared
// against the hardware perf monitor. A mismatch indicates
// either a scheduling bug (ops being counted wrong) or a
// compute bug (tiles completing without doing real work).
//
// Attach like a scoreboard — instantiate alongside the DUT
// and drive it from the sequencer's dispatch outputs.
// ============================================================
`timescale 1ns/1ps
`include "apex1_pkg.sv"
import apex1_pkg::*;

module apex1_tops_golden #(
  parameter real   CLK_FREQ_GHZ  = 1.0,
  parameter real   TOPS_TOLERANCE = 0.02  // 2% tolerance on TOPS comparison
)(
  input  logic        clk,
  input  logic        rst_n,

  // Observe sequencer dispatch bus (read-only probes)
  input  logic        op_valid,         // New op issued this cycle
  input  opcode_t     op_code,          // What operation
  input  logic [15:0] op_m,
  input  logic [15:0] op_n,
  input  logic [11:0] op_k,
  input  dtype_t      op_dtype,
  input  logic        op_sparse,        // 2:4 sparsity active

  // Observe op completions
  input  logic        op_done,          // Tile complete (from cluster)

  // Window control (tie to same signals as perf_monitor)
  input  logic        start_measure,
  input  logic        stop_measure,

  // Results from hardware monitor (for cross-check)
  input  real         hw_tops,

  // Outputs
  output real         expected_tops,
  output real         expected_ops_total,
  output logic        tops_match        // 1 if HW within tolerance
);

  // ── Pending op queue ──────────────────────────────────────
  // Track ops that were issued but not yet completed
  // A tile is counted when it COMPLETES, not when issued
  typedef struct packed {
    logic [15:0] m, n;
    logic [11:0] k;
    logic        sparse;
    dtype_t      dtype;
    logic        valid;
  } pending_op_t;

  localparam int QUEUE_DEPTH = 16;  // Max in-flight tiles
  pending_op_t op_queue [QUEUE_DEPTH];
  int          q_head, q_tail;

  // ── Reference counters ────────────────────────────────────
  longint unsigned ref_ops;
  longint unsigned ref_cycles;
  real             ref_tops_last;

  typedef enum logic [1:0] { G_IDLE, G_RUNNING, G_DONE } golden_state_t;
  golden_state_t gstate;

  // ── Op weight function ────────────────────────────────────
  // Returns the number of operations for one tile
  // For 2:4 sparse: effective K is halved (50% zeros skipped)
  function automatic longint ops_for_tile(
    input logic [15:0] m, n,
    input logic [11:0] k,
    input logic        sparse
  );
    automatic longint effective_k = sparse ? k / 2 : k;
    return 2 * longint'(m) * longint'(n) * longint'(effective_k);
  endfunction

  // ── Queue management ──────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      q_head <= 0; q_tail <= 0;
      for (int i = 0; i < QUEUE_DEPTH; i++) op_queue[i].valid <= 0;
    end else begin
      // Enqueue on op_valid for compute ops
      if (op_valid && gstate == G_RUNNING &&
          (op_code == OP_MATMUL || op_code == OP_CONV2D || op_code == OP_SPARSE_MM)) begin
        op_queue[q_tail] <= '{m: op_m, n: op_n, k: op_k,
                               sparse: op_sparse, dtype: op_dtype, valid: 1'b1};
        q_tail <= (q_tail + 1) % QUEUE_DEPTH;
      end
      // Dequeue on op_done
      if (op_done && op_queue[q_head].valid) begin
        op_queue[q_head].valid <= 1'b0;
        q_head <= (q_head + 1) % QUEUE_DEPTH;
      end
    end
  end

  // ── Main measurement FSM ──────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      gstate            <= G_IDLE;
      ref_ops           <= '0;
      ref_cycles        <= '0;
      ref_tops_last     <= 0.0;
      expected_tops     <= 0.0;
      expected_ops_total<= 0.0;
      tops_match        <= 1'b1;
    end else begin
      unique case (gstate)
        G_IDLE: begin
          if (start_measure) begin
            ref_ops    <= '0;
            ref_cycles <= '0;
            gstate     <= G_RUNNING;
          end
        end

        G_RUNNING: begin
          ref_cycles <= ref_cycles + 1;

          // Count ops from completed tiles
          if (op_done && op_queue[q_head].valid) begin
            ref_ops <= ref_ops + ops_for_tile(
              op_queue[q_head].m,
              op_queue[q_head].n,
              op_queue[q_head].k,
              op_queue[q_head].sparse
            );
          end

          if (stop_measure) gstate <= G_DONE;
        end

        G_DONE: begin
          if (ref_cycles > 0) begin
            ref_tops_last     <= real'(ref_ops) * CLK_FREQ_GHZ
                                 / real'(ref_cycles) / 1.0e12;
            expected_tops     <= ref_tops_last;
            expected_ops_total<= real'(ref_ops);
          end

          // Cross-check against hardware monitor
          begin
            automatic real delta = (hw_tops > ref_tops_last)
                                   ? hw_tops - ref_tops_last
                                   : ref_tops_last - hw_tops;
            automatic real rel   = (ref_tops_last > 0.0)
                                   ? delta / ref_tops_last : 0.0;

            if (rel <= TOPS_TOLERANCE) begin
              tops_match <= 1'b1;
              $display("[GOLDEN] TOPS match: hw=%.4f ref=%.4f  delta=%.2f%%",
                       hw_tops, ref_tops_last, rel * 100.0);
            end else begin
              tops_match <= 1'b0;
              $error("[GOLDEN] TOPS MISMATCH: hw=%.4f ref=%.4f  delta=%.2f%% > %.0f%%",
                     hw_tops, ref_tops_last, rel * 100.0, TOPS_TOLERANCE * 100.0);
            end
          end

          gstate <= G_IDLE;
        end

        default: gstate <= G_IDLE;
      endcase
    end
  end

endmodule
