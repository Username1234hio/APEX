// ============================================================
// APEX-1 — pcie_host_if.sv
// PCIe 5.0 x16 host interface (simplified TLP model).
// Handles:
//   - Host → chip: instruction stream DMA load
//   - Host → chip: scratchpad writes (input tensors)
//   - Chip → host: scratchpad reads (output tensors)
//   - Control register access (start/stop/status)
// In real silicon: this module interfaces with a PCIe hard IP
// (e.g., Synopsys DesignWare PCIe Gen5 controller).
// ============================================================
import apex1_pkg::*;

module pcie_host_if (
  input  logic              clk,
  input  logic              rst_n,

  // PCIe TLP interface (simplified AXI-Stream from PCIe hard IP)
  input  logic [255:0]      pcie_rx_tdata,    // 256-bit TLP data
  input  logic [31:0]       pcie_rx_tuser,    // TLP header info
  input  logic              pcie_rx_tvalid,
  output logic              pcie_rx_tready,

  output logic [255:0]      pcie_tx_tdata,
  output logic [31:0]       pcie_tx_tuser,
  output logic              pcie_tx_tvalid,
  input  logic              pcie_tx_tready,

  // Control registers (BAR0 mapped)
  output logic              exec_start,       // Pulse to start execution
  output logic [11:0]       exec_instr_count,
  input  logic              seq_done,
  input  logic              executing,

  // Instruction buffer write interface
  output logic              ibuf_wr_en,
  output logic [127:0]      ibuf_wr_data,
  output logic [11:0]       ibuf_wr_addr,
  input  logic              ibuf_ready,

  // Scratchpad DMA write (host tensors → SPAD)
  output logic [SPAD_ADDR_W-1:0] spad_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_wr_data,
  output logic              spad_wr_en,

  // Scratchpad DMA read (SPAD → host)
  output logic [SPAD_ADDR_W-1:0] spad_rd_addr,
  output logic              spad_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_rd_data,
  input  logic              spad_rd_valid
);

  // ── Control register map (BAR0) ───────────────────────────
  // Offset 0x00: CTRL — bit[0]=exec_start, bit[1]=reset
  // Offset 0x04: INSTR_COUNT — number of instructions to execute
  // Offset 0x08: STATUS — bit[0]=executing, bit[1]=done
  // Offset 0x0C: SPAD_WR_ADDR — scratchpad target address
  // Offset 0x10: HBM_ADDR_LO — HBM source address [31:0]
  // Offset 0x14: HBM_ADDR_HI — HBM source address [36:32]

  // ── TLP type decode (simplified) ─────────────────────────
  // TLP type in pcie_rx_tuser[7:0]:
  //   0x00 = MRd (memory read)
  //   0x40 = MWr (memory write)
  //   0x05 = CplD (completion with data)

  typedef enum logic [2:0] {
    PCIE_IDLE,
    PCIE_IBUF_WRITE,
    PCIE_SPAD_WRITE,
    PCIE_SPAD_READ,
    PCIE_CREG_WRITE,
    PCIE_COMPLETE
  } pcie_state_t;

  pcie_state_t pcie_state;

  // TLP header fields
  logic [63:0]  tlp_addr;
  logic [9:0]   tlp_len;     // DWORDs
  logic [7:0]   tlp_type;
  logic [7:0]   tlp_tag;
  logic [15:0]  tlp_req_id;

  // Internal write pointer for multi-beat writes
  logic [11:0]  wr_beat;
  logic [27:0]  spad_wr_ptr;

  always_comb begin
    tlp_type   = pcie_rx_tuser[7:0];
    tlp_len    = {pcie_rx_tdata[9:0]};
    tlp_addr   = {pcie_rx_tdata[95:64], pcie_rx_tdata[127:96]};  // 64-bit address TLP
    tlp_tag    = pcie_rx_tdata[47:40];
    tlp_req_id = pcie_rx_tdata[63:48];
  end

  // ── Address decode ────────────────────────────────────────
  // BAR0: 0x0000_0000 – 0x0000_FFFF = Control registers
  // BAR1: 0x0001_0000 – 0x0010_FFFF = Instruction buffer
  // BAR2: 0x0100_0000 – 0x1100_FFFF = Scratchpad DMA window
  logic is_creg, is_ibuf, is_spad;
  assign is_creg = (tlp_addr[31:16] == 16'h0000);
  assign is_ibuf = (tlp_addr[31:16] == 16'h0001);
  assign is_spad = (tlp_addr[31:24] >= 8'h01);

  // ── FSM ───────────────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      pcie_state      <= PCIE_IDLE;
      pcie_rx_tready  <= 1'b1;
      exec_start      <= 1'b0;
      exec_instr_count <= '0;
      ibuf_wr_en      <= 1'b0;
      spad_wr_en      <= 1'b0;
      spad_rd_en      <= 1'b0;
      pcie_tx_tvalid  <= 1'b0;
      wr_beat         <= '0;
      spad_wr_ptr     <= '0;
    end else begin
      exec_start  <= 1'b0;
      ibuf_wr_en  <= 1'b0;
      spad_wr_en  <= 1'b0;
      spad_rd_en  <= 1'b0;
      pcie_tx_tvalid <= 1'b0;

      unique case (pcie_state)
        PCIE_IDLE: begin
          pcie_rx_tready <= 1'b1;
          if (pcie_rx_tvalid) begin
            if (tlp_type == 8'h40) begin  // MWr
              if (is_creg)       pcie_state <= PCIE_CREG_WRITE;
              else if (is_ibuf)  pcie_state <= PCIE_IBUF_WRITE;
              else if (is_spad)  begin
                spad_wr_ptr <= tlp_addr[27:0];
                pcie_state  <= PCIE_SPAD_WRITE;
              end
            end else if (tlp_type == 8'h00) begin  // MRd
              if (is_spad) begin
                spad_rd_addr <= tlp_addr[27:0];
                pcie_state   <= PCIE_SPAD_READ;
              end
            end
          end
        end

        PCIE_CREG_WRITE: begin
          // Parse control register write from TLP data payload
          case (tlp_addr[7:0])
            8'h00: begin  // CTRL register
              if (pcie_rx_tdata[160])  // bit 0 of payload DWORD
                exec_start <= 1'b1;
            end
            8'h04: exec_instr_count <= pcie_rx_tdata[171:160];
            default: ;
          endcase
          pcie_state <= PCIE_IDLE;
        end

        PCIE_IBUF_WRITE: begin
          // Write 128-bit instruction (256-bit TLP beat = 2 instructions)
          if (pcie_rx_tvalid && ibuf_ready) begin
            ibuf_wr_en   <= 1'b1;
            ibuf_wr_addr <= tlp_addr[13:2] + wr_beat;  // 4-byte aligned
            ibuf_wr_data <= pcie_rx_tdata[127:0];       // First instruction
            wr_beat      <= wr_beat + 1;
            if (wr_beat >= tlp_len - 1) begin
              wr_beat    <= '0;
              pcie_state <= PCIE_IDLE;
            end
          end
        end

        PCIE_SPAD_WRITE: begin
          // Burst write to scratchpad
          if (pcie_rx_tvalid) begin
            spad_wr_en   <= 1'b1;
            spad_wr_addr <= spad_wr_ptr[SPAD_ADDR_W-1:0];
            spad_wr_data <= {pcie_rx_tdata, pcie_rx_tdata};  // Replicate to 512b
            spad_wr_ptr  <= spad_wr_ptr + 32;  // 256-bit = 32 bytes per beat
            wr_beat      <= wr_beat + 1;
            if (wr_beat >= tlp_len - 1) begin
              wr_beat    <= '0;
              pcie_state <= PCIE_IDLE;
            end
          end
        end

        PCIE_SPAD_READ: begin
          spad_rd_en <= 1'b1;
          if (spad_rd_valid) begin
            // Return as CplD TLP
            pcie_tx_tvalid <= 1'b1;
            pcie_tx_tdata  <= spad_rd_data[255:0];  // First 256 bits
            pcie_tx_tuser  <= {8'h0, tlp_tag, tlp_req_id};
            pcie_state     <= PCIE_IDLE;
          end
        end

        default: pcie_state <= PCIE_IDLE;
      endcase
    end
  end

endmodule
