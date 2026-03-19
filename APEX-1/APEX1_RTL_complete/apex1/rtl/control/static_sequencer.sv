// ============================================================
// APEX-1 — static_sequencer.sv
// Fetches instructions from the instruction buffer (loaded via
// PCIe DMA from host), decodes them, and dispatches to:
//   - MXU clusters (MATMUL, CONV2D, SPARSE_MM)
//   - Special function units (ACTIVATE, NORMALIZE, SOFTMAX)
//   - DMA engine (LOAD_TILE, STORE_TILE, DMA_PREFETCH)
//   - Gradient accumulator (GRAD_ACCUM)
//   - All-reduce engine (ALL_REDUCE)
// No out-of-order execution. No branch prediction.
// Instruction stream is a flat, statically ordered sequence.
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module static_sequencer #(
  parameter int IBUF_DEPTH = 4096   // Instruction buffer depth
)(
  input  logic              clk,
  input  logic              rst_n,

  // Host loads instruction stream via PCIe DMA
  input  logic              ibuf_wr_en,
  input  logic [127:0]      ibuf_wr_data,
  input  logic [11:0]       ibuf_wr_addr,
  output logic              ibuf_ready,

  // Execution enable
  input  logic              exec_start,      // Pulse to begin execution
  input  logic [11:0]       exec_instr_count,

  // Global cycle counter (exported for DMA scheduling)
  output logic [31:0]       global_cycle,

  // ── Dispatch to MXU clusters ─────────────────────────────
  output logic              mxu_op_valid    [CLUSTERS_PER_DIE],
  output opcode_t           mxu_op_code     [CLUSTERS_PER_DIE],
  output logic [23:0]       mxu_addr_a      [CLUSTERS_PER_DIE],
  output logic [23:0]       mxu_addr_b      [CLUSTERS_PER_DIE],
  output logic [23:0]       mxu_addr_c      [CLUSTERS_PER_DIE],
  output logic [15:0]       mxu_dim_m       [CLUSTERS_PER_DIE],
  output logic [15:0]       mxu_dim_n       [CLUSTERS_PER_DIE],
  output logic [11:0]       mxu_dim_k       [CLUSTERS_PER_DIE],
  output dtype_t            mxu_dtype       [CLUSTERS_PER_DIE],
  output logic              mxu_sparse      [CLUSTERS_PER_DIE],
  input  logic              mxu_done        [CLUSTERS_PER_DIE],
  input  cluster_status_t   mxu_status      [CLUSTERS_PER_DIE],

  // ── Dispatch to SFU ──────────────────────────────────────
  output logic              sfu_op_valid,
  output opcode_t           sfu_op_code,
  output logic [23:0]       sfu_addr_a,
  output logic [23:0]       sfu_addr_c,
  output logic [15:0]       sfu_count,
  output act_fn_t           sfu_act_fn,
  output norm_fn_t          sfu_norm_fn,
  input  logic              sfu_done,

  // ── Dispatch to DMA ──────────────────────────────────────
  output logic              dma_desc_valid,
  output dma_desc_t         dma_desc,
  output logic [2:0]        dma_ch_sel,
  input  logic              dma_desc_ready,
  input  logic [7:0]        dma_ch_done,

  // ── Dispatch to gradient accumulator ─────────────────────
  output logic              grad_valid,
  output logic [23:0]       grad_addr,
  output logic [15:0]       grad_count,
  input  logic              grad_done,

  // ── Dispatch to all-reduce engine ────────────────────────
  output logic              ar_valid,
  output logic [23:0]       ar_addr,
  output logic [15:0]       ar_count,
  output reduce_topo_t      ar_topo,
  input  logic              ar_done,

  // ── Barrier synchronization ───────────────────────────────
  // (All units must reach the barrier before sequencer advances)
  output logic              all_barrier_req,
  input  logic              all_barrier_ack,

  // Status
  output logic              executing,
  output logic              seq_done
);

  // ── Instruction buffer ────────────────────────────────────
  logic [127:0] ibuf [IBUF_DEPTH];

  always_ff @(posedge clk) begin
    if (ibuf_wr_en && ibuf_ready)
      ibuf[ibuf_wr_addr] <= ibuf_wr_data;
  end

  // ── Sequencer state ───────────────────────────────────────
  typedef enum logic [2:0] {
    SEQ_IDLE,
    SEQ_FETCH,
    SEQ_DECODE,
    SEQ_ISSUE,
    SEQ_WAIT,    // Wait for current instruction to complete
    SEQ_BARRIER,
    SEQ_DONE
  } seq_state_t;

  seq_state_t   seq_state;
  logic [11:0]  pc;          // Program counter
  logic [11:0]  instr_total;
  logic [127:0] instr_raw;
  instruction_t instr;

  // ── Global cycle counter ──────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n)          global_cycle <= '0;
    else if (executing)  global_cycle <= global_cycle + 1;
    else if (!exec_start) global_cycle <= '0;
  end

  assign ibuf_ready = (seq_state == SEQ_IDLE);

  // ── Instruction decode ────────────────────────────────────
  always_comb begin
    instr_raw = ibuf[pc];
    // Map raw 128-bit word to instruction fields
    instr.opcode    = opcode_t'(instr_raw[7:0]);
    instr.operand_a = instr_raw[31:8];
    instr.operand_b = instr_raw[55:32];
    instr.operand_c = instr_raw[79:56];
    instr.dim_m     = instr_raw[95:80];
    instr.dim_n     = instr_raw[111:96];
    instr.dim_k     = instr_raw[123:112];
    instr.dtype     = dtype_t'(instr_raw[126:124]);
    instr.flags     = instr_raw[127:124];  // Overlapping — flags[3:0]
    instr.reserved  = '0;
  end

  // ── Round-robin cluster assignment ────────────────────────
  logic [$clog2(CLUSTERS_PER_DIE)-1:0] cluster_rr;

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) cluster_rr <= '0;
    else if (seq_state == SEQ_ISSUE &&
             (instr.opcode == OP_MATMUL ||
              instr.opcode == OP_CONV2D ||
              instr.opcode == OP_SPARSE_MM))
      cluster_rr <= (cluster_rr == CLUSTERS_PER_DIE-1) ? '0 : cluster_rr + 1;
  end

  // ── DMA channel round-robin ───────────────────────────────
  logic [2:0] dma_ch_rr;
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) dma_ch_rr <= '0;
    else if (seq_state == SEQ_ISSUE &&
             (instr.opcode == OP_LOAD_TILE ||
              instr.opcode == OP_STORE_TILE ||
              instr.opcode == OP_DMA_PREFETCH))
      dma_ch_rr <= (dma_ch_rr == 7) ? '0 : dma_ch_rr + 1;
  end

  // ── Main FSM ──────────────────────────────────────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      seq_state    <= SEQ_IDLE;
      pc           <= '0;
      executing    <= 1'b0;
      seq_done     <= 1'b0;
      instr_total  <= '0;
      // Clear all dispatch signals
      for (int c = 0; c < CLUSTERS_PER_DIE; c++)
        mxu_op_valid[c] <= 1'b0;
      sfu_op_valid    <= 1'b0;
      dma_desc_valid  <= 1'b0;
      grad_valid      <= 1'b0;
      ar_valid        <= 1'b0;
      all_barrier_req <= 1'b0;
    end else begin
      // Clear one-cycle pulses
      for (int c = 0; c < CLUSTERS_PER_DIE; c++)
        mxu_op_valid[c] <= 1'b0;
      sfu_op_valid   <= 1'b0;
      dma_desc_valid <= 1'b0;
      grad_valid     <= 1'b0;
      ar_valid       <= 1'b0;
      seq_done       <= 1'b0;

      unique case (seq_state)
        SEQ_IDLE: begin
          if (exec_start) begin
            pc          <= '0;
            instr_total <= exec_instr_count;
            executing   <= 1'b1;
            seq_state   <= SEQ_FETCH;
          end
        end

        SEQ_FETCH: begin
          seq_state <= SEQ_DECODE;
        end

        SEQ_DECODE: begin
          seq_state <= SEQ_ISSUE;
        end

        SEQ_ISSUE: begin
          seq_state <= SEQ_WAIT;

          unique case (instr.opcode)

            OP_NOP: begin
              seq_state <= SEQ_FETCH;   // NOP: skip wait
              pc <= pc + 1;
            end

            OP_MATMUL, OP_CONV2D, OP_SPARSE_MM: begin
              mxu_op_valid[cluster_rr] <= 1'b1;
              mxu_op_code[cluster_rr]  <= instr.opcode;
              mxu_addr_a[cluster_rr]   <= instr.operand_a;
              mxu_addr_b[cluster_rr]   <= instr.operand_b;
              mxu_addr_c[cluster_rr]   <= instr.operand_c;
              mxu_dim_m[cluster_rr]    <= instr.dim_m;
              mxu_dim_n[cluster_rr]    <= instr.dim_n;
              mxu_dim_k[cluster_rr]    <= instr.dim_k;
              mxu_dtype[cluster_rr]    <= instr.dtype;
              mxu_sparse[cluster_rr]   <= (instr.opcode == OP_SPARSE_MM);
            end

            OP_ACTIVATE, OP_NORMALIZE, OP_SOFTMAX,
            OP_ADD, OP_SCALE, OP_REDUCE_SUM,
            OP_REDUCE_MAX, OP_TRANSPOSE: begin
              sfu_op_valid <= 1'b1;
              sfu_op_code  <= instr.opcode;
              sfu_addr_a   <= instr.operand_a;
              sfu_addr_c   <= instr.operand_c;
              sfu_count    <= instr.dim_m;
              sfu_act_fn   <= act_fn_t'(instr.operand_b[2:0]);
              sfu_norm_fn  <= norm_fn_t'(instr.operand_b[4:3]);
            end

            OP_LOAD_TILE, OP_STORE_TILE, OP_DMA_PREFETCH: begin
              dma_desc_valid      <= 1'b1;
              dma_ch_sel          <= dma_ch_rr;
              dma_desc.hbm_addr   <= {instr.operand_b[8:0], instr.operand_a};   // 33-bit HBM addr
              dma_desc.spad_addr  <= instr.operand_c;
              dma_desc.byte_count <= {12'b0, instr.dim_m, instr.dim_n};
              dma_desc.fire_cycle <= (instr.opcode == OP_DMA_PREFETCH) ?
                                     {16'b0, instr.dim_k, 4'b0} : global_cycle;
              dma_desc.direction  <= (instr.opcode == OP_STORE_TILE) ? 1'b1 : 1'b0;
              dma_desc.valid      <= 1'b1;
            end

            OP_GRAD_ACCUM: begin
              grad_valid <= 1'b1;
              grad_addr  <= instr.operand_a;
              grad_count <= instr.dim_m;
            end

            OP_ALL_REDUCE: begin
              ar_valid <= 1'b1;
              ar_addr  <= instr.operand_a;
              ar_count <= instr.dim_m;
              ar_topo  <= reduce_topo_t'(instr.operand_b[0]);
            end

            OP_SYNC_BARRIER: begin
              all_barrier_req <= 1'b1;
              seq_state <= SEQ_BARRIER;
            end

            default: begin
              seq_state <= SEQ_FETCH;
              pc <= pc + 1;
            end
          endcase
        end

        SEQ_WAIT: begin
          // Wait for the dispatched unit to complete
          logic unit_done;
          unit_done = 1'b0;
          case (instr.opcode)
            OP_MATMUL, OP_CONV2D,
            OP_SPARSE_MM:             unit_done = mxu_done[cluster_rr];
            OP_ACTIVATE, OP_NORMALIZE,
            OP_SOFTMAX, OP_ADD,
            OP_SCALE, OP_REDUCE_SUM,
            OP_REDUCE_MAX, OP_TRANSPOSE: unit_done = sfu_done;
            OP_LOAD_TILE, OP_STORE_TILE,
            OP_DMA_PREFETCH:          unit_done = dma_ch_done[dma_ch_rr];
            OP_GRAD_ACCUM:            unit_done = grad_done;
            OP_ALL_REDUCE:            unit_done = ar_done;
            default:                  unit_done = 1'b1;
          endcase

          if (unit_done) begin
            pc <= pc + 1;
            if (pc + 1 >= instr_total)
              seq_state <= SEQ_DONE;
            else
              seq_state <= SEQ_FETCH;
          end
        end

        SEQ_BARRIER: begin
          all_barrier_req <= 1'b0;
          if (all_barrier_ack) begin
            pc        <= pc + 1;
            seq_state <= (pc + 1 >= instr_total) ? SEQ_DONE : SEQ_FETCH;
          end
        end

        SEQ_DONE: begin
          executing   <= 1'b0;
          seq_done    <= 1'b1;
          seq_state   <= SEQ_IDLE;
        end

        default: seq_state <= SEQ_IDLE;
      endcase
    end
  end

endmodule
