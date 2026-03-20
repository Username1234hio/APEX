#!/usr/bin/env bash
# Minimal lint test — run this directly to test without the full setup script
# Usage: ./test_lint.sh
set -e
cd "$(dirname "$0")"

echo "Working directory: $(pwd)"
echo "Verilator: $(verilator --version | head -1)"
echo ""
echo "Running lint..."

verilator --sv --lint-only \
  --top apex1_die \
  -Irtl/pkg \
  rtl/pkg/apex1_pkg.sv \
  rtl/core/bf16_mul.sv \
  rtl/core/fp8_mul.sv \
  rtl/core/mac_cell.sv \
  rtl/core/systolic_array.sv \
  rtl/core/mxu_cluster.sv \
  rtl/core/sparsity_engine.sv \
  rtl/core/conv_engine.sv \
  rtl/memory/spad_controller.sv \
  rtl/memory/dma_engine.sv \
  rtl/special/sfu.sv \
  rtl/special/grad_accumulator.sv \
  rtl/special/allreduce_engine.sv \
  rtl/special/softmax_unit.sv \
  rtl/special/norm_unit.sv \
  rtl/control/static_sequencer.sv \
  rtl/control/power_ctrl.sv \
  rtl/io/pcie_host_if.sv \
  rtl/apex1_die.sv

echo ""
echo "Lint passed."
