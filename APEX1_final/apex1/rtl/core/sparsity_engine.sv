// ============================================================
// APEX-1 — sparsity_engine.sv
// 2:4 Structured Sparsity Engine
//
// In 2:4 sparsity: every group of 4 consecutive weights has
// exactly 2 non-zero values. The compressed format stores:
//   - Compressed weight buffer: 50% of original size
//   - 2-bit index mask per group: which 2 of 4 positions are NZ
//
// This engine decompresses on-the-fly and feeds the systolic
// array, effectively doubling throughput vs dense INT8.
//
// Compression format (per 4-element group):
//   [31:16] = two 8-bit non-zero weights (w0, w1)
//   [15: 8] = 4-bit index of w0 (0–3) + 4-bit index of w1
//   [ 7: 0] = reserved / metadata
// ============================================================
import apex1_pkg::*;

module sparsity_engine #(
  parameter int COLS = ARRAY_COLS   // 128 — output width matches array
)(
  input  logic              clk,
  input  logic              rst_n,

  // Control
  input  logic              op_valid,
  input  logic [23:0]       sparse_wgt_addr,   // Compressed weight SPAD addr
  input  logic [23:0]       mask_addr,         // Index mask SPAD addr
  input  logic [23:0]       act_addr,          // Dense activation SPAD addr
  input  logic [23:0]       out_addr,          // Output SPAD addr
  input  logic [15:0]       dim_m,             // Output rows
  input  logic [15:0]       dim_n,             // Output cols
  input  logic [11:0]       dim_k,             // Inner dimension (dense)
  input  dtype_t            dtype,
  output logic              done,

  // Scratchpad read (compressed weights)
  output logic [SPAD_ADDR_W-1:0] spad_wgt_rd_addr,
  output logic              spad_wgt_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_wgt_rd_data,
  input  logic              spad_wgt_rd_valid,

  // Scratchpad read (index masks)
  output logic [SPAD_ADDR_W-1:0] spad_mask_rd_addr,
  output logic              spad_mask_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_mask_rd_data,
  input  logic              spad_mask_rd_valid,

  // Scratchpad read (dense activations)
  output logic [SPAD_ADDR_W-1:0] spad_act_rd_addr,
  output logic              spad_act_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_act_rd_data,
  input  logic              spad_act_rd_valid,

  // Scratchpad write (output)
  output logic [SPAD_ADDR_W-1:0] spad_out_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_out_wr_data,
  output logic              spad_out_wr_en,

  // Decompressed weight output → systolic array
  // (feeds weight_load_en / weight_col_data of the attached array)
  output logic              arr_weight_load_en,
  output logic [COLS*16-1:0] arr_weight_col_data,
  output logic [$clog2(COLS)-1:0] arr_weight_col_idx
);

  // ── Decompressor pipeline ─────────────────────────────────
  // One 512-bit SPAD read gives us:
  //   - 16 compressed groups (each group = 32 bits: 2 weights + mask)
  //   - Each group expands to 4 weight positions (2 NZ, 2 zero)
  //   - Output: 64 weight values (16-bit each) = 1024 bits
  //   (We process in two passes to fit 512-bit bus)

  localparam int GROUPS_PER_READ = SPAD_DATA_W / 32;  // 16 groups per 512b read

  // Decompressed weight buffer: holds one full column (128 × 16-bit)
  logic [15:0] decomp_col [COLS];

  // ── State machine ─────────────────────────────────────────
  typedef enum logic [2:0] {
    SP_IDLE,
    SP_LOAD_MASK,
    SP_LOAD_WGT,
    SP_DECOMPRESS,
    SP_ISSUE_COL,
    SP_DONE
  } sp_state_t;

  sp_state_t state;

  logic [15:0]  col_idx;      // Current weight column being processed
  logic [11:0]  k_idx;        // Current K dimension index
  logic [23:0]  wgt_ptr, mask_ptr, act_ptr, out_ptr;

  // Captured SPAD reads
  logic [SPAD_DATA_W-1:0] mask_buf, wgt_buf;
  logic [7:0]  group_idx;     // Which of 16 groups we are expanding

  // ── Decompression logic ────────────────────────────────────
  // Expand one 32-bit compressed group to 4 × 16-bit weight slots
  // Group format: [31:16]=w1,w0  [15:12]=idx1  [11:8]=idx0  [7:0]=reserved
  function automatic void decompress_group(
    input  logic [31:0] group,
    input  int          base_col,   // Which 4 columns this group covers
    ref    logic [15:0] out_col [COLS]
  );
    logic [7:0]  w0, w1;
    logic [3:0]  idx0, idx1;
    w0   = group[7:0];
    w1   = group[15:8];
    idx0 = group[19:16];
    idx1 = group[23:20];
    // Clear all 4 slots in this group
    out_col[base_col + 0] = 16'h0;
    out_col[base_col + 1] = 16'h0;
    out_col[base_col + 2] = 16'h0;
    out_col[base_col + 3] = 16'h0;
    // Place non-zero weights at their indexed positions
    out_col[base_col + idx0] = {8'h0, w0};
    out_col[base_col + idx1] = {8'h0, w1};
  endfunction

  // ── Main FSM ──────────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      state              <= SP_IDLE;
      done               <= 1'b0;
      arr_weight_load_en <= 1'b0;
      spad_wgt_rd_en     <= 1'b0;
      spad_mask_rd_en    <= 1'b0;
      spad_act_rd_en     <= 1'b0;
      spad_out_wr_en     <= 1'b0;
      col_idx            <= '0;
      k_idx              <= '0;
      group_idx          <= '0;
    end else begin
      done               <= 1'b0;
      arr_weight_load_en <= 1'b0;
      spad_wgt_rd_en     <= 1'b0;
      spad_mask_rd_en    <= 1'b0;
      spad_act_rd_en     <= 1'b0;
      spad_out_wr_en     <= 1'b0;

      unique case (state)
        SP_IDLE: begin
          if (op_valid) begin
            wgt_ptr  <= sparse_wgt_addr;
            mask_ptr <= mask_addr;
            act_ptr  <= act_addr;
            out_ptr  <= out_addr;
            col_idx  <= '0;
            k_idx    <= '0;
            state    <= SP_LOAD_MASK;
          end
        end

        SP_LOAD_MASK: begin
          // Read index mask for this group of 16 columns
          spad_mask_rd_en   <= 1'b1;
          spad_mask_rd_addr <= mask_ptr;
          if (spad_mask_rd_valid) begin
            mask_buf  <= spad_mask_rd_data;
            mask_ptr  <= mask_ptr + (SPAD_DATA_W/8);
            state     <= SP_LOAD_WGT;
          end
        end

        SP_LOAD_WGT: begin
          // Read compressed weights (half the data of dense)
          spad_wgt_rd_en   <= 1'b1;
          spad_wgt_rd_addr <= wgt_ptr;
          if (spad_wgt_rd_valid) begin
            wgt_buf   <= spad_wgt_rd_data;
            wgt_ptr   <= wgt_ptr + (SPAD_DATA_W/8);
            group_idx <= '0;
            state     <= SP_DECOMPRESS;
          end
        end

        SP_DECOMPRESS: begin
          // Expand 16 compressed groups into the decomp_col buffer
          for (int g = 0; g < GROUPS_PER_READ; g++) begin
            decompress_group(
              wgt_buf[g*32 +: 32],
              g * 4,
              decomp_col
            );
          end
          state <= SP_ISSUE_COL;
        end

        SP_ISSUE_COL: begin
          arr_weight_load_en <= 1'b1;
          arr_weight_col_idx <= $clog2(COLS)'(col_idx);
          for (int r = 0; r < COLS; r++)
            arr_weight_col_data[r*16 +: 16] = decomp_col[r];

          col_idx <= col_idx + GROUPS_PER_READ * 4;  // Advance by columns processed

          // Check if we've processed all K columns
          if (col_idx + GROUPS_PER_READ * 4 >= dim_k) begin
            state <= SP_DONE;
          end else begin
            state <= SP_LOAD_MASK;
          end
        end

        SP_DONE: begin
          done  <= 1'b1;
          state <= SP_IDLE;
        end

        default: state <= SP_IDLE;
      endcase
    end
  end

endmodule
