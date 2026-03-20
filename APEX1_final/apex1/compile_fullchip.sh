#!/usr/bin/env bash
# compile_fullchip.sh — full apex1_die TOPS test
# Expected compile time: 3-10 minutes
set -e
cd "$(dirname "$0")"

NCPU=$(nproc 2>/dev/null || echo 4)
echo "Compiling apex1_die (${NCPU} jobs)..."
echo "This takes 3-10 minutes. Get a coffee."
echo ""

verilator --sv \
  --cc --exe --build \
  -j "$NCPU" \
  --Mdir obj_dir_fullchip \
  -Irtl/pkg \
  --top apex1_die \
  -O1 \
  --x-assign fast \
  --threads 1 \
  --x-initial fast \
  -CFLAGS "-O1" \
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
  rtl/apex1_die.sv \
  verilator/sim_tops.cpp \
  -o Vapex1_die

echo ""
echo "Compile done. Running full-die TOPS test..."
echo ""
./obj_dir_fullchip/Vapex1_die
