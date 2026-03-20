#!/usr/bin/env bash
# ============================================================
# compile_array.sh  — systolic_array TOPS test
# Usage:
#   ./compile_array.sh        # 8×8  (~30 seconds)
#   ./compile_array.sh 128    # 128×128 (~10-20 min)
# ============================================================
set -e
cd "$(dirname "$0")"

SIM_SIZE="${1:-8}"
NCPU=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
OUTDIR="obj_dir_array_${SIM_SIZE}"
VLT_ROOT=$(verilator --getenv VERILATOR_ROOT 2>/dev/null)
VLT_INC="$VLT_ROOT/include"

echo "========================================"
echo "  APEX-1 systolic_array TOPS"
echo "  Array size : ${SIM_SIZE}x${SIM_SIZE}"
echo "  CPU jobs   : ${NCPU}"
echo "========================================"

if [[ "$SIM_SIZE" == "128" ]]; then
  echo "WARNING: ~10-20 min. Ctrl-C to cancel..."; sleep 5
  VLT_OPT="-O2"; COPT="-O2"
else
  echo "Compile time: ~30 seconds."
  VLT_OPT="-O1"; COPT="-O1"
fi

[[ -d "$OUTDIR" ]] && rm -rf "$OUTDIR"

TMP_PKG=$(mktemp /tmp/apex1_pkg_sim_XXXX.sv)
sed -E "s/(parameter int ARRAY_ROWS[[:space:]]*=)[[:space:]]*[0-9]+/\1 ${SIM_SIZE}/" \
    rtl/pkg/apex1_pkg.sv | \
sed -E "s/(parameter int ARRAY_COLS[[:space:]]*=)[[:space:]]*[0-9]+/\1 ${SIM_SIZE}/" \
    > "$TMP_PKG"

# ── Step 1: Verilator elaboration only (no --build) ────────
echo ""
echo "Step 1/3: Elaborating RTL..."
verilator --sv --cc \
  --threads 1 \
  --Mdir "$OUTDIR" \
  -Irtl/pkg \
  --top systolic_array \
  $VLT_OPT \
  --x-assign fast \
  --x-initial fast \
  "$TMP_PKG" \
  rtl/core/bf16_mul.sv \
  rtl/core/fp8_mul.sv \
  rtl/core/mac_cell.sv \
  rtl/core/systolic_array.sv \
  || { rm -f "$TMP_PKG"; exit 1; }
rm -f "$TMP_PKG"

# ── Step 2: Manual compile + link (bypasses Verilator's Makefile) ──
echo "Step 2/3: Compiling..."
CFLAGS="-std=c++17 -I$OUTDIR -I$VLT_INC -I$VLT_INC/vltstd \
  -DSIM_ROWS=$SIM_SIZE -DSIM_COLS=$SIM_SIZE $COPT"
OBJS=""

# Compile all generated RTL cpp files in parallel using xargs
GENLIST=$(ls "$OUTDIR"/V*.cpp)
echo "$GENLIST" | xargs -P "$NCPU" -I{} \
  sh -c "g++ $CFLAGS -c '{}' -o '{}'.o && echo 'OK: {}' || echo 'FAIL: {}'"

# Collect .o files
for f in "$OUTDIR"/V*.cpp; do
  [[ -f "${f}.o" ]] && OBJS="$OBJS ${f}.o"
done

# Compile Verilator runtime files
for rt in verilated.cpp verilated_threads.cpp verilated_vcd_c.cpp; do
  SRC="$VLT_INC/$rt"
  OBJ="$OUTDIR/${rt}.o"
  [[ -f "$SRC" ]] || continue
  g++ $CFLAGS -c "$SRC" -o "$OBJ"
  OBJS="$OBJS $OBJ"
done

# Compile harness
g++ $CFLAGS -c verilator/sim_array_tops.cpp -o "$OUTDIR/harness.o"
OBJS="$OBJS $OUTDIR/harness.o"

# ── Step 3: Link ───────────────────────────────────────────
echo "Step 3/3: Linking..."
g++ -std=c++17 $COPT $OBJS -lpthread -o "$OUTDIR/Vsystolic_array"
echo ""
echo "Build complete."

# ── Run ────────────────────────────────────────────────────
echo "Running 500-tile TOPS test..."
echo ""
"./$OUTDIR/Vsystolic_array" --tiles 500
