#!/usr/bin/env bash
# ============================================================
# APEX-1 Setup & Run Script  — corrected v3
# Usage:
#   ./setup_and_run.sh          # full: lint + compile + run
#   ./setup_and_run.sh array    # single-array test only
#   ./setup_and_run.sh fullchip # full-die test only
#   ./setup_and_run.sh lint     # lint check only
# ============================================================
set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

RED='\033[0;31m'; GREEN='\033[0;32m'; CYAN='\033[0;36m'; BOLD='\033[1m'; NC='\033[0m'
info() { echo -e "${CYAN}[INFO]${NC} $*"; }
ok()   { echo -e "${GREEN}[OK]${NC}   $*"; }
die()  { echo -e "${RED}[FAIL]${NC} $*" >&2; exit 1; }
step() { echo -e "\n${BOLD}── $* ──${NC}"; }

# ── Step 1: Install Verilator ─────────────────────────────
step "1/5  Install Verilator"
if command -v verilator &>/dev/null; then
  ok "Already installed: $(verilator --version | head -1)"
elif [[ "$(uname)" == "Darwin" ]]; then
  brew install verilator
elif grep -qi "ubuntu\|debian" /etc/os-release 2>/dev/null; then
  sudo apt-get update -q && sudo apt-get install -y verilator g++ make
elif grep -qi "fedora\|rhel\|centos" /etc/os-release 2>/dev/null; then
  sudo dnf install -y verilator gcc-c++ make
else
  die "Install Verilator manually: https://verilator.org/guide/latest/install.html"
fi
verilator --version &>/dev/null || die "Verilator install failed"
ok "$(verilator --version | head -1)"

# ── Step 2: Verify files ──────────────────────────────────
step "2/5  Verify project files"
REQUIRED=(
  rtl/pkg/apex1_pkg.sv
  rtl/core/bf16_mul.sv rtl/core/fp8_mul.sv rtl/core/mac_cell.sv
  rtl/core/systolic_array.sv rtl/core/mxu_cluster.sv
  rtl/core/sparsity_engine.sv rtl/core/conv_engine.sv
  rtl/memory/spad_controller.sv rtl/memory/dma_engine.sv
  rtl/special/sfu.sv rtl/special/grad_accumulator.sv
  rtl/special/allreduce_engine.sv rtl/special/softmax_unit.sv
  rtl/special/norm_unit.sv rtl/control/static_sequencer.sv
  rtl/control/power_ctrl.sv rtl/io/pcie_host_if.sv
  rtl/apex1_die.sv
  verilator/sim_tops.cpp verilator/sim_array_tops.cpp verilator/Makefile
)
MISSING=0
for f in "${REQUIRED[@]}"; do
  if [[ -f "$f" ]]; then ok "$f"
  else echo -e "${RED}[MISS]${NC} $f"; MISSING=$((MISSING+1)); fi
done
[[ $MISSING -gt 0 ]] && die "$MISSING files missing"
ok "All files present"

# ── Quick sanity: confirm apex1_pkg.sv has no ifndef guard ─
if grep -q '`ifndef' rtl/pkg/apex1_pkg.sv; then
  die "rtl/pkg/apex1_pkg.sv still has \`ifndef guard — extract the latest fixed archive"
fi
ok "Package file is clean (no \`ifndef guard)"

# ── Source lists ──────────────────────────────────────────
ARRAY_SRCS=(
  rtl/pkg/apex1_pkg.sv
  rtl/core/bf16_mul.sv
  rtl/core/fp8_mul.sv
  rtl/core/mac_cell.sv
  rtl/core/systolic_array.sv
)

RTL_SRCS=(
  rtl/pkg/apex1_pkg.sv
  rtl/core/bf16_mul.sv rtl/core/fp8_mul.sv rtl/core/mac_cell.sv
  rtl/core/systolic_array.sv rtl/core/mxu_cluster.sv
  rtl/core/sparsity_engine.sv rtl/core/conv_engine.sv
  rtl/memory/spad_controller.sv rtl/memory/dma_engine.sv
  rtl/special/sfu.sv rtl/special/grad_accumulator.sv
  rtl/special/allreduce_engine.sv rtl/special/softmax_unit.sv
  rtl/special/norm_unit.sv rtl/control/static_sequencer.sv
  rtl/control/power_ctrl.sv rtl/io/pcie_host_if.sv
  rtl/apex1_die.sv
)

NCPU=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
MODE="${1:-all}"

# ── Step 3: Lint ──────────────────────────────────────────
step "3/5  Verilator lint"
info "Running lint on all RTL sources..."

# Note: Verilator requires -I with NO space (-Irtl/pkg not -I rtl/pkg)
verilator --sv --lint-only \
  --top apex1_die \
  -Irtl/pkg \
  "${RTL_SRCS[@]}" \
  && ok "Lint passed — no errors" \
  || die "Lint failed — fix errors above before compiling"

# ── Step 4: Compile ───────────────────────────────────────
step "4/5  Compile"
info "Using $NCPU parallel jobs"

[[ "$MODE" == "lint" ]] && { ok "Lint-only mode — done"; exit 0; }

# Common flags — Verilator needs -I with no space
VLT_FLAGS=(
  --sv
  -O1
  --x-assign fast
  --threads 1
  --x-initial fast
  --public-flat-rw
  --Mdir obj_dir
  --cc --exe --build
  -j "$NCPU"
  -Irtl/pkg
)

if [[ "$MODE" == "array" || "$MODE" == "all" ]]; then
  info "Compiling single-array harness (systolic_array)..."
  verilator "${VLT_FLAGS[@]}" \
    --top systolic_array \
    "${ARRAY_SRCS[@]}" \
    verilator/sim_array_tops.cpp \
    -o Vsystolic_array \
    && ok "Compiled → obj_dir/Vsystolic_array" \
    || die "Compile failed"
fi

if [[ "$MODE" == "fullchip" || "$MODE" == "all" ]]; then
  info "Compiling full-die harness (apex1_die) — this takes 2–5 min..."
  verilator "${VLT_FLAGS[@]}" \
    --top apex1_die \
    "${RTL_SRCS[@]}" \
    verilator/sim_tops.cpp \
    -o Vapex1_die \
    && ok "Compiled → obj_dir/Vapex1_die" \
    || die "Compile failed"
fi

# ── Step 5: Run ───────────────────────────────────────────
step "5/5  Run TOPS tests"

if [[ "$MODE" == "array" || "$MODE" == "all" ]]; then
  info "Running single-array TOPS test (~30s)..."
  ./obj_dir/Vsystolic_array --tiles 500 | tee array_tops.log
  echo ""
  echo -e "${BOLD}── Array results ──${NC}"
  grep -E "TOPS|Extrapolated|Efficiency|PASS|FAIL" array_tops.log || true
fi

if [[ "$MODE" == "fullchip" || "$MODE" == "all" ]]; then
  info "Running full-die TOPS test (2–10 min)..."
  ./obj_dir/Vapex1_die | tee fullchip_tops.log
  echo ""
  echo -e "${BOLD}── Full-chip results ──${NC}"
  grep -E "TOPS|estimate|PASS|FAIL|Summary" fullchip_tops.log || true
fi

echo ""
ok "Done."
echo "  Logs:     array_tops.log  fullchip_tops.log"
echo "  Waveform: gtkwave array_tops.vcd verilator/apex1_tops.gtkw"
