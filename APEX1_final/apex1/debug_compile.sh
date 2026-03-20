#!/usr/bin/env bash
# Diagnoses build failures. Run when compile_array.sh fails.
# Usage: ./debug_compile.sh [8|128]
cd "$(dirname "$0")"

SIM_SIZE="${1:-8}"
OUTDIR="obj_dir_array_${SIM_SIZE}"
VLT_ROOT=$(verilator --getenv VERILATOR_ROOT 2>/dev/null)
VLT_INC="$VLT_ROOT/include"

rm -rf "$OUTDIR"

TMP_PKG=$(mktemp /tmp/apex1_pkg_sim_XXXX.sv)
sed -E "s/(parameter int ARRAY_ROWS[[:space:]]*=)[[:space:]]*[0-9]+/\1 ${SIM_SIZE}/" \
    rtl/pkg/apex1_pkg.sv | \
sed -E "s/(parameter int ARRAY_COLS[[:space:]]*=)[[:space:]]*[0-9]+/\1 ${SIM_SIZE}/" \
    > "$TMP_PKG"

echo "=== Step 1: Verilator elaboration ==="
verilator --sv --cc \
  --threads 1 \
  -Irtl/pkg --top systolic_array \
  --x-assign fast --x-initial fast \
  --Mdir "$OUTDIR" \
  "$TMP_PKG" \
  rtl/core/bf16_mul.sv rtl/core/fp8_mul.sv \
  rtl/core/mac_cell.sv rtl/core/systolic_array.sv
ELAB=$?
rm -f "$TMP_PKG"
echo "Exit: $ELAB"
[[ $ELAB -ne 0 ]] && exit 1

echo ""
echo "=== Step 2: Port types in generated header ==="
grep -E 'dtype|weight_col_data|act_row_data|weight_col_idx|act_row_idx|result_data' \
    "$OUTDIR/Vsystolic_array.h" | grep -v '//' | head -20

echo ""
echo "=== Step 3: Runtime files available ==="
ls "$VLT_INC"/verilated*.cpp | xargs -I{} basename {}

echo ""
echo "=== Step 4: Compile everything to .o ==="
CFLAGS="-std=c++17 -I$OUTDIR -I$VLT_INC -I$VLT_INC/vltstd -DSIM_ROWS=$SIM_SIZE -DSIM_COLS=$SIM_SIZE -O1"
OBJS=""

# Generated RTL files
for f in "$OUTDIR"/V*.cpp; do
    OUT="/tmp/dbg_$(basename $f .cpp).o"
    if g++ $CFLAGS -c "$f" -o "$OUT" 2>&1; then
        OBJS="$OBJS $OUT"
    else
        echo "FAIL: $f"
    fi
done

# Verilator runtime — include ALL runtime cpp files to satisfy all symbols
for f in "$VLT_INC"/verilated.cpp \
         "$VLT_INC"/verilated_threads.cpp \
         "$VLT_INC"/verilated_vcd_c.cpp; do
    [[ -f "$f" ]] || { echo "SKIP (not found): $f"; continue; }
    OUT="/tmp/dbg_$(basename $f .cpp).o"
    if g++ $CFLAGS -c "$f" -o "$OUT" 2>&1; then
        OBJS="$OBJS $OUT"
    else
        echo "FAIL: $f"
    fi
done

# Harness
OUT="/tmp/dbg_harness.o"
if g++ $CFLAGS -c verilator/sim_array_tops.cpp -o "$OUT" 2>&1; then
    OBJS="$OBJS $OUT"
else
    echo "FAIL: harness"
fi

echo ""
echo "=== Step 5: Link ==="
g++ -std=c++17 -O1 $OBJS -lpthread -o /tmp/Vsystolic_test 2>&1
echo "Link exit: $?"

[[ $? -eq 0 ]] && echo "" && echo "SUCCESS — binary at /tmp/Vsystolic_test" && /tmp/Vsystolic_test --tiles 10
