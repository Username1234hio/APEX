# ============================================================
# APEX-1 Verilator Makefile
# Usage:
#   make array        — compile + run single-array TOPS test
#   make fullchip     — compile + run full-die TOPS test
#   make array_trace  — same with VCD tracing enabled
#   make lint         — Verilator lint only
# ============================================================

RTL_DIR   = ../rtl
TB_DIR    = .
OBJ_DIR   = obj_dir
JOBS      = $(shell nproc 2>/dev/null || echo 4)

VLT       = verilator
VLT_FLAGS = --sv -O3 --x-assign fast --x-initial fast \
            --timing --public-flat-rw \
            -I$(RTL_DIR)/pkg

RTL_SRCS = \
  $(RTL_DIR)/pkg/apex1_pkg.sv \
  $(RTL_DIR)/core/bf16_mul.sv \
  $(RTL_DIR)/core/fp8_mul.sv \
  $(RTL_DIR)/core/mac_cell.sv \
  $(RTL_DIR)/core/systolic_array.sv \
  $(RTL_DIR)/core/mxu_cluster.sv \
  $(RTL_DIR)/memory/spad_controller.sv \
  $(RTL_DIR)/memory/dma_engine.sv \
  $(RTL_DIR)/special/sfu.sv \
  $(RTL_DIR)/special/grad_accumulator.sv \
  $(RTL_DIR)/special/allreduce_engine.sv \
  $(RTL_DIR)/control/static_sequencer.sv \
  $(RTL_DIR)/io/pcie_host_if.sv \
  $(RTL_DIR)/apex1_die.sv

ARRAY_SRCS = \
  $(RTL_DIR)/pkg/apex1_pkg.sv \
  $(RTL_DIR)/core/bf16_mul.sv \
  $(RTL_DIR)/core/fp8_mul.sv \
  $(RTL_DIR)/core/mac_cell.sv \
  $(RTL_DIR)/core/systolic_array.sv

.PHONY: array fullchip array_trace lint clean all

# ── Single-array TOPS (fastest, ~30s) ─────────────────────
array: $(OBJ_DIR)/Vsystolic_array
	@echo "Running array TOPS test..."
	$(OBJ_DIR)/Vsystolic_array --tiles 500 | tee array_tops.log
	@echo ""
	@grep "TOPS\|PASS\|Efficiency\|Extrapolated" array_tops.log

$(OBJ_DIR)/Vsystolic_array: $(ARRAY_SRCS) $(TB_DIR)/sim_array_tops.cpp
	$(VLT) $(VLT_FLAGS) --cc --exe --build -j$(JOBS) \
	  --top systolic_array \
	  $(ARRAY_SRCS) \
	  $(TB_DIR)/sim_array_tops.cpp \
	  -o Vsystolic_array
	@echo "Array harness compiled: $@"

# ── Single-array with tracing ─────────────────────────────
array_trace: $(ARRAY_SRCS) $(TB_DIR)/sim_array_tops.cpp
	$(VLT) $(VLT_FLAGS) --cc --exe --build --trace -j$(JOBS) \
	  --top systolic_array \
	  $(ARRAY_SRCS) \
	  $(TB_DIR)/sim_array_tops.cpp \
	  -o Vsystolic_array_trace
	$(OBJ_DIR)/Vsystolic_array_trace --trace --tiles 50
	@echo "Waveform: array_tops.vcd  (open with: gtkwave array_tops.vcd)"

# ── Full-die TOPS (slower, models full RTL) ───────────────
fullchip: $(OBJ_DIR)/Vapex1_die
	@echo "Running full-die TOPS test..."
	$(OBJ_DIR)/Vapex1_die | tee fullchip_tops.log
	@echo ""
	@grep "TOPS\|PASS\|FAIL\|estimate" fullchip_tops.log

$(OBJ_DIR)/Vapex1_die: $(RTL_SRCS) $(TB_DIR)/sim_tops.cpp
	$(VLT) $(VLT_FLAGS) --cc --exe --build -j$(JOBS) \
	  --top apex1_die \
	  $(RTL_SRCS) \
	  $(TB_DIR)/sim_tops.cpp \
	  -o Vapex1_die
	@echo "Full-die harness compiled: $@"

# ── Full-die with tracing ──────────────────────────────────
fullchip_trace:
	$(VLT) $(VLT_FLAGS) --cc --exe --build --trace -j$(JOBS) \
	  --top apex1_die \
	  $(RTL_SRCS) \
	  $(TB_DIR)/sim_tops.cpp \
	  -o Vapex1_die_trace
	$(OBJ_DIR)/Vapex1_die_trace --trace
	@echo "Waveform: apex1_tops.vcd"

# ── Lint only (no simulation) ─────────────────────────────
lint:
	$(VLT) $(VLT_FLAGS) --lint-only \
	  --top apex1_die \
	  $(RTL_SRCS)
	@echo "Lint passed."

# ── Clean ─────────────────────────────────────────────────
clean:
	rm -rf $(OBJ_DIR)
	rm -f  *.log *.vcd

all: array fullchip
