// ============================================================
// APEX-1 AI Matrix Processor — Package File
// All parameters, types, and constants shared across the design
// ============================================================
`ifndef APEX1_PKG_SV
`define APEX1_PKG_SV

package apex1_pkg;

  // ──────────────────────────────────────────────────────────
  // Top-level chip parameters
  // ──────────────────────────────────────────────────────────
  parameter int ARRAY_ROWS        = 128;   // Systolic array rows
  parameter int ARRAY_COLS        = 128;   // Systolic array cols
  parameter int ARRAYS_PER_CLUSTER = 4;   // Arrays per MXU cluster
  parameter int CLUSTERS_PER_DIE  = 4;    // MXU clusters per die
  parameter int NUM_DIES          = 4;    // Dies in package

  // Derived
  parameter int ARRAYS_PER_DIE    = ARRAYS_PER_CLUSTER * CLUSTERS_PER_DIE;
  parameter int TOTAL_ARRAYS      = ARRAYS_PER_DIE * NUM_DIES;
  parameter int MACS_PER_ARRAY    = ARRAY_ROWS * ARRAY_COLS;

  // ──────────────────────────────────────────────────────────
  // Memory parameters
  // ──────────────────────────────────────────────────────────
  parameter int SPAD_SIZE_BYTES   = 256 * 1024 * 1024;  // 256 MB scratchpad
  parameter int SPAD_ADDR_W       = 28;   // log2(256MB) = 28
  parameter int SPAD_DATA_W       = 512;  // 512-bit wide SRAM bus
  parameter int TILE_SRAM_KB      = 2048; // 2 MB per cluster local SRAM
  parameter int HBM_ADDR_W        = 37;   // 96 GB = 2^37 bytes
  parameter int HBM_DATA_W        = 512;  // HBM burst width
  parameter int DMA_CHANNELS      = 8;    // Parallel DMA channels

  // ──────────────────────────────────────────────────────────
  // Data format encoding
  // ──────────────────────────────────────────────────────────
  typedef enum logic [2:0] {
    DTYPE_INT8   = 3'b000,
    DTYPE_INT4   = 3'b001,
    DTYPE_BF16   = 3'b010,
    DTYPE_FP8_E4M3 = 3'b011,
    DTYPE_FP8_E5M2 = 3'b100,
    DTYPE_FP32   = 3'b101   // accumulator only
  } dtype_t;

  // ──────────────────────────────────────────────────────────
  // ISA — Opcode encoding (8-bit opcode field)
  // ──────────────────────────────────────────────────────────
  typedef enum logic [7:0] {
    OP_LOAD_TILE    = 8'h01,
    OP_STORE_TILE   = 8'h02,
    OP_MATMUL       = 8'h03,
    OP_CONV2D       = 8'h04,
    OP_SPARSE_MM    = 8'h05,
    OP_ADD          = 8'h06,
    OP_SCALE        = 8'h07,
    OP_ACTIVATE     = 8'h08,
    OP_NORMALIZE    = 8'h09,
    OP_SOFTMAX      = 8'h0A,
    OP_REDUCE_SUM   = 8'h0B,
    OP_REDUCE_MAX   = 8'h0C,
    OP_TRANSPOSE    = 8'h0D,
    OP_GRAD_ACCUM   = 8'h0E,
    OP_ALL_REDUCE   = 8'h0F,
    OP_DMA_PREFETCH = 8'h10,
    OP_SYNC_BARRIER = 8'h11,
    OP_NOP          = 8'h00
  } opcode_t;

  // ──────────────────────────────────────────────────────────
  // Instruction format — 128-bit fixed width
  // ──────────────────────────────────────────────────────────
  typedef struct packed {
    logic [7:0]   opcode;
    logic [23:0]  operand_a;   // Source A address / cluster mask
    logic [23:0]  operand_b;   // Source B address / scalar
    logic [23:0]  operand_c;   // Destination address
    logic [15:0]  dim_m;       // Matrix dimension M
    logic [15:0]  dim_n;       // Matrix dimension N
    logic [11:0]  dim_k;       // Matrix dimension K
    logic [2:0]   dtype;       // Data type
    logic [3:0]   flags;       // Misc flags (sparse, fuse, etc.)
    logic [4:0]   reserved;
  } instruction_t;             // Total: 8+24+24+24+16+16+12+3+4+5 = 136 — packed to 128 via reserved trim

  // ──────────────────────────────────────────────────────────
  // Activation function encoding
  // ──────────────────────────────────────────────────────────
  typedef enum logic [2:0] {
    ACT_RELU    = 3'b000,
    ACT_GELU    = 3'b001,
    ACT_SILU    = 3'b010,
    ACT_SIGMOID = 3'b011,
    ACT_NONE    = 3'b111
  } act_fn_t;

  // ──────────────────────────────────────────────────────────
  // Normalization function encoding
  // ──────────────────────────────────────────────────────────
  typedef enum logic [1:0] {
    NORM_LAYER  = 2'b00,
    NORM_RMS    = 2'b01,
    NORM_GROUP  = 2'b10,
    NORM_NONE   = 2'b11
  } norm_fn_t;

  // ──────────────────────────────────────────────────────────
  // All-reduce topology
  // ──────────────────────────────────────────────────────────
  typedef enum logic [1:0] {
    TOPO_RING = 2'b00,
    TOPO_TREE = 2'b01
  } reduce_topo_t;

  // ──────────────────────────────────────────────────────────
  // MXU cluster status
  // ──────────────────────────────────────────────────────────
  typedef struct packed {
    logic        busy;
    logic        power_gated;
    logic [3:0]  array_active;   // Which of the 4 arrays are active
    logic [15:0] tiles_completed;
  } cluster_status_t;

  // ──────────────────────────────────────────────────────────
  // DMA descriptor
  // ──────────────────────────────────────────────────────────
  typedef struct packed {
    logic [HBM_ADDR_W-1:0]  hbm_addr;
    logic [SPAD_ADDR_W-1:0] spad_addr;
    logic [27:0]             byte_count;
    logic [31:0]             fire_cycle;   // Cycle number to begin transfer
    logic                    valid;
    logic                    direction;    // 0=HBM->SPAD, 1=SPAD->HBM
  } dma_desc_t;

endpackage
`endif
