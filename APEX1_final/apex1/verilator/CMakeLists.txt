cmake_minimum_required(VERSION 3.16)
project(apex1_verilator CXX)

# ── Find Verilator ────────────────────────────────────────
find_package(verilator HINTS $ENV{VERILATOR_ROOT})
if (NOT verilator_FOUND)
  message(FATAL_ERROR
    "Verilator not found. Install with:\n"
    "  Ubuntu/Debian: sudo apt install verilator\n"
    "  macOS:         brew install verilator\n"
    "  Or from source: https://verilator.org/guide/latest/install.html")
endif()

set(RTL_DIR   "${CMAKE_SOURCE_DIR}/../rtl")
set(TB_DIR    "${CMAKE_SOURCE_DIR}")

# ── RTL source list ───────────────────────────────────────
set(RTL_SRCS
  ${RTL_DIR}/pkg/apex1_pkg.sv
  ${RTL_DIR}/core/bf16_mul.sv
  ${RTL_DIR}/core/fp8_mul.sv
  ${RTL_DIR}/core/mac_cell.sv
  ${RTL_DIR}/core/systolic_array.sv
  ${RTL_DIR}/core/mxu_cluster.sv
  ${RTL_DIR}/memory/spad_controller.sv
  ${RTL_DIR}/memory/dma_engine.sv
  ${RTL_DIR}/special/sfu.sv
  ${RTL_DIR}/special/grad_accumulator.sv
  ${RTL_DIR}/special/allreduce_engine.sv
  ${RTL_DIR}/control/static_sequencer.sv
  ${RTL_DIR}/io/pcie_host_if.sv
  ${RTL_DIR}/apex1_die.sv
)

set(ARRAY_RTL_SRCS
  ${RTL_DIR}/pkg/apex1_pkg.sv
  ${RTL_DIR}/core/bf16_mul.sv
  ${RTL_DIR}/core/fp8_mul.sv
  ${RTL_DIR}/core/mac_cell.sv
  ${RTL_DIR}/core/systolic_array.sv
)

# Common Verilator flags
set(VLT_FLAGS
  --sv
  --timing                  # Enable timing-aware simulation
  -O3                       # Verilator optimization level
  --x-assign fast           # Treat X as 0 for speed
  --x-initial fast
  --noassert                # Skip assertions for speed (remove for debug)
  -I${RTL_DIR}/pkg
)

# ── Target 1: Full-die TOPS harness ──────────────────────
add_executable(sim_apex1_tops ${TB_DIR}/sim_tops.cpp)

verilate(sim_apex1_tops
  SOURCES        ${RTL_SRCS}
  TOP_MODULE     apex1_die
  VERILATOR_ARGS ${VLT_FLAGS} --trace --public-flat-rw
  INCLUDE_DIRS   ${RTL_DIR}/pkg
)

target_compile_options(sim_apex1_tops PRIVATE -O3 -march=native)

# ── Target 2: Single-array TOPS harness (fastest) ────────
add_executable(sim_array_tops ${TB_DIR}/sim_array_tops.cpp)

verilate(sim_array_tops
  SOURCES        ${ARRAY_RTL_SRCS}
  TOP_MODULE     systolic_array
  VERILATOR_ARGS ${VLT_FLAGS} --trace --public-flat-rw
  INCLUDE_DIRS   ${RTL_DIR}/pkg
)

target_compile_options(sim_array_tops PRIVATE -O3 -march=native)

# ── Optional: Verilator lint-only check ──────────────────
add_custom_target(lint
  COMMAND verilator --sv --lint-only
          ${VLT_FLAGS}
          ${RTL_SRCS}
  COMMENT "Running Verilator lint check on all RTL"
)

message(STATUS "Targets: sim_apex1_tops  sim_array_tops  lint")
message(STATUS "Build:   cmake -B build && cmake --build build -j$(nproc)")
message(STATUS "Run:     ./build/sim_array_tops --tiles 500")
message(STATUS "Trace:   ./build/sim_array_tops --trace --tiles 50")
