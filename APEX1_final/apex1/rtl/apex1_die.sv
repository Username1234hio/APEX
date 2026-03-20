// ============================================================
// APEX-1 — apex1_die.sv
// Top-level die integration.
// Instantiates:
//   - 4 × MXU clusters
//   - Global scratchpad controller
//   - DMA engine (8 channels)
//   - Static sequencer
//   - SFU (special function unit)
//   - Gradient accumulator
//   - All-reduce engine
//   - PCIe host interface
// ============================================================
import apex1_pkg::*;

module apex1_die #(
  parameter int DIE_ID = 0
)(
  input  logic              clk,
  input  logic              rst_n,

  // PCIe 5.0 x16 host interface
  input  logic [255:0]      pcie_rx_tdata,
  input  logic [31:0]       pcie_rx_tuser,
  input  logic              pcie_rx_tvalid,
  output logic              pcie_rx_tready,

  output logic [255:0]      pcie_tx_tdata,
  output logic [31:0]       pcie_tx_tuser,
  output logic              pcie_tx_tvalid,
  input  logic              pcie_tx_tready,

  // HBM3e interface (AXI4, simplified)
  output logic [HBM_ADDR_W-1:0]  hbm_rd_addr,
  output logic [7:0]        hbm_rd_len,
  output logic              hbm_rd_valid,
  input  logic              hbm_rd_ready,
  input  logic [HBM_DATA_W-1:0]  hbm_rd_data,
  input  logic              hbm_rd_last,
  input  logic              hbm_rd_data_valid,

  output logic [HBM_ADDR_W-1:0]  hbm_wr_addr,
  output logic [HBM_DATA_W-1:0]  hbm_wr_data,
  output logic              hbm_wr_valid,
  input  logic              hbm_wr_ready,

  // UCIe die-to-die links (TX to next, RX from prev in ring)
  output logic [SPAD_DATA_W-1:0] ucie_tx_data,
  output logic              ucie_tx_valid,
  input  logic              ucie_tx_ready,

  input  logic [SPAD_DATA_W-1:0] ucie_rx_data,
  input  logic              ucie_rx_valid,
  output logic              ucie_rx_ready,

  // Status outputs
  output logic              executing,
  output logic              seq_done
);

  // ── Internal signal declarations ──────────────────────────

  // Sequencer → clusters
  logic              mxu_op_valid  [CLUSTERS_PER_DIE];
  opcode_t           mxu_op_code   [CLUSTERS_PER_DIE];
  logic [23:0]       mxu_addr_a    [CLUSTERS_PER_DIE];
  logic [23:0]       mxu_addr_b    [CLUSTERS_PER_DIE];
  logic [23:0]       mxu_addr_c    [CLUSTERS_PER_DIE];
  logic [15:0]       mxu_dim_m     [CLUSTERS_PER_DIE];
  logic [15:0]       mxu_dim_n     [CLUSTERS_PER_DIE];
  logic [11:0]       mxu_dim_k     [CLUSTERS_PER_DIE];
  dtype_t            mxu_dtype     [CLUSTERS_PER_DIE];
  logic              mxu_sparse    [CLUSTERS_PER_DIE];
  logic              mxu_done      [CLUSTERS_PER_DIE];
  cluster_status_t   mxu_status    [CLUSTERS_PER_DIE];

  // Scratchpad ports (5 ports: 4 clusters + DMA)
  localparam int N_SPAD_PORTS = 5;

  logic [SPAD_ADDR_W-1:0] spad_rd_addr  [N_SPAD_PORTS];
  logic              spad_rd_en    [N_SPAD_PORTS];
  logic [SPAD_DATA_W-1:0] spad_rd_data  [N_SPAD_PORTS];
  logic              spad_rd_valid [N_SPAD_PORTS];

  logic [SPAD_ADDR_W-1:0] spad_wr_addr  [N_SPAD_PORTS];
  logic [SPAD_DATA_W-1:0] spad_wr_data  [N_SPAD_PORTS];
  logic              spad_wr_en    [N_SPAD_PORTS];
  logic              spad_wr_ack   [N_SPAD_PORTS];

  // SFU scratchpad (reuse port 4 shared with DMA — arbitrated)
  logic [SPAD_ADDR_W-1:0] sfu_rd_addr, sfu_wr_addr;
  logic [SPAD_DATA_W-1:0] sfu_rd_data, sfu_wr_data;
  logic              sfu_rd_en, sfu_rd_valid, sfu_wr_en;

  // DMA
  logic              dma_desc_valid;
  dma_desc_t         dma_desc;
  logic [2:0]        dma_ch_sel;
  logic              dma_desc_ready;
  logic [7:0]        dma_ch_done;
  logic [7:0]        dma_ch_active;

  // DMA scratchpad connections (port 4)
  logic [SPAD_ADDR_W-1:0] dma_spad_wr_addr, dma_spad_rd_addr;
  logic [SPAD_DATA_W-1:0] dma_spad_wr_data, dma_spad_rd_data;
  logic              dma_spad_wr_en, dma_spad_rd_en, dma_spad_rd_valid;

  // Sequencer
  logic              exec_start;
  logic [11:0]       exec_instr_count;
  logic              ibuf_wr_en;
  logic [127:0]      ibuf_wr_data;
  logic [11:0]       ibuf_wr_addr;
  logic              ibuf_ready;
  logic [31:0]       global_cycle;

  // SFU
  logic              sfu_op_valid, sfu_done;
  opcode_t           sfu_op_code;
  logic [23:0]       sfu_addr_a, sfu_addr_c;
  logic [15:0]       sfu_count;
  act_fn_t           sfu_act_fn;
  norm_fn_t          sfu_norm_fn;

  // Gradient accumulator
  logic              grad_valid, grad_done;
  logic [23:0]       grad_addr;
  logic [15:0]       grad_count;
  logic [SPAD_ADDR_W-1:0] grad_spad_rd_addr, grad_spad_wr_addr;
  logic [SPAD_DATA_W-1:0] grad_spad_rd_data, grad_spad_wr_data;
  logic              grad_spad_rd_en, grad_spad_rd_valid, grad_spad_wr_en;

  // All-reduce
  logic              ar_valid, ar_done;
  logic [23:0]       ar_addr;
  logic [15:0]       ar_count;
  reduce_topo_t      ar_topo;

  // Barrier (stub — all units always ready in this model)
  logic              all_barrier_req;
  logic all_barrier_ack;
  assign all_barrier_ack = all_barrier_req;

  // PCIe SPAD bridge
  logic [SPAD_ADDR_W-1:0] pcie_spad_wr_addr, pcie_spad_rd_addr;
  logic [SPAD_DATA_W-1:0] pcie_spad_wr_data, pcie_spad_rd_data;
  logic              pcie_spad_wr_en, pcie_spad_rd_en, pcie_spad_rd_valid;

  // ── PCIe host interface ───────────────────────────────────
  pcie_host_if u_pcie (
    .clk              (clk),
    .rst_n            (rst_n),
    .pcie_rx_tdata    (pcie_rx_tdata),
    .pcie_rx_tuser    (pcie_rx_tuser),
    .pcie_rx_tvalid   (pcie_rx_tvalid),
    .pcie_rx_tready   (pcie_rx_tready),
    .pcie_tx_tdata    (pcie_tx_tdata),
    .pcie_tx_tuser    (pcie_tx_tuser),
    .pcie_tx_tvalid   (pcie_tx_tvalid),
    .pcie_tx_tready   (pcie_tx_tready),
    .exec_start       (exec_start),
    .exec_instr_count (exec_instr_count),
    .seq_done         (seq_done),
    .executing        (executing),
    .ibuf_wr_en       (ibuf_wr_en),
    .ibuf_wr_data     (ibuf_wr_data),
    .ibuf_wr_addr     (ibuf_wr_addr),
    .ibuf_ready       (ibuf_ready),
    .spad_wr_addr     (pcie_spad_wr_addr),
    .spad_wr_data     (pcie_spad_wr_data),
    .spad_wr_en       (pcie_spad_wr_en),
    .spad_rd_addr     (pcie_spad_rd_addr),
    .spad_rd_en       (pcie_spad_rd_en),
    .spad_rd_data     (pcie_spad_rd_data),
    .spad_rd_valid    (pcie_spad_rd_valid)
  );

  // ── Static sequencer ──────────────────────────────────────
  static_sequencer u_seq (
    .clk              (clk),
    .rst_n            (rst_n),
    .ibuf_wr_en       (ibuf_wr_en),
    .ibuf_wr_data     (ibuf_wr_data),
    .ibuf_wr_addr     (ibuf_wr_addr),
    .ibuf_ready       (ibuf_ready),
    .exec_start       (exec_start),
    .exec_instr_count (exec_instr_count),
    .global_cycle     (global_cycle),
    .mxu_op_valid     (mxu_op_valid),
    .mxu_op_code      (mxu_op_code),
    .mxu_addr_a       (mxu_addr_a),
    .mxu_addr_b       (mxu_addr_b),
    .mxu_addr_c       (mxu_addr_c),
    .mxu_dim_m        (mxu_dim_m),
    .mxu_dim_n        (mxu_dim_n),
    .mxu_dim_k        (mxu_dim_k),
    .mxu_dtype        (mxu_dtype),
    .mxu_sparse       (mxu_sparse),
    .mxu_done         (mxu_done),
    .mxu_status       (mxu_status),
    .sfu_op_valid     (sfu_op_valid),
    .sfu_op_code      (sfu_op_code),
    .sfu_addr_a       (sfu_addr_a),
    .sfu_addr_c       (sfu_addr_c),
    .sfu_count        (sfu_count),
    .sfu_act_fn       (sfu_act_fn),
    .sfu_norm_fn      (sfu_norm_fn),
    .sfu_done         (sfu_done),
    .dma_desc_valid   (dma_desc_valid),
    .dma_desc         (dma_desc),
    .dma_ch_sel       (dma_ch_sel),
    .dma_desc_ready   (dma_desc_ready),
    .dma_ch_done      (dma_ch_done),
    .grad_valid       (grad_valid),
    .grad_addr        (grad_addr),
    .grad_count       (grad_count),
    .grad_done        (grad_done),
    .ar_valid         (ar_valid),
    .ar_addr          (ar_addr),
    .ar_count         (ar_count),
    .ar_topo          (ar_topo),
    .ar_done          (ar_done),
    .all_barrier_req  (all_barrier_req),
    .all_barrier_ack  (all_barrier_ack),
    .executing        (executing),
    .seq_done         (seq_done)
  );

  // ── MXU clusters ──────────────────────────────────────────
  generate
    for (genvar c = 0; c < CLUSTERS_PER_DIE; c++) begin : gen_clusters
      mxu_cluster #(
        .CLUSTER_ID(c)
      ) u_cluster (
        .clk          (clk),
        .rst_n        (rst_n),
        .op_valid     (mxu_op_valid[c]),
        .op_code      (mxu_op_code[c]),
        .op_addr_a    (mxu_addr_a[c]),
        .op_addr_b    (mxu_addr_b[c]),
        .op_addr_c    (mxu_addr_c[c]),
        .op_dim_m     (mxu_dim_m[c]),
        .op_dim_n     (mxu_dim_n[c]),
        .op_dim_k     (mxu_dim_k[c]),
        .op_dtype     (mxu_dtype[c]),
        .op_sparse    (mxu_sparse[c]),
        .spad_rd_addr (spad_rd_addr[c]),
        .spad_rd_en   (spad_rd_en[c]),
        .spad_rd_data (spad_rd_data[c]),
        .spad_rd_valid(spad_rd_valid[c]),
        .spad_wr_addr (spad_wr_addr[c]),
        .spad_wr_data (spad_wr_data[c]),
        .spad_wr_en   (spad_wr_en[c]),
        .cluster_en   (1'b1),
        .status       (mxu_status[c]),
        .done         (mxu_done[c])
      );
    end
  endgenerate

  // ── SFU ───────────────────────────────────────────────────
  sfu u_sfu (
    .clk          (clk),
    .rst_n        (rst_n),
    .op_valid     (sfu_op_valid),
    .op_code      (sfu_op_code),
    .addr_a       (sfu_addr_a),
    .addr_c       (sfu_addr_c),
    .elem_count   (sfu_count),
    .act_fn       (sfu_act_fn),
    .norm_fn      (sfu_norm_fn),
    .scalar_in    (16'h0),
    .done         (sfu_done),
    .spad_rd_addr (sfu_rd_addr),
    .spad_rd_en   (sfu_rd_en),
    .spad_rd_data (sfu_rd_data),
    .spad_rd_valid(sfu_rd_valid),
    .spad_wr_addr (sfu_wr_addr),
    .spad_wr_data (sfu_wr_data),
    .spad_wr_en   (sfu_wr_en)
  );

  // ── Gradient accumulator ──────────────────────────────────
  grad_accumulator u_grad (
    .clk          (clk),
    .rst_n        (rst_n),
    .op_valid     (grad_valid),
    .src_addr     (grad_addr),
    .elem_count   (grad_count),
    .done         (grad_done),
    .spad_rd_addr (grad_spad_rd_addr),
    .spad_rd_en   (grad_spad_rd_en),
    .spad_rd_data (grad_spad_rd_data),
    .spad_rd_valid(grad_spad_rd_valid),
    .spad_wr_addr (grad_spad_wr_addr),
    .spad_wr_data (grad_spad_wr_data),
    .spad_wr_en   (grad_spad_wr_en),
    .accum_clear  (exec_start)
  );

  // ── All-reduce engine ─────────────────────────────────────
  allreduce_engine #(.DIE_ID(DIE_ID)) u_ar (
    .clk          (clk),
    .rst_n        (rst_n),
    .op_valid     (ar_valid),
    .src_addr     (ar_addr),
    .elem_count   (ar_count),
    .topology     (ar_topo),
    .done         (ar_done),
    .spad_rd_addr (spad_rd_addr[4]),
    .spad_rd_en   (spad_rd_en[4]),
    .spad_rd_data (spad_rd_data[4]),
    .spad_rd_valid(spad_rd_valid[4]),
    .spad_wr_addr (spad_wr_addr[4]),
    .spad_wr_data (spad_wr_data[4]),
    .spad_wr_en   (spad_wr_en[4]),
    .ucie_tx_data (ucie_tx_data),
    .ucie_tx_valid(ucie_tx_valid),
    .ucie_tx_ready(ucie_tx_ready),
    .ucie_rx_data (ucie_rx_data),
    .ucie_rx_valid(ucie_rx_valid),
    .ucie_rx_ready(ucie_rx_ready)
  );

  // ── DMA engine ────────────────────────────────────────────
  dma_engine u_dma (
    .clk              (clk),
    .rst_n            (rst_n),
    .global_cycle     (global_cycle),
    .desc_valid       (dma_desc_valid),
    .desc_in          (dma_desc),
    .desc_channel     (dma_ch_sel),
    .desc_ready       (dma_desc_ready),
    .hbm_rd_addr      (hbm_rd_addr),
    .hbm_rd_len       (hbm_rd_len),
    .hbm_rd_valid     (hbm_rd_valid),
    .hbm_rd_ready     (hbm_rd_ready),
    .hbm_rd_data      (hbm_rd_data),
    .hbm_rd_last      (hbm_rd_last),
    .hbm_rd_data_valid(hbm_rd_data_valid),
    .hbm_wr_addr      (hbm_wr_addr),
    .hbm_wr_data      (hbm_wr_data),
    .hbm_wr_valid     (hbm_wr_valid),
    .hbm_wr_ready     (hbm_wr_ready),
    .spad_wr_addr     (dma_spad_wr_addr),
    .spad_wr_data     (dma_spad_wr_data),
    .spad_wr_en       (dma_spad_wr_en),
    .spad_wr_ack      (spad_wr_ack[4]),
    .spad_rd_addr     (dma_spad_rd_addr),
    .spad_rd_en       (dma_spad_rd_en),
    .spad_rd_data     (dma_spad_rd_data),
    .spad_rd_valid    (dma_spad_rd_valid),
    .ch_done          (dma_ch_done),
    .ch_active        (dma_ch_active)
  );

  // ── Scratchpad port 4 mux (DMA / all-reduce / PCIe / grad / SFU) ──
  // Priority: DMA > all-reduce > PCIe > grad > SFU
  // Simple combinational mux for behavioral model
  always_comb begin
    if (dma_spad_wr_en || dma_spad_rd_en) begin
      spad_rd_addr[4]   = dma_spad_rd_addr;
      spad_rd_en[4]     = dma_spad_rd_en;
      dma_spad_rd_data  = spad_rd_data[4];
      dma_spad_rd_valid = spad_rd_valid[4];
      spad_wr_addr[4]   = dma_spad_wr_addr;
      spad_wr_data[4]   = dma_spad_wr_data;
      spad_wr_en[4]     = dma_spad_wr_en;
      // Unused ports
      sfu_rd_data       = '0;
      sfu_rd_valid      = 1'b0;
      pcie_spad_rd_data  = '0;
      pcie_spad_rd_valid = 1'b0;
      grad_spad_rd_data  = '0;
      grad_spad_rd_valid = 1'b0;
    end else if (pcie_spad_wr_en || pcie_spad_rd_en) begin
      spad_rd_addr[4]    = pcie_spad_rd_addr;
      spad_rd_en[4]      = pcie_spad_rd_en;
      pcie_spad_rd_data  = spad_rd_data[4];
      pcie_spad_rd_valid = spad_rd_valid[4];
      spad_wr_addr[4]    = pcie_spad_wr_addr;
      spad_wr_data[4]    = pcie_spad_wr_data;
      spad_wr_en[4]      = pcie_spad_wr_en;
      dma_spad_rd_data   = '0;
      dma_spad_rd_valid  = 1'b0;
      sfu_rd_data        = '0;
      sfu_rd_valid       = 1'b0;
      grad_spad_rd_data  = '0;
      grad_spad_rd_valid = 1'b0;
    end else begin
      // SFU / grad share when neither DMA nor PCIe active
      spad_rd_addr[4]    = sfu_rd_en ? sfu_rd_addr : grad_spad_rd_addr;
      spad_rd_en[4]      = sfu_rd_en | grad_spad_rd_en;
      sfu_rd_data        = spad_rd_data[4];
      sfu_rd_valid       = sfu_rd_en ? spad_rd_valid[4] : 1'b0;
      grad_spad_rd_data  = spad_rd_data[4];
      grad_spad_rd_valid = grad_spad_rd_en ? spad_rd_valid[4] : 1'b0;
      spad_wr_addr[4]    = sfu_wr_en ? sfu_wr_addr : grad_spad_wr_addr;
      spad_wr_data[4]    = sfu_wr_en ? sfu_wr_data : grad_spad_wr_data;
      spad_wr_en[4]      = sfu_wr_en | grad_spad_wr_en;
      dma_spad_rd_data   = '0;
      dma_spad_rd_valid  = 1'b0;
      pcie_spad_rd_data  = '0;
      pcie_spad_rd_valid = 1'b0;
    end
  end

  // ── Scratchpad controller ─────────────────────────────────
  spad_controller #(
    .N_PORTS(N_SPAD_PORTS)
  ) u_spad (
    .clk      (clk),
    .rst_n    (rst_n),
    .rd_addr  (spad_rd_addr),
    .rd_en    (spad_rd_en),
    .rd_data  (spad_rd_data),
    .rd_valid (spad_rd_valid),
    .wr_addr  (spad_wr_addr),
    .wr_data  (spad_wr_data),
    .wr_en    (spad_wr_en),
    .wr_ack   (spad_wr_ack)
  );

endmodule
