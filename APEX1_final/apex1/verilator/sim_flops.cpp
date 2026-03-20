// ============================================================
// sim_flops.cpp
// FLOPS measurement harness for APEX-1 systolic_array.
//
// Measures TFLOPS for floating-point dtypes (BF16, FP8).
// Also measures TOPS for INT8 for comparison.
//
// Key distinction:
//   TOPS  = counts ALL ops (int + float)
//   TFLOPS = counts only floating-point ops
//   FLOPS/TOPS ratio depends on workload dtype mix
//
// Build via:
//   ./measure_flops.sh        # 8x8 sim
//   ./measure_flops.sh 128    # 128x128 full size
// ============================================================

#include "Vsystolic_array.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#ifndef SIM_ROWS
#define SIM_ROWS 8
#endif
#ifndef SIM_COLS
#define SIM_COLS 8
#endif

static constexpr int    ROWS    = SIM_ROWS;
static constexpr int    COLS    = SIM_COLS;
static constexpr double CLK_GHZ = 1.0;

// dtype encoding — must match apex1_pkg.sv
static constexpr uint8_t DTYPE_INT8     = 0;
static constexpr uint8_t DTYPE_BF16     = 2;
static constexpr uint8_t DTYPE_FP8_E4M3 = 3;
static constexpr uint8_t DTYPE_FP8_E5M2 = 4;
static constexpr uint8_t DTYPE_FP32     = 5;

// Whether a dtype is floating-point (counts toward FLOPS)
static bool is_float(uint8_t dtype) {
    return dtype == DTYPE_BF16     ||
           dtype == DTYPE_FP8_E4M3 ||
           dtype == DTYPE_FP8_E5M2 ||
           dtype == DTYPE_FP32;
}

static VerilatedContext* ctx = nullptr;
static Vsystolic_array*  dut = nullptr;
static uint64_t clk_cycles   = 0;

void tick() {
    dut->clk = 1; dut->eval();
    dut->clk = 0; dut->eval();
    clk_cycles++;
}
void ticks(int n) { for (int i = 0; i < n; i++) tick(); }

void do_reset() {
    dut->rst_n = 0; dut->array_en = 0;
    dut->weight_load_en = 0; dut->act_valid = 0; dut->drain_en = 0;
    for (int w = 0; w < (ROWS*16+31)/32; w++) dut->weight_col_data[w] = 0;
    for (int w = 0; w < (COLS*16+31)/32; w++) dut->act_row_data[w]    = 0;
    ticks(10);
    dut->rst_n = 1; dut->array_en = 1;
    ticks(5);
}

void load_weights(uint8_t dtype_val) {
    dut->dtype = dtype_val;
    for (int col = 0; col < COLS; col++) {
        for (int w = 0; w < (ROWS*16+31)/32; w++) dut->weight_col_data[w] = 0;
        for (int r = 0; r < ROWS; r++) {
            int word = (r*16)/32, off = (r*16)%32;
            dut->weight_col_data[word] |= (0x3F80u << off); // BF16 1.0
        }
        dut->weight_col_idx = static_cast<uint8_t>(col & (COLS-1));
        dut->weight_load_en = 1; tick();
    }
    dut->weight_load_en = 0; tick();
}

void feed_activations() {
    for (int row = 0; row < ROWS; row++) {
        for (int w = 0; w < (COLS*16+31)/32; w++) dut->act_row_data[w] = 0;
        for (int c = 0; c < COLS; c++) {
            int word = (c*16)/32, off = (c*16)%32;
            dut->act_row_data[word] |= (0x3F80u << off);
        }
        dut->act_row_idx = static_cast<uint8_t>(row);
        dut->act_valid   = 1; tick();
    }
    dut->act_valid = 0; tick();
}

void drain_array() {
    ticks(ROWS + COLS - 2);
    dut->drain_en = 1; tick(); dut->drain_en = 0;
    int t = COLS + 20;
    while (!dut->result_valid && t-- > 0) tick();
    tick();
}

// ── Result type ─────────────────────────────────────────────
struct PerfResult {
    std::string name;
    uint8_t     dtype;
    double      util_pct;
    double      tflops_silicon;  // TFLOPS extrapolated to 128×128
    double      tops_silicon;    // TOPS  extrapolated to 128×128
    bool        is_floating;
};

PerfResult measure(const std::string& name, int n_tiles, uint8_t dtype) {
    // Ops per tile: 2 × M × N × K (multiply + accumulate)
    const long long ops = 2LL * ROWS * COLS * COLS;

    // Warmup
    load_weights(dtype); feed_activations(); drain_array();

    uint64_t start  = clk_cycles;
    uint64_t active = 0;

    load_weights(dtype); // weight-stationary
    for (int t = 0; t < n_tiles; t++) {
        uint64_t t0 = clk_cycles;
        feed_activations(); drain_array();
        active += clk_cycles - t0;
    }

    uint64_t elapsed = clk_cycles - start;
    double util      = (double)active / (double)elapsed;

    // Scale utilization to silicon peak throughput
    // Silicon peak = 2 × 128 × 128 × CLK_GHz / 1e12 TOPS per array
    double peak_silicon = 2.0 * 128.0 * 128.0 * CLK_GHZ / 1000.0;  // TOPS per 128x128 array

    PerfResult r;
    r.name          = name;
    r.dtype         = dtype;
    r.util_pct      = util * 100.0;
    r.tops_silicon  = peak_silicon * util;
    // TFLOPS = TOPS only if this dtype is floating-point
    r.tflops_silicon = is_float(dtype) ? r.tops_silicon : 0.0;
    r.is_floating   = is_float(dtype);
    return r;
}

int main(int argc, char** argv) {
    ctx = new VerilatedContext;
    ctx->commandArgs(argc, argv);
    dut = new Vsystolic_array{ctx};
    dut->clk = 0; dut->eval();
    do_reset();

    int n_tiles = 500;
    for (int i = 1; i < argc; i++)
        if (std::string(argv[i]) == "--tiles" && i+1 < argc)
            n_tiles = atoi(argv[++i]);

    // Silicon reference values (128×128 at 1 GHz)
    // Peak TOPS per 128x128 array at 1 GHz
    // = 2 MACs/cycle * 128 * 128 * 1e9 cycles/sec / 1e12 = 32.768 TOPS
    double peak_tops   = 2.0 * 128.0 * 128.0 * CLK_GHZ / 1000.0;  // TOPS per array
    double peak_tflops = peak_tops;

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║  APEX-1 Performance: TOPS and TFLOPS                    ║\n");
    printf("║  Sim: %dx%d  |  Silicon extrapolation: 128x128           ║\n", ROWS, COLS);
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║  Peak per 128×128 array @ 1 GHz:  %.4f TOPS/TFLOPS   ║\n", peak_tops);
    printf("║  Peak per die (16 arrays):        %.3f TOPS/TFLOPS  ║\n", peak_tops * 16);
    printf("║  Peak 4-die package (64 arrays):  %.2f TOPS/TFLOPS ║\n", peak_tops * 64);
    printf("╚══════════════════════════════════════════════════════════╝\n\n");

    printf("  %-20s  %6s  %10s  %10s  %s\n",
           "Format", "Util%", "TOPS(Si)", "TFLOPS(Si)", "FP?");
    printf("  %-20s  %6s  %10s  %10s  %s\n",
           "--------------------","------","----------","----------","---");

    std::vector<PerfResult> results;

    // INT8 — integer, contributes to TOPS not TFLOPS
    results.push_back(measure("INT8 dense",      n_tiles, DTYPE_INT8));
    // BF16 — 16-bit brain float, full TFLOPS
    results.push_back(measure("BF16 dense",      n_tiles, DTYPE_BF16));
    // FP8 E4M3 — 8-bit float (inference), full TFLOPS
    results.push_back(measure("FP8 E4M3 dense",  n_tiles, DTYPE_FP8_E4M3));
    // FP8 E5M2 — 8-bit float (training gradients), full TFLOPS  
    results.push_back(measure("FP8 E5M2 dense",  n_tiles, DTYPE_FP8_E5M2));

    for (const auto& r : results) {
        printf("  %-20s  %5.1f%%  %10.4f  %10s  %s\n",
               r.name.c_str(),
               r.util_pct,
               r.tops_silicon,
               r.is_floating
                   ? (std::to_string((int)(r.tflops_silicon * 10000) / 10000.0)
                      .substr(0, 8)).c_str()
                   : "    N/A   ",
               r.is_floating ? "YES" : "no");
    }

    printf("\n");
    printf("  ╔═══════════════════════════════════════════════╗\n");
    printf("  ║  Summary (1 die = 16 arrays, 4-die pkg)      ║\n");
    printf("  ╠═══════════════════════════════════════════════╣\n");

    for (const auto& r : results) {
        if (!r.is_floating) {
            printf("  ║  %-14s  die: %6.1f TOPS   pkg: %6.0f TOPS  ║\n",
                   r.name.c_str(),
                   r.tops_silicon * 16,
                   r.tops_silicon * 64);
        } else {
            printf("  ║  %-14s  die: %5.1f TFLOPS  pkg: %5.0f TFLOPS ║\n",
                   r.name.c_str(),
                   r.tflops_silicon * 16,
                   r.tflops_silicon * 64);
        }
    }

    printf("  ╚═══════════════════════════════════════════════╝\n\n");

    // Key insight: roofline model
    printf("  Roofline note:\n");
    printf("  At 6 TB/s HBM bandwidth and ~2000 TOPS INT8 peak:\n");
    printf("  Arithmetic intensity needed to be compute-bound:\n");

    double bw_tbps  = 6.0;   // HBM3e TB/s
    // ops_byte = (TOPS * 1e12 ops/s) / (TB/s * 1e12 B/s)
    // OPS/byte = package_TOPS / HBM_bandwidth_TBps  (1e12 factors cancel)
    double ops_byte = (results[0].tops_silicon * 64.0) / bw_tbps;
    printf("    %.0f OPS/byte  (INT8 matmul tiles must exceed this)\n\n", ops_byte);

    dut->final(); delete dut; delete ctx;
    return 0;
}
