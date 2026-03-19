// ============================================================
// APEX-1 — grad_accumulator.sv
// FP32 gradient accumulator for training.
// Reads BF16 gradient tiles from scratchpad, converts to FP32,
// accumulates across multiple backward passes, writes FP32
// gradient tensor back to scratchpad.
// 256 parallel FP32 accumulator lanes.
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module grad_accumulator (
  input  logic              clk,
  input  logic              rst_n,

  // Dispatch
  input  logic              op_valid,
  input  logic [23:0]       src_addr,    // BF16 gradient source in SPAD
  input  logic [15:0]       elem_count,
  output logic              done,

  // Scratchpad interface
  output logic [SPAD_ADDR_W-1:0] spad_rd_addr,
  output logic              spad_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_rd_data,   // 512-bit = 32 × BF16
  input  logic              spad_rd_valid,

  output logic [SPAD_ADDR_W-1:0] spad_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_wr_data,   // 512-bit = 16 × FP32
  output logic              spad_wr_en,

  // Clear accumulator (new training step)
  input  logic              accum_clear
);

  localparam int LANES = 16;   // FP32 lanes per cycle (512 bits / 32)
  localparam int BF16_LANES = 32; // BF16 per 512-bit read

  // ── FP32 accumulator register file ───────────────────────
  // 256 entries × 32-bit = 1 KB (fits in small SRAM)
  logic [31:0] accum_reg [256];

  // ── BF16 → FP32 conversion (extend mantissa) ─────────────
  function automatic logic [31:0] bf16_to_fp32(input logic [15:0] b);
    // BF16 is just FP32 with lower 16 mantissa bits zeroed
    return {b, 16'h0000};
  endfunction

  // ── FP32 adder (behavioral; synthesis maps to hard adder) ─
  function automatic logic [31:0] fp32_add(input logic [31:0] a, input logic [31:0] b);
    // Behavioral FP32 add — real implementation uses an IEEE 754 adder
    // For synthesis: replace with technology-mapped FP32 adder IP
    logic        sa, sb, sr;
    logic [7:0]  ea, eb, er;
    logic [23:0] ma, mb;
    logic [24:0] sum_mant;
    integer      exp_diff;

    sa = a[31]; sb = b[31];
    ea = a[30:23]; eb = b[30:23];
    ma = {1'b1, a[22:0]}; mb = {1'b1, b[22:0]};

    if (ea >= eb) begin
      exp_diff = ea - eb;
      mb = mb >> exp_diff;
      er = ea;
    end else begin
      exp_diff = eb - ea;
      ma = ma >> exp_diff;
      er = eb;
    end

    if (sa == sb) begin
      sum_mant = {1'b0, ma} + {1'b0, mb};
      sr = sa;
    end else begin
      if (ma >= mb) begin
        sum_mant = {1'b0, ma} - {1'b0, mb};
        sr = sa;
      end else begin
        sum_mant = {1'b0, mb} - {1'b0, ma};
        sr = sb;
      end
    end

    if (sum_mant[24]) begin
      sum_mant = sum_mant >> 1;
      er = er + 1;
    end

    return {sr, er, sum_mant[22:0]};
  endfunction

  // ── FSM ───────────────────────────────────────────────────
  typedef enum logic [2:0] {
    GA_IDLE, GA_READ, GA_ACCUM, GA_WRITE, GA_DONE
  } ga_state_t;

  ga_state_t state;
  logic [23:0] rd_ptr, wr_ptr;
  logic [15:0] elems_rem;
  logic [7:0]  accum_idx;

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      state      <= GA_IDLE;
      done       <= 1'b0;
      spad_rd_en <= 1'b0;
      spad_wr_en <= 1'b0;
      for (int i = 0; i < 256; i++) accum_reg[i] <= '0;
    end else begin
      done       <= 1'b0;
      spad_rd_en <= 1'b0;
      spad_wr_en <= 1'b0;

      // Clear accumulator on new training step
      if (accum_clear)
        for (int i = 0; i < 256; i++) accum_reg[i] <= '0;

      unique case (state)
        GA_IDLE: begin
          if (op_valid) begin
            rd_ptr    <= src_addr;
            wr_ptr    <= src_addr;   // Write back to same location (in-place)
            elems_rem <= elem_count;
            accum_idx <= '0;
            state     <= GA_READ;
          end
        end

        GA_READ: begin
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= rd_ptr;
          state        <= GA_ACCUM;
        end

        GA_ACCUM: begin
          if (spad_rd_valid) begin
            // Convert 32 BF16 values and accumulate (first 16 per cycle)
            for (int i = 0; i < LANES; i++) begin
              automatic logic [15:0] bf16_val = spad_rd_data[i*16 +: 16];
              automatic logic [31:0] fp32_val = bf16_to_fp32(bf16_val);
              automatic int idx = accum_idx * LANES + i;
              if (idx < 256)
                accum_reg[idx] <= fp32_add(accum_reg[idx], fp32_val);
            end
            rd_ptr    <= rd_ptr + (SPAD_DATA_W / 8);
            elems_rem <= (elems_rem > BF16_LANES) ? elems_rem - BF16_LANES : '0;
            accum_idx <= accum_idx + 1;
            state     <= (elems_rem <= BF16_LANES) ? GA_WRITE : GA_READ;
          end
        end

        GA_WRITE: begin
          // Write FP32 accumulated values back to SPAD (16 FP32 = 512 bits)
          spad_wr_en   <= 1'b1;
          spad_wr_addr <= wr_ptr;
          for (int i = 0; i < LANES; i++)
            spad_wr_data[i*32 +: 32] <= accum_reg[accum_idx * LANES + i < 256 ?
                                                   accum_idx * LANES + i : 0];
          wr_ptr    <= wr_ptr + (SPAD_DATA_W / 8);
          accum_idx <= accum_idx + 1;
          if (accum_idx >= (256 / LANES) - 1) state <= GA_DONE;
        end

        GA_DONE: begin
          done  <= 1'b1;
          state <= GA_IDLE;
        end

        default: state <= GA_IDLE;
      endcase
    end
  end

endmodule
