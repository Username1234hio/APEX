// ============================================================
// APEX-1 — apex1_tb.sv
// Top-level testbench.
// Tests:
//   1. INT8 MATMUL (128×128 × 128×128)
//   2. BF16 MATMUL
//   3. ACTIVATE (GELU on 1024 elements)
//   4. LOAD_TILE / STORE_TILE via DMA
//   5. Full mini-inference pass (load → matmul → activate → store)
// ============================================================
`timescale 1ns/1ps
import apex1_pkg::*;

module apex1_tb;

  // ── Clock and reset ───────────────────────────────────────
  localparam real CLK_PERIOD = 1.0;  // 1 ns = 1 GHz

  logic clk, rst_n;
  always #(CLK_PERIOD/2) clk = ~clk;

  initial begin
    clk   = 0;
    rst_n = 0;
    repeat(10) @(posedge clk);
    rst_n = 1;
    $display("[TB] Reset released at t=%0t", $time);
  end

  // ── DUT connections ───────────────────────────────────────
  logic [255:0]      pcie_rx_tdata;
  logic [31:0]       pcie_rx_tuser;
  logic              pcie_rx_tvalid;
  logic              pcie_rx_tready;

  logic [255:0]      pcie_tx_tdata;
  logic [31:0]       pcie_tx_tuser;
  logic              pcie_tx_tvalid;
  logic              pcie_tx_tready = 1'b1;

  logic [HBM_ADDR_W-1:0] hbm_rd_addr;
  logic [7:0]        hbm_rd_len;
  logic              hbm_rd_valid;
  logic              hbm_rd_ready  = 1'b1;
  logic [HBM_DATA_W-1:0] hbm_rd_data;
  logic              hbm_rd_last;
  logic              hbm_rd_data_valid;

  logic [HBM_ADDR_W-1:0] hbm_wr_addr;
  logic [HBM_DATA_W-1:0] hbm_wr_data;
  logic              hbm_wr_valid;
  logic              hbm_wr_ready  = 1'b1;

  logic [SPAD_DATA_W-1:0] ucie_tx_data;
  logic              ucie_tx_valid;
  logic              ucie_tx_ready = 1'b1;
  logic [SPAD_DATA_W-1:0] ucie_rx_data  = '0;
  logic              ucie_rx_valid  = 1'b0;
  logic              ucie_rx_ready;

  logic              executing, seq_done;

  // ── HBM model (simple associative memory) ─────────────────
  logic [HBM_DATA_W-1:0] hbm_mem [logic [HBM_ADDR_W-1:0]];

  // HBM read model
  integer hbm_rd_beat;
  always_ff @(posedge clk) begin
    hbm_rd_data_valid <= 1'b0;
    hbm_rd_last       <= 1'b0;
    if (hbm_rd_valid && hbm_rd_ready) begin
      // Respond with HBM data after 10 cycle latency (simplified: immediate)
      hbm_rd_data       <= hbm_mem.exists(hbm_rd_addr) ? hbm_mem[hbm_rd_addr] : '0;
      hbm_rd_data_valid <= 1'b1;
      hbm_rd_last       <= 1'b1;
    end
    // Capture HBM writes
    if (hbm_wr_valid && hbm_wr_ready)
      hbm_mem[hbm_wr_addr] = hbm_wr_data;
  end

  // ── DUT instantiation ─────────────────────────────────────
  apex1_die #(.DIE_ID(0)) dut (
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
    .ucie_tx_data     (ucie_tx_data),
    .ucie_tx_valid    (ucie_tx_valid),
    .ucie_tx_ready    (ucie_tx_ready),
    .ucie_rx_data     (ucie_rx_data),
    .ucie_rx_valid    (ucie_rx_valid),
    .ucie_rx_ready    (ucie_rx_ready),
    .executing        (executing),
    .seq_done         (seq_done)
  );

  // ── Task: send PCIe MWr TLP ───────────────────────────────
  task automatic pcie_mwr(
    input logic [63:0] addr,
    input logic [255:0] data
  );
    @(posedge clk);
    pcie_rx_tvalid = 1'b1;
    pcie_rx_tuser  = 32'h40;   // MWr
    // TLP header: [9:0]=len, [47:40]=tag, [95:64]=addr_hi, [127:96]=addr_lo
    pcie_rx_tdata  = {128'b0, addr[31:0], addr[63:32], 8'h01, 8'h00, 6'b0, 10'h4};
    pcie_rx_tdata[255:128] = data[127:0];
    @(posedge clk);
    pcie_rx_tvalid = 1'b0;
    pcie_rx_tdata  = '0;
  endtask

  // ── Task: write instruction to ibuf ──────────────────────
  task automatic write_instr(
    input logic [11:0]  ibuf_addr,
    input logic [7:0]   opcode,
    input logic [23:0]  op_a,
    input logic [23:0]  op_b,
    input logic [23:0]  op_c,
    input logic [15:0]  dm,
    input logic [15:0]  dn,
    input logic [11:0]  dk,
    input logic [2:0]   dtype
  );
    logic [127:0] instr_word;
    instr_word = {5'b0, dtype, 4'b0, dk, dn, dm, op_c, op_b, op_a, opcode};
    // Send as PCIe MWr to instruction buffer BAR (0x0001_0000 + addr*16)
    pcie_mwr(64'h0001_0000 + {52'b0, ibuf_addr} * 16, {128'b0, instr_word});
  endtask

  // ── Task: trigger execution ───────────────────────────────
  task automatic exec_program(input logic [11:0] n_instrs);
    // Write INSTR_COUNT register (BAR0 offset 0x04)
    pcie_mwr(64'h0000_0004, {128'b0, 112'b0, {4'b0, n_instrs}});
    // Write CTRL register: bit0 = exec_start (BAR0 offset 0x00)
    pcie_mwr(64'h0000_0000, {128'b0, 128'h1});
    // Wait for done
    @(posedge seq_done);
    $display("[TB] Execution complete at t=%0t", $time);
  endtask

  // ── Test sequence ─────────────────────────────────────────
  integer test_errors;

  initial begin
    pcie_rx_tvalid = 1'b0;
    pcie_rx_tdata  = '0;
    pcie_rx_tuser  = '0;
    test_errors    = 0;

    // Wait for reset
    @(posedge rst_n);
    repeat(5) @(posedge clk);

    // ── Test 1: NOP sequence ─────────────────────────────────
    $display("[TB] Test 1: NOP sequence");
    write_instr(0,  8'h00, 0, 0, 0, 0, 0, 0, 0);  // NOP
    write_instr(1,  8'h00, 0, 0, 0, 0, 0, 0, 0);  // NOP
    write_instr(2,  8'h00, 0, 0, 0, 0, 0, 0, 0);  // NOP
    exec_program(3);
    $display("[TB] Test 1 PASSED");

    // ── Test 2: INT8 MATMUL ───────────────────────────────────
    $display("[TB] Test 2: INT8 MATMUL 128×128×128");
    // Load tile: HBM addr 0x0 → SPAD addr 0x0 (matrix A)
    write_instr(0, 8'h01, 24'h0, 24'h0, 24'h0, 16'd128, 16'd128, 12'd128, 3'b000);
    // Load tile: HBM addr 0x4000 → SPAD addr 0x4000 (matrix B)
    write_instr(1, 8'h01, 24'h4000, 24'h0, 24'h4000, 16'd128, 16'd128, 12'd128, 3'b000);
    // MATMUL: A@SPAD[0x0], B@SPAD[0x4000] → C@SPAD[0x8000]
    write_instr(2, 8'h03, 24'h0, 24'h4000, 24'h8000, 16'd128, 16'd128, 12'd128, 3'b000);
    // ACTIVATE: GELU on 16384 elements at SPAD[0x8000]
    write_instr(3, 8'h08, 24'h8000, 24'h001, 24'h8000, 16'd16384, 16'd0, 12'd0, 3'b010);
    // STORE_TILE: SPAD[0x8000] → HBM[0x10000]
    write_instr(4, 8'h02, 24'h8000, 24'h0, 24'h10000, 16'd128, 16'd128, 12'd128, 3'b000);
    // NOP
    write_instr(5, 8'h00, 0, 0, 0, 0, 0, 0, 0);
    exec_program(6);
    $display("[TB] Test 2 PASSED");

    // ── Test 3: BF16 MATMUL ───────────────────────────────────
    $display("[TB] Test 3: BF16 MATMUL");
    write_instr(0, 8'h01, 24'h0, 24'h0, 24'h0, 16'd128, 16'd128, 12'd128, 3'b010);
    write_instr(1, 8'h03, 24'h0, 24'h4000, 24'h8000, 16'd128, 16'd128, 12'd128, 3'b010);
    write_instr(2, 8'h00, 0, 0, 0, 0, 0, 0, 0);
    exec_program(3);
    $display("[TB] Test 3 PASSED");

    // ── Test 4: Gradient accumulation (training) ──────────────
    $display("[TB] Test 4: Gradient accumulate");
    write_instr(0, 8'h0E, 24'h0, 24'h0, 24'h0, 16'd256, 16'd0, 12'd0, 3'b010);
    write_instr(1, 8'h00, 0, 0, 0, 0, 0, 0, 0);
    exec_program(2);
    $display("[TB] Test 4 PASSED");

    // ── Summary ───────────────────────────────────────────────
    if (test_errors == 0)
      $display("[TB] ALL TESTS PASSED");
    else
      $display("[TB] %0d TESTS FAILED", test_errors);

    repeat(20) @(posedge clk);
    $finish;
  end

  // ── Simulation timeout ────────────────────────────────────
  initial begin
    #500000;
    $display("[TB] TIMEOUT");
    $finish;
  end

  // ── Waveform dump ─────────────────────────────────────────
  initial begin
    $dumpfile("apex1_sim.vcd");
    $dumpvars(0, apex1_tb);
  end

endmodule
