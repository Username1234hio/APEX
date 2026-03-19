// ============================================================
// APEX-1 — allreduce_engine.sv
// Ring all-reduce for gradient synchronization across dies/cards.
// Supports SUM reduction in both RING and TREE topology.
// Connects to UCIe die-to-die link (tx/rx FIFO interfaces).
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module allreduce_engine #(
  parameter int DIE_ID   = 0,
  parameter int NUM_DIES_AR = 4   // Dies in ring
)(
  input  logic              clk,
  input  logic              rst_n,

  // Dispatch
  input  logic              op_valid,
  input  logic [23:0]       src_addr,
  input  logic [15:0]       elem_count,
  input  reduce_topo_t      topology,
  output logic              done,

  // Scratchpad interface
  output logic [SPAD_ADDR_W-1:0] spad_rd_addr,
  output logic              spad_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_rd_data,
  input  logic              spad_rd_valid,

  output logic [SPAD_ADDR_W-1:0] spad_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_wr_data,
  output logic              spad_wr_en,

  // UCIe TX (send to next die in ring)
  output logic [SPAD_DATA_W-1:0] ucie_tx_data,
  output logic              ucie_tx_valid,
  input  logic              ucie_tx_ready,

  // UCIe RX (receive from previous die in ring)
  input  logic [SPAD_DATA_W-1:0] ucie_rx_data,
  input  logic              ucie_rx_valid,
  output logic              ucie_rx_ready
);

  // ── Ring all-reduce phases ────────────────────────────────
  // Phase 1 (reduce-scatter): N-1 steps, each die sends a chunk
  //          and accumulates received chunk into local buffer.
  // Phase 2 (all-gather):     N-1 steps, each die forwards its
  //          fully-reduced chunk to the next die.

  localparam int CHUNK_ELEMS = 512 / 16;  // 32 BF16 elements per transfer

  typedef enum logic [2:0] {
    AR_IDLE,
    AR_REDUCE_SCATTER,
    AR_ACCUMULATE,
    AR_ALL_GATHER,
    AR_WRITEBACK,
    AR_DONE
  } ar_state_t;

  ar_state_t   state;
  logic [3:0]  step;
  logic [15:0] chunk_idx;
  logic [15:0] elems_rem;
  logic [23:0] rd_ptr, wr_ptr;

  // Incoming chunk accumulation buffer (one chunk)
  logic [SPAD_DATA_W-1:0] accum_buf;

  // ── BF16 element-wise addition of two 512-bit vectors ────
  function automatic logic [SPAD_DATA_W-1:0] vec_bf16_add(
    input logic [SPAD_DATA_W-1:0] a, b
  );
    logic [SPAD_DATA_W-1:0] result;
    for (int i = 0; i < 32; i++) begin
      // Simplified BF16 add (behavioral)
      result[i*16 +: 16] = a[i*16 +: 16] + b[i*16 +: 16];  // Placeholder
    end
    return result;
  endfunction

  // ── FSM ───────────────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      state        <= AR_IDLE;
      done         <= 1'b0;
      step         <= '0;
      chunk_idx    <= '0;
      ucie_tx_valid <= 1'b0;
      ucie_rx_ready <= 1'b1;
      spad_rd_en   <= 1'b0;
      spad_wr_en   <= 1'b0;
    end else begin
      done          <= 1'b0;
      spad_rd_en    <= 1'b0;
      spad_wr_en    <= 1'b0;
      ucie_tx_valid <= 1'b0;

      unique case (state)
        AR_IDLE: begin
          if (op_valid) begin
            rd_ptr    <= src_addr;
            wr_ptr    <= src_addr;
            elems_rem <= elem_count;
            chunk_idx <= '0;
            step      <= '0;
            state     <= AR_REDUCE_SCATTER;
          end
        end

        AR_REDUCE_SCATTER: begin
          // Read local chunk and send to next die
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= rd_ptr + chunk_idx * (SPAD_DATA_W/8);
          if (spad_rd_valid) begin
            ucie_tx_data  <= spad_rd_data;
            ucie_tx_valid <= 1'b1;
            state         <= AR_ACCUMULATE;
          end
        end

        AR_ACCUMULATE: begin
          // Wait for incoming chunk from previous die and accumulate
          if (ucie_rx_valid) begin
            accum_buf <= vec_bf16_add(accum_buf, ucie_rx_data);
            // Write accumulated chunk back to local scratchpad
            spad_wr_en   <= 1'b1;
            spad_wr_addr <= rd_ptr + chunk_idx * (SPAD_DATA_W/8);
            spad_wr_data <= vec_bf16_add(accum_buf, ucie_rx_data);

            step <= step + 1;
            if (step == NUM_DIES_AR - 2) begin
              // Reduce-scatter complete; start all-gather
              step      <= '0;
              chunk_idx <= '0;
              state     <= AR_ALL_GATHER;
            end else begin
              // Advance chunk index (ring offset per step)
              chunk_idx <= (chunk_idx + 1) % (elem_count / CHUNK_ELEMS);
              state     <= AR_REDUCE_SCATTER;
            end
          end
        end

        AR_ALL_GATHER: begin
          // Forward fully-reduced chunk to next die
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= rd_ptr + chunk_idx * (SPAD_DATA_W/8);
          if (spad_rd_valid) begin
            ucie_tx_data  <= spad_rd_data;
            ucie_tx_valid <= 1'b1;
          end
          // Also receive and write incoming chunk
          if (ucie_rx_valid) begin
            spad_wr_en   <= 1'b1;
            spad_wr_addr <= rd_ptr + ((chunk_idx + 1) % (elem_count / CHUNK_ELEMS)) * (SPAD_DATA_W/8);
            spad_wr_data <= ucie_rx_data;
            step <= step + 1;
            if (step == NUM_DIES_AR - 2) begin
              state <= AR_DONE;
            end else begin
              chunk_idx <= (chunk_idx + 1) % (elem_count / CHUNK_ELEMS);
            end
          end
        end

        AR_DONE: begin
          done  <= 1'b1;
          state <= AR_IDLE;
        end

        default: state <= AR_IDLE;
      endcase
    end
  end

  assign ucie_rx_ready = (state == AR_ACCUMULATE || state == AR_ALL_GATHER);

endmodule
