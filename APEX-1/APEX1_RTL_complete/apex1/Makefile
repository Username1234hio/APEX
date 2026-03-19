# ============================================================
# APEX-1 RTL Build & Simulation Makefile
# Supports: Verilator (fast), Icarus Verilog (quick check)
# Synthesis: Yosys (open-source) or Synopsys DC (commercial)
# ============================================================

DESIGN     = apex1_die
TESTBENCH  = apex1_tb
RTL_DIR    = rtl
PKG_FILE   = $(RTL_DIR)/pkg/apex1_pkg.sv

# All RTL source files in dependency order
RTL_SRCS = \
  $(PKG_FILE) \
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

TB_SRC     = $(RTL_DIR)/apex1_tb.sv

# ── Icarus Verilog (quick syntax check & simulation) ─────────
IVERILOG   = iverilog
VVP        = vvp

.PHONY: iverilog sim clean lint synth

iverilog:
	$(IVERILOG) -g2012 -Wall \
	  -I $(RTL_DIR)/pkg \
	  $(RTL_SRCS) $(TB_SRC) \
	  -o apex1_sim.vvp
	@echo "Compilation successful"

sim: iverilog
	$(VVP) apex1_sim.vvp
	@echo "Simulation complete — waveform in apex1_sim.vcd"

# ── Verilator (fast, synthesisable subset only) ───────────────
VERILATOR  = verilator
VLT_FLAGS  = --sv --cc --exe --build --trace \
             -Wall -Wno-fatal \
             --top-module $(TESTBENCH) \
             -I $(RTL_DIR)/pkg

verilate:
	$(VERILATOR) $(VLT_FLAGS) \
	  $(RTL_SRCS) $(TB_SRC) \
	  -o apex1_verilated
	@echo "Verilator build complete"

verilate_run: verilate
	./obj_dir/apex1_verilated
	@echo "Verilator simulation done"

# ── Lint with Verilator ────────────────────────────────────────
lint:
	$(VERILATOR) --lint-only --sv -Wall \
	  -I $(RTL_DIR)/pkg \
	  $(RTL_SRCS)
	@echo "Lint complete"

# ── Open-source synthesis with Yosys (for area estimation) ───
YOSYS = yosys

synth_yosys:
	$(YOSYS) -p " \
	  read_verilog -sv $(RTL_SRCS); \
	  hierarchy -top $(DESIGN); \
	  proc; opt; techmap; opt; \
	  synth -top $(DESIGN); \
	  stat; \
	  write_verilog apex1_synth.v \
	"

# ── Clean ─────────────────────────────────────────────────────
clean:
	rm -f apex1_sim.vvp apex1_sim.vcd apex1_synth.v
	rm -rf obj_dir

# ── Help ──────────────────────────────────────────────────────
help:
	@echo "APEX-1 RTL build targets:"
	@echo "  make iverilog    — Compile with Icarus Verilog"
	@echo "  make sim         — Compile and run simulation (Icarus)"
	@echo "  make verilate    — Build with Verilator"
	@echo "  make verilate_run — Build and run (Verilator)"
	@echo "  make lint        — Run Verilator lint check"
	@echo "  make synth_yosys — Synthesize with Yosys (area estimate)"
	@echo "  make clean       — Remove build artifacts"
