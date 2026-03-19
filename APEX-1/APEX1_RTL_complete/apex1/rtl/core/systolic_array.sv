// ============================================================
// APEX-1 — systolic_array.sv
// 128×128 weight-stationary systolic array.
// Activations stream in from the west (left) edge, one row/cycle.
// Weights are loaded once per tile and held stationary.
// Results drain from the east (right) edge via reduction tree.
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module systolic_array #(
  parameter int ROWS = ARRAY_ROWS,   // 128
  parameter int COLS = ARRAY_COLS    // 128
)(
  input  logic              clk,
  input  logic              rst_n,

  // Data type
  input  dtype_t            dtype,

  // Weight load interface (one column of weights per cycle, broadcast)
  input  logic              weight_load_en,
  input  logic [ROWS*16-1:0] weight_col_data,   // One column: ROWS×16-bit values
  input  logic [$clog2(COLS)-1:0] weight_col_idx,

  // Activation input (west edge, one row per cycle)
  input  logic              act_valid,
  input  logic [COLS*16-1:0] act_row_data,      // One row: COLS×16-bit values
  input  logic [$clog2(ROWS)-1:0] act_row_idx,

  // Drain control
  input  logic              drain_en,           // Pulse to drain all columns

  // Output — one full row of accumulators per drain cycle
  output logic              result_valid,
  output logic [COLS*32-1:0] result_data,       // COLS×FP32 accumulators

  // Power gate
  input  logic              array_en,

  // Status
  output logic              busy
);

  // ── Weight registers (one per cell, loaded before each tile) ──
  logic [15:0] weights [ROWS][COLS];

  // ── Activation input shift register (feeds west edge) ─────────
  logic [15:0] act_west [ROWS];   // Current activation column
  logic [15:0] act_pipe [ROWS][COLS]; // Pipeline registers in array

  // ── Accumulator drain bus (rightward chain) ───────────────────
  logic [31:0] drain_bus [ROWS][COLS+1];  // COLS+1 so last col feeds output

  // ── MAC array instantiation ───────────────────────────────────
  // Generate ROWS × COLS mac_cell instances
  logic [15:0] act_e_wire [ROWS][COLS];  // East outputs
  logic [15:0] wgt_s_wire [ROWS][COLS];  // South outputs

  generate
    for (genvar r = 0; r < ROWS; r++) begin : gen_row
      for (genvar c = 0; c < COLS; c++) begin : gen_col
        mac_cell u_mac (
          .clk       (clk),
          .rst_n     (rst_n),
          .dtype     (dtype),
          // Activation: west input = either act_west (col 0) or east output of previous cell
          .act_in    (c == 0 ? act_west[r] : act_e_wire[r][c-1]),
          .act_out   (act_e_wire[r][c]),
          // Weight: north input = weight register for this cell
          .wgt_in    (weights[r][c]),
          .wgt_out   (wgt_s_wire[r][c]),   // Unused in weight-stationary mode
          // Drain chain: west input = 0 (col 0) or previous drain_bus
          .drain_en  (drain_en),
          .drain_in  (drain_bus[r][c]),
          .drain_out (drain_bus[r][c+1]),
          .cell_en   (array_en)
        );
      end
    end
  endgenerate

  // ── Weight loading ────────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      // Clear weights
      for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
          weights[r][c] <= '0;
    end else if (weight_load_en && array_en) begin
      // Load one column of weights
      for (int r = 0; r < ROWS; r++)
        weights[r][weight_col_idx] <= weight_col_data[r*16 +: 16];
    end
  end

  // ── Activation feeding (west edge) ────────────────────────────
  // Activations arrive one row at a time, staggered to match systolic timing
  logic [15:0] act_stagger [ROWS][ROWS];  // Stagger buffer

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      for (int r = 0; r < ROWS; r++)
        act_west[r] <= '0;
    end else if (act_valid && array_en) begin
      // Load activation row into stagger buffer
      for (int c = 0; c < COLS; c++)
        act_stagger[act_row_idx][c] <= act_row_data[c*16 +: 16];
    end
  end

  // Staggered feed: row r feeds into west edge at cycle r after trigger
  integer stagger_cnt;
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      stagger_cnt <= 0;
      for (int r = 0; r < ROWS; r++) act_west[r] <= '0;
    end else if (array_en) begin
      if (act_valid && act_row_idx == 0) stagger_cnt <= 0;
      // Each row is skewed by its row index to align with systolic timing
      for (int r = 0; r < ROWS; r++) begin
        if (stagger_cnt >= r)
          act_west[r] <= act_stagger[r][stagger_cnt - r < COLS ? stagger_cnt - r : 0];
        else
          act_west[r] <= '0;
      end
      stagger_cnt <= stagger_cnt + 1;
    end
  end

  // ── Drain bus initialization ──────────────────────────────────
  // Left edge of drain chain is always 0
  generate
    for (genvar r = 0; r < ROWS; r++) begin : gen_drain_init
      assign drain_bus[r][0] = '0;
    end
  endgenerate

  // ── Output capture ────────────────────────────────────────────
  // After drain, result_data holds the rightmost drain_bus column
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      result_valid <= 1'b0;
      result_data  <= '0;
    end else begin
      result_valid <= drain_en;
      if (drain_en && array_en) begin
        for (int r = 0; r < ROWS; r++)
          result_data[r*32 +: 32] <= drain_bus[r][COLS];
      end
    end
  end

  // ── Busy flag ─────────────────────────────────────────────────
  assign busy = array_en && (act_valid || (stagger_cnt > 0 && stagger_cnt < ROWS + COLS));

endmodule
