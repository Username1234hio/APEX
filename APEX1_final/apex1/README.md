# APEX-1

**AI Processing EXecution — Matrix Processor**

> *Purpose-built silicon for the age of large-scale AI. Nothing more. Nothing less.*

---

## What is APEX-1?

APEX-1 is a custom AI accelerator chip designed from first principles to do one thing extraordinarily well: **matrix multiplication**. Every transistor, every wire, every instruction in the ISA exists to serve that goal.

It cannot run a web browser. It cannot render a game. It cannot execute a Python script. What it *can* do is multiply matrices at a scale and efficiency that no general-purpose processor can match — and it does this by ruthlessly discarding everything that doesn't contribute to that mission.

APEX-1 achieves **3,000+ TOPS** of INT8 throughput in a four-die chiplet package on TSMC N3E, backed by 96 GB of HBM3e memory at 6 TB/s bandwidth. It supports LLM inference, LLM training, and convolutional neural network workloads — the three dominant compute patterns in modern AI.

---

## Why does this chip exist?

Modern AI workloads are dominated by one mathematical operation: the matrix multiply-accumulate, or MAC. When a transformer model processes a token, when a convolutional net classifies an image, when backpropagation updates weights during training — all of it reduces to vast grids of MAC operations applied to dense matrices.

General-purpose processors (CPUs, GPUs) are built for unpredictable workloads. They spend enormous silicon area on branch predictors, out-of-order execution engines, cache hierarchies, and instruction decoders — hardware that exists entirely to handle the fact that the processor doesn't know what's coming next.

APEX-1 does know what's coming next. The compiler knows the *entire* execution schedule before the first token is processed. So APEX-1 discards the uncertainty-handling hardware entirely and replaces it with more arithmetic.

---

## Architecture at a glance

```
┌─────────────────────────────────────────────────────────────────┐
│                    APEX-1 Package (CoWoS)                       │
│                                                                  │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐        │
│  │  Die 0   │  │  Die 1   │  │  Die 2   │  │  Die 3   │        │
│  │ 4×MXU    │  │ 4×MXU    │  │ 4×MXU    │  │ 4×MXU    │        │
│  │ clusters │  │ clusters │  │ clusters │  │ clusters │        │
│  └────┬─────┘  └────┬─────┘  └────┬─────┘  └────┬─────┘        │
│       └─────────────┴──────────────┴─────────────┘             │
│                     UCIe 2.0 ring  (20 TB/s)                   │
│                                                                  │
│  ┌──────────────────────┐    ┌──────────────────────┐           │
│  │    HBM3e Stack A     │    │    HBM3e Stack B     │           │
│  │  48 GB  ·  3 TB/s    │    │  48 GB  ·  3 TB/s    │           │
│  └──────────────────────┘    └──────────────────────┘           │
└─────────────────────────────────────────────────────────────────┘
```

### MXU Cluster

Each of the 16 MXU (Matrix eXecution Unit) clusters contains four 128×128 systolic arrays. A systolic array is a grid of MAC cells where data flows rhythmically between neighbors — activations drift rightward, weights sit stationary, and partial products accumulate in place. This eliminates broadcasting overhead entirely: each datum moves exactly one cell per clock cycle.

```
Weight column loading (once per tile):
  W[0]  W[1]  W[2] ... W[127]
   ↓     ↓     ↓          ↓
  [M] → [M] → [M] → ... [M]  ← Activation row 0
  [M] → [M] → [M] → ... [M]  ← Activation row 1
   ⋮                     ⋮
  [M] → [M] → [M] → ... [M]  ← Activation row 127
                              → Results drain rightward
```

One 128×128 array: **32.8 TOPS** at INT8, 1 GHz.
Four arrays per cluster: **131 TOPS**.
Sixteen clusters (four dies): **3,146 TOPS** dense, **6,291 TOPS** with 2:4 sparsity.

### Memory hierarchy

| Level | Size | Bandwidth | Managed by |
|---|---|---|---|
| MAC registers | 4 KB / array | — | Hardware |
| Tile SRAM | 2 MB / cluster | ~8 TB/s | Compiler |
| Global scratchpad | 256 MB | ~20 TB/s | Compiler |
| HBM3e | 96 GB | 6 TB/s | DMA engine |

There are no hardware caches. The compiler assigns every data movement at compile time. Memory latency is fully deterministic by construction — no cache miss is possible because no cache exists.

---

## Key specifications

| Parameter | Value |
|---|---|
| Process node | TSMC N3E (3nm class) |
| Package | 4-die CoWoS on silicon interposer |
| Die area | ~300 mm² each |
| Clock frequency | 1.0 GHz |
| Peak throughput (INT8, dense) | 3,146 TOPS |
| Peak throughput (INT8, 2:4 sparse) | 6,291 TOPS |
| Peak throughput (BF16) | 786 TOPS |
| Peak throughput (FP8) | 3,146 TOPS |
| On-chip SRAM | 256 MB |
| HBM3e memory | 96 GB (2 stacks) |
| Memory bandwidth | 6 TB/s |
| Host interface | PCIe 5.0 x16 (128 GB/s) |
| Scale-out link | UCIe 2.0 (20 TB/s) |
| Package TDP | ~400 W |
| Supported workloads | LLM inference · LLM training · CNN inference · CNN training |
| Unsupported workloads | Everything else |

---

## Supported workloads

### Large language model inference

APEX-1 is designed around the transformer attention mechanism. The Q×Kᵀ matmul, softmax, and ×V projection are fused into a single tiled kernel that never leaves the scratchpad between stages — a FlashAttention-style approach baked into the compiler. The 96 GB HBM accommodates model weights for:

- **~48B parameters** at BF16 (inference only)
- **~8B parameters** at BF16 (full training with Adam optimizer state)

### LLM training

Training adds gradient computation and weight updates to the inference path. APEX-1 supports training through:

- **FP32 gradient accumulation** — a dedicated 256-entry FP32 register file prevents precision loss during gradient reduction
- **Ring all-reduce** — the `ALL_REDUCE` instruction coordinates gradient synchronization across all four dies over the UCIe ring, with no host CPU involvement
- **Gradient checkpointing** — the compiler can recompute activations on demand rather than storing them, trading compute for memory headroom on large models

### Convolutional neural networks

CNN inference and training are handled through two specialized paths in the convolution engine:

- **im2col** — reshapes the input tensor into a 2D matrix on-the-fly, with zero memory replication. Works for any kernel size, stride, dilation, and group configuration
- **Winograd F(2,3)** — reduces multiply count by 2.25× for 3×3/stride-1 kernels. Selected automatically by the compiler when the kernel geometry matches

---

## The ISA: 18 instructions

APEX-1's instruction set has exactly 18 entries. This is not a limitation — it is the enforcement mechanism. There is no way to express a branch, a memory allocation, a loop counter, or a conditional in this ISA. A standard binary cannot execute here.

| Opcode | Instruction | Description |
|---|---|---|
| `0x00` | `NOP` | No operation |
| `0x01` | `LOAD_TILE` | HBM → scratchpad DMA transfer |
| `0x02` | `STORE_TILE` | Scratchpad → HBM writeback |
| `0x03` | `MATMUL` | Systolic GEMM tile (INT8 / BF16 / FP8) |
| `0x04` | `CONV2D` | 2D convolution (im2col or Winograd) |
| `0x05` | `SPARSE_MM` | 2:4 structured sparse GEMM |
| `0x06` | `ADD` | Element-wise addition |
| `0x07` | `SCALE` | Scalar multiply |
| `0x08` | `ACTIVATE` | GELU · ReLU · SiLU · Sigmoid |
| `0x09` | `NORMALIZE` | LayerNorm · RMSNorm · GroupNorm |
| `0x0A` | `SOFTMAX` | Numerically stable row softmax |
| `0x0B` | `REDUCE_SUM` | Reduction along a tensor dimension |
| `0x0C` | `REDUCE_MAX` | Max reduction |
| `0x0D` | `TRANSPOSE` | Tensor layout permutation |
| `0x0E` | `GRAD_ACCUM` | BF16 → FP32 gradient accumulation |
| `0x0F` | `ALL_REDUCE` | Cross-die ring gradient reduction |
| `0x10` | `DMA_PREFETCH` | Scheduled async prefetch (fire at cycle N) |
| `0x11` | `SYNC_BARRIER` | Stall until all clusters reach barrier |

All instructions are 128-bit fixed width. The compiler emits a flat binary blob with no labels, no relocations, and no runtime linking. Execution is deterministic to the cycle.

---

## Number formats

| Format | Width | Use case | Relative throughput |
|---|---|---|---|
| INT8 | 8-bit | Quantized inference | 1.0× (baseline) |
| INT4 | 4-bit | Aggressive quantized inference | 2.0× |
| BF16 | 16-bit | Training forward pass, high-quality inference | 0.25× |
| FP8 E4M3 | 8-bit | Training, high-quality inference | 1.0× |
| FP8 E5M2 | 8-bit | Training gradients | 1.0× |
| FP32 | 32-bit | Gradient accumulation only — no compute | — |

FP64 is not supported. FP32 compute is not supported. These are not omissions — they are load-bearing design decisions that free up die area for more INT8 MACs.

---

## Sparsity

Modern large models can be pruned using the **2:4 structured sparsity** pattern: in every consecutive group of four weights, exactly two are forced to zero during a sparsity-aware training pass. The compressed representation stores only the two non-zero values plus a 2-bit index mask indicating which positions they occupy.

APEX-1's sparsity engine decompresses this format on-the-fly as data enters the systolic array, skipping the zero-multiplications entirely. The result is **2× throughput** on 2:4-sparse models with no arithmetic accuracy loss — pushing the effective system peak to 6,291 TOPS INT8.

---

## Power management

Three operating points, selectable at runtime by the host driver:

| Mode | Frequency | Core voltage | Power |
|---|---|---|---|
| Performance | 1.0 GHz | 0.75 V | ~400 W |
| Balanced | 800 MHz | 0.70 V | ~260 W |
| Efficiency | 500 MHz | 0.65 V | ~120 W |

Each MXU cluster is independently power-gated after 16 consecutive idle cycles. A dedicated power controller monitors eight on-die temperature sensors and automatically steps down the operating point if the junction temperature exceeds 80°C, throttling to the efficiency point at 90°C.

---

## RTL overview

The codebase is written in SystemVerilog (IEEE 1800-2012) and organized as follows:

```
rtl/
├── pkg/
│   └── apex1_pkg.sv           # All parameters, types, ISA definitions
├── core/
│   ├── mac_cell.sv             # Single MAC cell (INT8 / BF16 / FP8)
│   ├── bf16_mul.sv             # BF16 × BF16 → FP32 multiplier
│   ├── fp8_mul.sv              # FP8 multiplier (E4M3 / E5M2)
│   ├── systolic_array.sv       # 128×128 weight-stationary array
│   ├── mxu_cluster.sv          # Cluster: 4 arrays + 2MB SRAM + reduction
│   ├── sparsity_engine.sv      # 2:4 sparse decompressor
│   └── conv_engine.sv          # im2col + Winograd convolution engine
├── memory/
│   ├── spad_controller.sv      # 256MB scratchpad (16 banks, 5 ports)
│   └── dma_engine.sv           # 8-channel scheduled DMA engine
├── special/
│   ├── sfu.sv                  # Special Function Unit (activate/norm)
│   ├── softmax_unit.sv         # Two-pass numerically stable softmax
│   ├── norm_unit.sv            # LayerNorm / RMSNorm / GroupNorm
│   ├── grad_accumulator.sv     # FP32 gradient accumulator (training)
│   └── allreduce_engine.sv     # Ring all-reduce over UCIe
├── control/
│   ├── static_sequencer.sv     # Flat instruction stream executor
│   └── power_ctrl.sv           # DVFS + cluster power gating
├── io/
│   └── pcie_host_if.sv         # PCIe 5.0 host interface
├── apex1_die.sv                # Top-level die integration
└── apex1_tb.sv                 # Full system testbench
constraints/
├── apex1.sdc                   # Synthesis timing constraints (1 GHz)
└── apex1.upf                   # UPF 3.0 power intent (multi-voltage)
```

### Getting started

**Compile and simulate** (requires Icarus Verilog ≥ 12):
```bash
make sim
gtkwave apex1_sim.vcd
```

**Lint check** (requires Verilator ≥ 5.0):
```bash
make lint
```

**Area estimate** (requires Yosys ≥ 0.30):
```bash
make synth_yosys
```

### Notes for synthesis

Three categories of behavioral code must be replaced with technology-mapped IP before tape-out:

- **FP32 arithmetic** in `grad_accumulator.sv` and `norm_unit.sv` — replace with a technology-mapped IEEE 754 adder (e.g., Synopsys DesignWare FP add)
- **SRAM arrays** in `spad_controller.sv` and `mxu_cluster.sv` — replace `logic` arrays with TSMC N3E SRAM compiler macros
- **PCIe hard IP** in `pcie_host_if.sv` — replace the TLP behavioral model with Synopsys DesignWare PCIe Gen5 hard IP

---

## Design decisions

**Why no cache?**
Hardware caches exist to handle unpredictable access patterns. AI inference and training have perfectly predictable access patterns, determined entirely at compile time. A cache would waste silicon area on tag arrays, LRU logic, and coherence hardware — none of which benefits a workload the compiler already manages optimally. Software-managed scratchpads achieve zero miss overhead by construction.

**Why no branch predictor?**
There are no branches in the ISA. The question cannot arise.

**Why systolic arrays over SIMD?**
GPU SIMD units broadcast operands to many parallel lanes, requiring O(N) bandwidth for N lanes. Systolic arrays are local: each datum moves one cell per cycle, O(1) bandwidth per cell. At the scale of millions of MACs, this difference dominates power consumption.

**Why HBM3e over GDDR7?**
At 400W total package power, reaching 6 TB/s bandwidth from GDDR7 would require six 32-bit channels spread across the PCB with substantial signal integrity challenges. HBM3e delivers 3 TB/s per stack through a 1024-bit interface across a few millimeters of interposer. For a chip built around an interposer anyway, HBM3e wins on bandwidth-per-watt and bandwidth-per-mm² by a wide margin.

**Why static scheduling?**
Dynamic scheduling exists for unpredictable workloads. Inference graphs are fully determined at model load time. Every tensor shape, every data dependency, every memory address is known before the first token. Static scheduling moves all of that decision-making to compile time, drops runtime overhead to zero, and makes latency deterministic — which is what SLA-driven inference actually requires.

---

## Known limitations

- **Dynamic sequence lengths** require shape-specialized compilation or conservative scratchpad allocation. Variable-length L