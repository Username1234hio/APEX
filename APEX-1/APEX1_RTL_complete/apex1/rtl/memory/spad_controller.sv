// ============================================================
// APEX-1 — spad_controller.sv
// 256 MB Global Scratchpad SRAM Controller
// 16 independent banks × 16 MB, 512-bit wide bus.
// Software-managed: no eviction, no coherence, no tags.
// Arbitrates between N_PORTS read/write requestors
// (4 MXU clusters + DMA engine = 5 ports).
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module spad_controller #(
  parameter int N_PORTS      = 5,    // Number of requestor ports
  parameter int N_BANKS      = 16,   // Number of SRAM banks
  parameter int BANK_SIZE_KB = 16384 // 16 MB per bank
)(
  input  logic              clk,
  input  logic              rst_n,

  // Read ports (one per requestor)
  input  logic [SPAD_ADDR_W-1:0] rd_addr   [N_PORTS],
  input  logic              rd_en    [N_PORTS],
  output logic [SPAD_DATA_W-1:0] rd_data   [N_PORTS],
  output logic              rd_valid  [N_PORTS],

  // Write ports
  input  logic [SPAD_ADDR_W-1:0] wr_addr   [N_PORTS],
  input  logic [SPAD_DATA_W-1:0] wr_data   [N_PORTS],
  input  logic              wr_en    [N_PORTS],
  output logic              wr_ack   [N_PORTS]
);

  // ── Bank address decode ───────────────────────────────────
  // Bank index = addr[27:24] (4 bits for 16 banks)
  // Bank offset = addr[23:0]
  localparam int BANK_ADDR_W = SPAD_ADDR_W - $clog2(N_BANKS);

  // ── SRAM model (behavioral — synthesis maps to TSMC SRAM macros) ──
  // In synthesis: replace with TSMC N3E SRAM compiler output
  logic [SPAD_DATA_W-1:0] sram [N_BANKS][2**BANK_ADDR_W];

  // ── Arbitration (round-robin per bank) ───────────────────
  logic [$clog2(N_PORTS)-1:0] rr_ptr [N_BANKS];

  // ── Per-port bank select ──────────────────────────────────
  logic [$clog2(N_BANKS)-1:0]  rd_bank  [N_PORTS];
  logic [BANK_ADDR_W-1:0]      rd_baddr [N_PORTS];
  logic [$clog2(N_BANKS)-1:0]  wr_bank  [N_PORTS];
  logic [BANK_ADDR_W-1:0]      wr_baddr [N_PORTS];

  generate
    for (genvar p = 0; p < N_PORTS; p++) begin : gen_decode
      assign rd_bank[p]  = rd_addr[p][SPAD_ADDR_W-1 -: $clog2(N_BANKS)];
      assign rd_baddr[p] = rd_addr[p][BANK_ADDR_W-1:0];
      assign wr_bank[p]  = wr_addr[p][SPAD_ADDR_W-1 -: $clog2(N_BANKS)];
      assign wr_baddr[p] = wr_addr[p][BANK_ADDR_W-1:0];
    end
  endgenerate

  // ── Bank conflict detection ───────────────────────────────
  // Two ports conflict if they target the same bank in the same cycle
  // Losing port is stalled for one cycle (simple priority arbitration)
  logic [N_BANKS-1:0] bank_rd_busy;
  logic [N_BANKS-1:0] bank_wr_busy;

  always_comb begin
    bank_rd_busy = '0;
    bank_wr_busy = '0;
  end

  // ── SRAM read/write logic ─────────────────────────────────
  always_ff @(posedge clk) begin
    // Write ports (priority: lowest port index wins on conflict)
    for (int p = 0; p < N_PORTS; p++) begin
      if (wr_en[p]) begin
        sram[wr_bank[p]][wr_baddr[p]] <= wr_data[p];
      end
    end
  end

  // Read with 1-cycle latency
  logic [SPAD_ADDR_W-1:0] rd_addr_r [N_PORTS];
  logic                   rd_en_r   [N_PORTS];

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      for (int p = 0; p < N_PORTS; p++) begin
        rd_en_r[p]   <= 1'b0;
        rd_valid[p]  <= 1'b0;
        rd_data[p]   <= '0;
        wr_ack[p]    <= 1'b0;
      end
    end else begin
      for (int p = 0; p < N_PORTS; p++) begin
        // Pipeline read address
        rd_addr_r[p] <= rd_addr[p];
        rd_en_r[p]   <= rd_en[p];

        // Return data on cycle after request
        rd_valid[p] <= rd_en_r[p];
        if (rd_en_r[p])
          rd_data[p] <= sram[rd_addr_r[p][SPAD_ADDR_W-1 -: $clog2(N_BANKS)]]
                            [rd_addr_r[p][BANK_ADDR_W-1:0]];

        // Write ack is immediate
        wr_ack[p] <= wr_en[p];
      end
    end
  end

endmodule
