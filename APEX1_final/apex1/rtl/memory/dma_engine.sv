// ============================================================
// APEX-1 — dma_engine.sv
// 8-channel DMA engine: HBM ↔ Scratchpad transfers.
// Each channel has a descriptor with a scheduled fire_cycle.
// The sequencer loads descriptors; the DMA fires them at the
// exact cycle specified, hiding HBM latency behind compute.
// ============================================================
import apex1_pkg::*;

module dma_engine (
  input  logic              clk,
  input  logic              rst_n,

  // Global cycle counter (from sequencer)
  input  logic [31:0]       global_cycle,

  // Descriptor load interface (from sequencer)
  input  logic              desc_valid,
  input  dma_desc_t         desc_in,
  input  logic [2:0]        desc_channel,   // Which of 8 channels to load
  output logic              desc_ready,     // Channel is free

  // HBM read interface (AXI4-like, simplified)
  output logic [HBM_ADDR_W-1:0] hbm_rd_addr,
  output logic [7:0]        hbm_rd_len,     // Burst length - 1
  output logic              hbm_rd_valid,
  input  logic              hbm_rd_ready,
  input  logic [HBM_DATA_W-1:0] hbm_rd_data,
  input  logic              hbm_rd_last,
  input  logic              hbm_rd_data_valid,

  // HBM write interface
  output logic [HBM_ADDR_W-1:0] hbm_wr_addr,
  output logic [HBM_DATA_W-1:0] hbm_wr_data,
  output logic              hbm_wr_valid,
  input  logic              hbm_wr_ready,

  // Scratchpad write interface (DMA → SPAD)
  output logic [SPAD_ADDR_W-1:0] spad_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_wr_data,
  output logic              spad_wr_en,
  input  logic              spad_wr_ack,

  // Scratchpad read interface (SPAD → DMA → HBM)
  output logic [SPAD_ADDR_W-1:0] spad_rd_addr,
  output logic              spad_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_rd_data,
  input  logic              spad_rd_valid,

  // Completion signals (one per channel)
  output logic [7:0]        ch_done,

  // Status
  output logic [7:0]        ch_active
);

  // ── Channel state machine ─────────────────────────────────
  typedef enum logic [2:0] {
    CH_IDLE,
    CH_WAIT,      // Waiting for fire_cycle
    CH_FETCH,     // Issuing HBM read request
    CH_RECEIVE,   // Receiving HBM data into SPAD
    CH_WRITEBACK, // Writing SPAD data to HBM
    CH_DONE
  } ch_state_t;

  ch_state_t  ch_state [8];
  dma_desc_t  ch_desc  [8];
  logic [27:0] ch_bytes_remaining [8];
  logic [HBM_ADDR_W-1:0] ch_hbm_ptr [8];
  logic [SPAD_ADDR_W-1:0] ch_spad_ptr [8];

  // ── Descriptor loading ────────────────────────────────────
  assign desc_ready = (ch_state[desc_channel] == CH_IDLE);

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      for (int i = 0; i < 8; i++) begin
        ch_state[i]           = CH_IDLE;
        ch_desc[i]            = '0;
        ch_bytes_remaining[i] = '0;
        ch_done[i]            = 1'b0;
        ch_active[i]          = 1'b0;
      end
    end else begin
      // Load new descriptor
      if (desc_valid && ch_state[desc_channel] == CH_IDLE) begin
        ch_desc[desc_channel]            = desc_in;
        ch_bytes_remaining[desc_channel] = desc_in.byte_count;
        ch_hbm_ptr[desc_channel]         = desc_in.hbm_addr;
        ch_spad_ptr[desc_channel]        = desc_in.spad_addr;
        ch_state[desc_channel]           = CH_WAIT;
        ch_done[desc_channel]            = 1'b0;
        ch_active[desc_channel]          = 1'b1;
      end

      // Per-channel state progression
      for (int i = 0; i < 8; i++) begin
        unique case (ch_state[i])
          CH_IDLE: begin
            ch_active[i] = 1'b0;
            ch_done[i]   = 1'b0;
          end

          CH_WAIT: begin
            if (global_cycle >= ch_desc[i].fire_cycle)
              ch_state[i] = ch_desc[i].direction ? CH_WRITEBACK : CH_FETCH;
          end

          CH_FETCH: begin
            if (hbm_rd_ready && hbm_rd_valid)
              ch_state[i] = CH_RECEIVE;
          end

          CH_RECEIVE: begin
            if (hbm_rd_data_valid && spad_wr_ack) begin
              ch_spad_ptr[i]        = ch_spad_ptr[i] + (SPAD_DATA_W/8);
              ch_hbm_ptr[i]         = ch_hbm_ptr[i]  + (HBM_DATA_W/8);
              ch_bytes_remaining[i] = ch_bytes_remaining[i] - (SPAD_DATA_W/8);
              if (hbm_rd_last || ch_bytes_remaining[i] <= (SPAD_DATA_W/8))
                ch_state[i] = CH_DONE;
            end
          end

          CH_WRITEBACK: begin
            if (hbm_wr_ready && hbm_wr_valid) begin
              ch_spad_ptr[i]        = ch_spad_ptr[i] + (SPAD_DATA_W/8);
              ch_hbm_ptr[i]         = ch_hbm_ptr[i]  + (HBM_DATA_W/8);
              ch_bytes_remaining[i] = ch_bytes_remaining[i] - (SPAD_DATA_W/8);
              if (ch_bytes_remaining[i] <= (SPAD_DATA_W/8))
                ch_state[i] = CH_DONE;
            end
          end

          CH_DONE: begin
            ch_done[i]   = 1'b1;
            ch_active[i] = 1'b0;
            ch_state[i]  = CH_IDLE;
          end

          default: ch_state[i] = CH_IDLE;
        endcase
      end
    end
  end

  // ── HBM request arbitration (priority encoder across channels) ──
  logic [2:0] fetch_ch, wb_ch;
  logic fetch_req, wb_req;

  always_comb begin
    fetch_req = 1'b0; fetch_ch = '0;
    wb_req    = 1'b0; wb_ch    = '0;
    for (int i = 7; i >= 0; i--) begin
      if (ch_state[i] == CH_FETCH)    begin fetch_req = 1'b1; fetch_ch = i[2:0]; end
      if (ch_state[i] == CH_WRITEBACK) begin wb_req   = 1'b1; wb_ch    = i[2:0]; end
    end
  end

  // ── HBM read channel drive ────────────────────────────────
  assign hbm_rd_addr  = ch_hbm_ptr[fetch_ch];
  assign hbm_rd_len   = 8'hF;   // 16-beat burst
  assign hbm_rd_valid = fetch_req;

  // ── SPAD write from HBM data ──────────────────────────────
  assign spad_wr_addr = ch_spad_ptr[fetch_ch];
  assign spad_wr_data = hbm_rd_data;
  assign spad_wr_en   = hbm_rd_data_valid && (ch_state[fetch_ch] == CH_RECEIVE);

  // ── HBM write from SPAD ───────────────────────────────────
  assign spad_rd_addr = ch_spad_ptr[wb_ch];
  assign spad_rd_en   = wb_req && (ch_state[wb_ch] == CH_WRITEBACK);
  assign hbm_wr_addr  = ch_hbm_ptr[wb_ch];
  assign hbm_wr_data  = spad_rd_data;
  assign hbm_wr_valid = spad_rd_valid && wb_req;

endmodule
