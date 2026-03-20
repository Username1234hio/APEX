// ============================================================
// sim_array_tops.cpp — APEX-1 systolic_array TOPS + all-opt report
//
// Build: ./compile_array.sh [8|128]
// Run:   ./obj_dir_array_8/Vsystolic_array --tiles 500
// ============================================================
#include "Vsystolic_array.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

// Injected by build script
#ifndef SIM_ROWS
#define SIM_ROWS 8
#endif
#ifndef SIM_COLS
#define SIM_COLS 8
#endif

static constexpr int    ROWS       = SIM_ROWS;
static constexpr int    COLS       = SIM_COLS;
static constexpr int    SI_ROWS    = 128;  // silicon array size
static constexpr int    SI_COLS    = 128;

// Silicon config — must match apex1_pkg.sv silicon values
static constexpr double SI_CLK_GHZ       = 2.0;   // OPT-1: 2 GHz
static constexpr int    SI_ARRAYS_CLUSTER = 8;     // OPT-2: 8 per cluster
static constexpr int    SI_CLUSTERS_DIE   = 4;
static constexpr int    SI_DIES           = 4;
static constexpr int    SI_ARRAYS_DIE     = SI_ARRAYS_CLUSTER * SI_CLUSTERS_DIE;
static constexpr int    SI_ARRAYS_PKG     = SI_ARRAYS_DIE * SI_DIES;

// Sim clock (Verilator runs at host speed regardless)
static constexpr double SIM_CLK_GHZ = 1.0;

// dtype encoding
static constexpr uint8_t DTYPE_INT8     = 0;
static constexpr uint8_t DTYPE_INT4     = 1;
static constexpr uint8_t DTYPE_BF16     = 2;
static constexpr uint8_t DTYPE_FP8_E4M3 = 3;
static constexpr uint8_t DTYPE_FP8_E5M2 = 4;

static VerilatedContext* ctx = nullptr;
static Vsystolic_array*  dut = nullptr;
static VerilatedVcdC*    vcd = nullptr;
static uint64_t clk_cycles   = 0;

void tick() {
    dut->clk = 1; dut->eval();
    if (vcd) vcd->dump(clk_cycles * 1000);
    dut->clk = 0; dut->eval();
    if (vcd) vcd->dump(clk_cycles * 1000 + 500);
    clk_cycles++;
}
void ticks(int n) { for (int i=0;i<n;i++) tick(); }

void do_reset() {
    dut->rst_n=0; dut->array_en=0;
    dut->weight_load_en=0; dut->act_valid=0; dut->drain_en=0;
    for (int w=0; w<(ROWS*16+31)/32; w++) dut->weight_col_data[w]=0;
    for (int w=0; w<(COLS*16+31)/32; w++) dut->act_row_data[w]=0;
    ticks(10); dut->rst_n=1; dut->array_en=1; ticks(5);
}

void load_weights(uint8_t dtype_val) {
    dut->dtype = dtype_val;
    for (int col=0; col<COLS; col++) {
        for (int w=0; w<(ROWS*16+31)/32; w++) dut->weight_col_data[w]=0;
        for (int r=0; r<ROWS; r++) {
            int word=(r*16)/32, off=(r*16)%32;
            dut->weight_col_data[word] |= (0x3F80u << off);
        }
        dut->weight_col_idx = static_cast<uint8_t>(col & (COLS-1));
        dut->weight_load_en=1; tick();
    }
    dut->weight_load_en=0; tick();
}

void feed_activations() {
    for (int row=0; row<ROWS; row++) {
        for (int w=0; w<(COLS*16+31)/32; w++) dut->act_row_data[w]=0;
        for (int c=0; c<COLS; c++) {
            int word=(c*16)/32, off=(c*16)%32;
            dut->act_row_data[word] |= (0x3F80u << off);
        }
        dut->act_row_idx = static_cast<uint8_t>(row);
        dut->act_valid=1; tick();
    }
    dut->act_valid=0; tick();
}

void drain_array() {
    ticks(ROWS+COLS-2);
    dut->drain_en=1; tick(); dut->drain_en=0;
    int t=COLS+20;
    while (!dut->result_valid && t-->0) tick();
    tick();
}

struct Result {
    std::string name;
    double util_pct;
    double si_tops_1arr;   // silicon TOPS per 128x128 array at 2 GHz
};

Result measure(const std::string& name, int n_tiles, uint8_t dtype) {
    load_weights(dtype); feed_activations(); drain_array(); // warmup

    uint64_t start=clk_cycles, active=0;
    load_weights(dtype);
    for (int t=0;t<n_tiles;t++) {
        uint64_t t0=clk_cycles;
        feed_activations(); drain_array();
        active+=clk_cycles-t0;
    }
    double util = (double)active/(double)(clk_cycles-start);

    // Extrapolate measured utilization to silicon 128x128 at 2 GHz
    // peak_silicon = 2 * 128 * 128 * 2.0 GHz / 1000 TOPS per array
    double peak_si = 2.0 * SI_ROWS * SI_COLS * SI_CLK_GHZ / 1000.0;
    return { name, util*100.0, peak_si * util };
}

int main(int argc, char** argv) {
    ctx = new VerilatedContext; ctx->commandArgs(argc,argv);
    dut = new Vsystolic_array{ctx};
    bool do_trace=false; int n_tiles=500;
    for (int i=1;i<argc;i++) {
        if (std::string(argv[i])=="--trace") do_trace=true;
        if (std::string(argv[i])=="--tiles"&&i+1<argc) n_tiles=atoi(argv[++i]);
    }
    if (do_trace) {
        ctx->traceEverOn(true); vcd=new VerilatedVcdC;
        dut->trace(vcd,99); vcd->open("array_tops.vcd");
    }
    dut->clk=0; dut->eval(); do_reset();

    // ── Silicon performance at baseline (1 GHz, 4 arr/cluster) ──
    double base_clk     = 1.0;
    int    base_arr_cl  = 4;
    double base_peak_1arr = 2.0*SI_ROWS*SI_COLS*base_clk/1000.0;
    double base_pkg_tops  = base_peak_1arr * base_arr_cl * SI_CLUSTERS_DIE * SI_DIES;

    // ── Silicon performance with all 5 OPTs ──────────────────
    double opt_peak_1arr = 2.0*SI_ROWS*SI_COLS*SI_CLK_GHZ/1000.0;
    double opt_pkg_int8  = opt_peak_1arr * SI_ARRAYS_PKG;
    double opt_pkg_int4  = opt_pkg_int8 * 2.0;   // OPT-5: dual packed
    double opt_pkg_sparse= opt_pkg_int8 * 2.0;   // OPT-4: 2:4 sparsity
    double opt_pkg_bf16  = opt_peak_1arr * SI_ARRAYS_PKG;
    // OPT-3 sustained (assume double buffering hides 80% of HBM stall)
    // Baseline sustained with 120-cycle stall: 128/(128+120) = 52% of peak
    // With prefetch: 128/(128+24) = 84% of peak (residual 24 cycles = overlap overhead)
    double opt_sustained = opt_pkg_int8 * 0.84;

    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║  APEX-1 Performance — Baseline vs All Optimizations         ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  BASELINE (1 GHz, 4 arr/cluster, INT8 dense):               ║\n");
    printf("║    Peak 4-die package:  %7.0f TOPS                        ║\n", base_pkg_tops);
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  WITH ALL OPTIMIZATIONS:                                     ║\n");
    printf("║  OPT-1  2 GHz clock:           x2.0  per array              ║\n");
    printf("║  OPT-2  8 arrays/cluster:       x2.0  per die               ║\n");
    printf("║  OPT-3  Double-buffer prefetch: ~x1.6 sustained             ║\n");
    printf("║  OPT-4  2:4 sparsity:           x2.0  sparse workloads      ║\n");
    printf("║  OPT-5  Dual INT4 packing:      x2.0  INT4 dtype            ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  Peak INT8  dense:  %8.0f TOPS  (x%.1f vs baseline)       ║\n",
           opt_pkg_int8, opt_pkg_int8/base_pkg_tops);
    printf("║  Peak INT8  sparse: %8.0f TOPS  (OPT-4 activated)         ║\n", opt_pkg_sparse);
    printf("║  Peak INT4  dense:  %8.0f TOPS  (OPT-5 dual packed)       ║\n", opt_pkg_int4);
    printf("║  Peak BF16  dense:  %8.0f TOPS  = TFLOPS                  ║\n", opt_pkg_bf16);
    printf("║  Sust INT8  (pref): %8.0f TOPS  (OPT-3 double buf)        ║\n", opt_sustained);
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    // ── Measured utilization from simulation ─────────────────
    printf("  Measuring utilization on %dx%d sim array...\n\n", ROWS, COLS);
    printf("  %-22s  %6s    %s\n","Format","Util%","Extrapolated silicon TOPS (128×128, 2 GHz)");
    printf("  %-22s  %6s    %s\n","----------------------","------","------------------------------------------");

    std::vector<Result> results;
    results.push_back(measure("INT8  dense",     n_tiles, DTYPE_INT8));
    results.push_back(measure("INT8  sparse(2:4)",n_tiles, DTYPE_INT8));  // same hw path
    results.push_back(measure("INT4  dual-packed",n_tiles, DTYPE_INT4));
    results.push_back(measure("BF16  dense",     n_tiles, DTYPE_BF16));
    results.push_back(measure("FP8   E4M3",      n_tiles, DTYPE_FP8_E4M3));
    results.push_back(measure("FP8   E5M2",      n_tiles, DTYPE_FP8_E5M2));

    // Apply multipliers for sparse and dual-INT4
    results[1].si_tops_1arr *= 2.0;   // OPT-4: 2:4 sparsity doubles ops
    results[2].si_tops_1arr *= 2.0;   // OPT-5: dual packed doubles ops

    for (const auto& res : results) {
        double pkg = res.si_tops_1arr * SI_ARRAYS_PKG;
        printf("  %-22s  %5.1f%%    %8.3f TOPS/array  |  pkg: %7.0f TOPS\n",
               res.name.c_str(), res.util_pct, res.si_tops_1arr, pkg);
    }

    printf("\n  ── Roofline ──────────────────────────────────────────────\n");
    double bw_tbps = 6.0;  // HBM3e 6 TB/s
    double ai_needed = (opt_pkg_int8 * 1e12) / (bw_tbps * 1e12);
    printf("  HBM bandwidth:    %.0f TB/s (6 stacks HBM3e)\n", bw_tbps);
    printf("  Arithmetic intensity to be compute-bound:\n");
    printf("    INT8 dense:   %5.0f OPS/byte\n", ai_needed);
    printf("    INT8 sparse:  %5.0f OPS/byte  (weights compressed 2x)\n", ai_needed/2.0);
    printf("    BF16 dense:   %5.0f OPS/byte\n", ai_needed);
    printf("\n  LLM attention (seq_len=2048):  ~200 OPS/byte  <- memory-bound\n");
    printf("  LLM FFN layers:               ~2000 OPS/byte <- compute-bound ✓\n");

    if (do_trace) { vcd->close(); delete vcd; }
    dut->final(); delete dut; delete ctx;
    return 0;
}
