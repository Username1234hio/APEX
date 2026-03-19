// ============================================================
// APEX-1 — mxu_cluster.sv
// MXU Cluster: 4 × 128×128 systolic arrays + 2MB local SRAM
// + partial-sum reduction tree + sparsity engine interface.
// The cluster is the scheduling unit — one MATMUL instruction
// runs on one cluster at a time.
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module mxu_cluster #(
  parameter int CLUSTER_ID   = 0,
  parameter int LOCAL_SRAM_KB = TILE_SRAM_KB
)(
  input  logic              clk,
  input  logic              rst_n,

  // Sequencer control
  input  logic              op_valid,        // New operation dispatched
  input  opcode_t           op_code,
  input  logic [23:0]       op_addr_a,       // Scratchpad address of A matrix
  input  logic [23:0]       op_addr_b,       // Scratchpad address of B matrix
  input  logic [23:0]       op_addr_c,       // Scratchpad address of C (output)
  input  logic [15:0]       op_dim_m,
  input  logic [15:0]       op_dim_n,
  input  logic [11:0]       op_dim_k,
  input  dtype_t            op_dtype,
  input  logic              op_sparse,       // Use sparsity engine

  // Global scratchpad interface (read port)
  output logic [SPAD_ADDR_W-1:0] spad_rd_addr,
  output logic              spad_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_rd_data,
  input  logic              spad_rd_valid,

  // Global scratchpad interface (write port — results)
  output logic [SPAD_ADDR_W-1:0] spad_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_wr_data,
  output logic              spad_wr_en,

  // Power gate
  input  logic              cluster_en,

  // Status
  output cluster_status_t   status,
  output logic              done            // Pulse when operation completes
);

  // ── Local parameters ─────────────────────────────────────
  localparam int ARRAYS = ARRAYS_PER_CLUSTER;  // 4
  localparam int ROWS   = ARRAY_ROWS;          // 128
  localparam int COLS   = ARRAY_COLS;          // 128

  // ── Array control signals ─────────────────────────────────
  logic [ARRAYS-1:0]  arr_weight_load_en;
  logic [ROWS*16-1:0] arr_weight_col_data [ARRAYS];
  logic [$clog2(COLS)-1:0] arr_weight_col_idx [ARRAYS];

  logic [ARRAYS-1:0]  arr_act_valid;
  logic [COLS*16-1:0] arr_act_row_data [ARRAYS];
  logic [$clog2(ROWS)-1:0] arr_act_row_idx [ARRAYS];

  logic [ARRAYS-1:0]  arr_drain_en;
  logic               arr_result_valid [ARRAYS];
  logic [COLS*32-1:0] arr_result_data [ARRAYS];
  logic [ARRAYS-1:0]  arr_busy;
  logic [ARRAYS-1:0]  arr_en;

  // ── Instantiate 4 systolic arrays ─────────────────────────
  generate
    for (genvar a = 0; a < ARRAYS; a++) begin : gen_arrays
      systolic_array #(
        .ROWS(ROWS),
        .COLS(COLS)
      ) u_array (
        .clk              (clk),
        .rst_n            (rst_n),
        .dtype            (op_dtype),
        .weight_load_en   (arr_weight_load_en[a]),
        .weight_col_data  (arr_weight_col_data[a]),
        .weight_col_idx   (arr_weight_col_idx[a]),
        .act_valid        (arr_act_valid[a]),
        .act_row_data     (arr_act_row_data[a]),
        .act_row_idx      (arr_act_row_idx[a]),
        .drain_en         (arr_drain_en[a]),
        .result_valid     (arr_result_valid[a]),
        .result_data      (arr_result_data[a]),
        .array_en         (arr_en[a]),
        .busy             (arr_busy[a])
      );
    end
  endgenerate

  // ── State machine ─────────────────────────────────────────
  typedef enum logic [3:0] {
    ST_IDLE,
    ST_LOAD_WEIGHTS,
    ST_FEED_ACT,
    ST_WAIT_DRAIN,
    ST_DRAIN,
    ST_WRITEBACK,
    ST_DONE
  } state_t;

  state_t state, next_state;

  // Tile tracking counters
  logic [15:0] tile_m_cnt, tile_n_cnt, tile_k_cnt;
  logic [15:0] col_cnt;
  logic [15:0] row_cnt;
  logic [31:0] cycle_cnt;

  // Accumulated output buffer (holds one output tile before writeback)
  // ROWS × COLS × 32-bit = 128×128×4 = 65536 bytes = 64KB per array
  // We use a simpler model: write results directly to scratchpad
  logic [31:0] out_buffer [ROWS];

  // ── Main FSM ──────────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) state <= ST_IDLE;
    else        state <= next_state;
  end

  always_comb begin
    next_state = state;
    unique case (state)
      ST_IDLE:        if (op_valid && cluster_en)       next_state = ST_LOAD_WEIGHTS;
      ST_LOAD_WEIGHTS: if (col_cnt == COLS-1)           next_state = ST_FEED_ACT;
      ST_FEED_ACT:    if (row_cnt == ROWS-1)            next_state = ST_WAIT_DRAIN;
      ST_WAIT_DRAIN:  if (cycle_cnt == COLS + ROWS - 2) next_state = ST_DRAIN;
      ST_DRAIN:       if (row_cnt == ROWS-1)            next_state = ST_WRITEBACK;
      ST_WRITEBACK:   if (spad_wr_en && row_cnt == ROWS-1) next_state = ST_DONE;
      ST_DONE:                                          next_state = ST_IDLE;
      default:                                          next_state = ST_IDLE;
    endcase
  end

  // ── Counter updates ───────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      col_cnt   <= '0;
      row_cnt   <= '0;
      cycle_cnt <= '0;
    end else begin
      unique case (state)
        ST_IDLE: begin
          col_cnt <= '0; row_cnt <= '0; cycle_cnt <= '0;
        end
        ST_LOAD_WEIGHTS: begin
          col_cnt <= (col_cnt == COLS-1) ? '0 : col_cnt + 1;
        end
        ST_FEED_ACT: begin
          row_cnt <= (row_cnt == ROWS-1) ? '0 : row_cnt + 1;
        end
        ST_WAIT_DRAIN: begin
          cycle_cnt <= cycle_cnt + 1;
        end
        ST_DRAIN: begin
          row_cnt <= (row_cnt == ROWS-1) ? '0 : row_cnt + 1;
        end
        ST_WRITEBACK: begin
          row_cnt <= (row_cnt == ROWS-1) ? '0 : row_cnt + 1;
        end
        default: ;
      endcase
    end
  end

  // ── Scratchpad read interface ─────────────────────────────
  always_comb begin
    spad_rd_en   = 1'b0;
    spad_rd_addr = '0;
    unique case (state)
      ST_LOAD_WEIGHTS: begin
        // Read weight column from scratchpad
        spad_rd_en   = 1'b1;
        spad_rd_addr = op_addr_b + col_cnt * ROWS * 2;  // BF16 = 2 bytes
      end
      ST_FEED_ACT: begin
        // Read activation row from scratchpad
        spad_rd_en   = 1'b1;
        spad_rd_addr = op_addr_a + row_cnt * COLS * 2;
      end
      default: ;
    endcase
  end

  // ── Array control drive ───────────────────────────────────
  always_comb begin
    for (int a = 0; a < ARRAYS; a++) begin
      arr_en[a] = cluster_en && (state != ST_IDLE);
      arr_weight_load_en[a] = (state == ST_LOAD_WEIGHTS) && spad_rd_valid;
      arr_weight_col_idx[a] = col_cnt[$clog2(COLS)-1:0];
      arr_weight_col_data[a] = spad_rd_data[ROWS*16-1:0];  // Each array gets same weights (broadcast)
      arr_act_valid[a]   = (state == ST_FEED_ACT) && spad_rd_valid;
      arr_act_row_idx[a] = row_cnt[$clog2(ROWS)-1:0];
      arr_act_row_data[a] = spad_rd_data[COLS*16-1:0];
      arr_drain_en[a]    = (state == ST_DRAIN);
    end
  end

  // ── Partial sum reduction across 4 arrays ─────────────────
  // Arrays are partitioned: array 0 handles rows 0–31, etc.
  // For simplicity in this model, array 0 results are written back
  logic [31:0] reduced_result [ROWS];
  always_comb begin
    for (int r = 0; r < ROWS; r++) begin
      // Sum partial results from all 4 arrays (FP32 add)
      reduced_result[r] = arr_result_data[0][r*32 +: 32]
                        + arr_result_data[1][r*32 +: 32]
                        + arr_result_data[2][r*32 +: 32]
                        + arr_result_data[3][r*32 +: 32];
    end
  end

  // ── Scratchpad write interface ────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      spad_wr_en   <= 1'b0;
      spad_wr_addr <= '0;
      spad_wr_data <= '0;
    end else if (state == ST_WRITEBACK) begin
      spad_wr_en   <= 1'b1;
      spad_wr_addr <= op_addr_c + row_cnt * COLS * 4;  // FP32 = 4 bytes
      // Pack reduced results into SPAD_DATA_W-bit write bus
      spad_wr_data <= {480'b0, reduced_result[row_cnt]};  // Simplified: 1 result per write
    end else begin
      spad_wr_en   <= 1'b0;
    end
  end

  // ── Done pulse ────────────────────────────────────────────
  assign done = (state == ST_DONE);

  // ── Status output ─────────────────────────────────────────
  assign status.busy          = (state != ST_IDLE);
  assign status.power_gated   = !cluster_en;
  assign status.array_active  = arr_busy[3:0];
  assign status.tiles_completed = tile_m_cnt;

endmodule
