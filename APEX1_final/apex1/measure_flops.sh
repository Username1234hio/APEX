#!/usr/bin/env bash
# ============================================================
# measure_flops.sh — TOPS and TFLOPS measurement
# Usage:
#   ./measure_flops.sh        # 8×8 sim (~30 seconds)
#   ./measure_flops.sh 128    # 128×128 full size (~10-20 min)
# ============================================================
set -e
cd "$(dirname "$0")"

SIM_SIZE="${1:-8}"
NCPU=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
OUTDIR="obj_dir_flops_${SIM_SIZE}"
VLT_ROOT=$(verilator --getenv VERILATOR_ROOT 2>/dev/null)
VLT_INC="$VLT_ROOT/include"

[[ "$SIM_SIZE" == "128" ]] && { COPT="-O2"; VLT_OPT="-O2"; } \
                            || { COPT="-O1"; VLT_OPT="-O1"; }

[[ -d "$OUTDIR" ]] && rm -rf "$OUTDIR"

TMP_PKG=$(mktemp /tmp/apex1_pkg_sim_XXXX.sv)
sed -E "s/(parameter int ARRAY_ROWS[[:space:]]*=)[[:space:]]*[0-9]+/\1 ${SIM_SIZE}/" \
    rtl/pkg/apex1_pkg.sv | \
sed -E "s/(parameter int ARRAY_COLS[[:space:]]*=)[[:space:]]*[0-9]+/\1 ${SIM_SIZE}/" \
    > "$TMP_PKG"

echo "Elaborating (${SIM_SIZE}x${SIM_SIZE})..."
verilator --sv --cc \
  --threads 1 \
  --Mdir "$OUTDIR" \
  -Irtl/pkg \
  --top systolic_array \
  $VLT_OPT --x-assign fast --x-initial fast \
  "$TMP_PKG" \
  rtl/core/bf16_mul.sv rtl/core/fp8_mul.sv \
  rtl/core/mac_cell.sv rtl/core/systolic_array.sv \
  || { rm -f "$TMP_PKG"; exit 1; }
rm -f "$TMP_PKG"

CFLAGS="-std=c++17 -I$OUTDIR -I$VLT_INC -I$VLT_INC/vltstd \
  -DSIM_ROWS=$SIM_SIZE -DSIM_COLS=$SIM_SIZE $COPT"
OBJS=""

echo "Compiling..."
for f in "$OUTDIR"/V*.cpp; do
    g++ $CFLAGS -c "$f" -o "${f}.o" &
done
wait
for f in "$OUTDIR"/V*.cpp; do [[ -f "${f}.o" ]] && OBJS="$OBJS ${f}.o"; done

for rt in verilated.cpp verilated_threads.cpp verilated_vcd_c.cpp; do
    SRC="$VLT_INC/$rt"; OBJ="$OUTDIR/${rt}.o"
    [[ -f "$SRC" ]] && g++ $CFLAGS -c "$SRC" -o "$OBJ" && OBJS="$OBJS $OBJ"
done

g++ $CFLAGS -c verilator/sim_flops.cpp -o "$OUTDIR/flops_harness.o"
OBJS="$OBJS $OUTDIR/flops_harness.o"

echo "Linking..."
g++ -std=c++17 $COPT $OBJS -lpthread -o "$OUTDIR/Vmeasure_flops"

echo ""
"./$OUTDIR/Vmeasure_flops" --tiles 500
