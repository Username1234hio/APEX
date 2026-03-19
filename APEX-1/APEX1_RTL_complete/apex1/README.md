# APEX-1 AI Matrix Processor — RTL

SystemVerilog RTL for the APEX-1 AI matrix processor.
Target: TSMC N3E | 3,000+ TOPS INT8 | LLM + CNN inference & training.

## File Structure

```
rtl/
├── pkg/
│   └── apex1_pkg.sv          # Package: parameters, types, ISA opcodes
├── core/
│   ├── bf16_mul.sv            # BF16 × BF16 → FP32 multiplier
│   ├── fp8_mul.sv             # FP8 multiplier (E4M3 / E5M2)
│   ├── mac_cell.sv            # Single MAC cell (INT8/BF16/FP8)
│   ├── systolic_array.sv      # 128×128 weight-stationary array
│   └── mxu_cluster.sv        # MXU cluster: 4 arrays + local SRAM
├── memory/
│   ├── spad_controller.sv     # 256 MB scratchpad SRAM controller
│   └── dma_engine.sv          # 8-channel scheduled DMA engine
├── special/
│   ├── sfu.sv                 # Special Function Unit (activate/norm)
│   ├── grad_accumulator.sv    # FP32 gradient accumulator (training)
│   └── allreduce_engine.sv   # Ring all-reduce over UCIe
├── control/
│   └── static_sequencer.sv   # Static instruction sequencer
├── io/
│   └── pcie_host_if.sv        # PCIe 5.0 host interface
├── apex1_die.sv               # Top-level die integration
└── apex1_tb.sv                # Full testbench
```

## Quick Start

### Syntax check (Icarus Verilog)
```bash
make iverilog
```

### Full simulation
```bash
make sim
# Produces apex1_sim.vcd — open with GTKWave
gtkwave apex1_sim.vcd
```

### Lint
```bash
make lint
```

### Area estimate (requires Yosys)
```bash
make synth_yosys
```

## Design Notes

- All modules use SystemVerilog (IEEE 1800-2012)
- Behavioral models for FP32 adder and BF16/FP8 arithmetic
  — replace with technology-mapped hard IP for synthesis
- SRAM arrays use behavioral `logic` arrays
  — replace with TSMC N3E SRAM compiler macros for tape-out
- PCIe interface is a simplified TLP model
  — replace with Synopsys DesignWare PCIe Gen5 hard IP

## ISA Summary (18 instructions)

| Opcode | Instruction    | Description                         |
|--------|----------------|-------------------------------------|
| 0x00   | NOP            | No operation                        |
| 0x01   | LOAD_TILE      | HBM → scratchpad DMA                |
| 0x02   | STORE_TILE     | Scratchpad → HBM DMA                |
| 0x03   | MATMUL         | Systolic GEMM tile                  |
| 0x04   | CONV2D         | 2D convolution                      |
| 0x05   | SPARSE_MM      | 2:4 sparse GEMM                     |
| 0x06   | ADD            | Element-wise add                    |
| 0x07   | SCALE          | Scalar multiply                     |
| 0x08   | ACTIVATE       | GELU / ReLU / SiLU / Sigmoid        |
| 0x09   | NORMALIZE      | LayerNorm / RMSNorm / GroupNorm     |
| 0x0A   | SOFTMAX        | Row softmax                         |
| 0x0B   | REDUCE_SUM     | Reduction along dimension           |
| 0x0C   | REDUCE_MAX     | Max reduction                       |
| 0x0D   | TRANSPOSE      | Tensor layout permutation           |
| 0x0E   | GRAD_ACCUM     | BF16→FP32 gradient accumulation     |
| 0x0F   | ALL_REDUCE     | Cross-die ring all-reduce           |
| 0x10   | DMA_PREFETCH   | Scheduled async prefetch            |
| 0x11   | SYNC_BARRIER   | Barrier synchronization             |
