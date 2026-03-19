# ============================================================
# APEX-1 Synthesis Constraints
# Format: Synopsys Design Constraints (SDC) 2.1
# Compatible with: Synopsys DC, Cadence Genus, OpenROAD
#
# Target: TSMC N3E, 1.0 GHz core clock
# ============================================================

# ── Clock definitions ────────────────────────────────────────
# Primary compute clock — 1.0 GHz
create_clock -name CLK_CORE \
  -period 1.000 \
  -waveform {0.000 0.500} \
  [get_ports clk]

# HBM interface clock — 800 MHz (HBM3e operates at 6.4 Gbps/pin)
# (In real design: separate clock domain with CDC)
create_clock -name CLK_HBM \
  -period 1.250 \
  -waveform {0.000 0.625} \
  [get_ports clk_hbm]

# PCIe reference clock — 100 MHz (PCIe 5.0 refclk)
create_clock -name CLK_PCIE_REF \
  -period 10.000 \
  -waveform {0.000 5.000} \
  [get_ports clk_pcie_ref]

# UCIe die-to-die clock — 1.0 GHz
create_clock -name CLK_UCIE \
  -period 1.000 \
  [get_ports clk_ucie]

# ── Clock uncertainty and jitter ─────────────────────────────
# Include: PLL jitter (20 ps), clock skew target (30 ps),
# hold guard (20 ps)
set_clock_uncertainty -setup 0.060 [get_clocks CLK_CORE]
set_clock_uncertainty -hold  0.030 [get_clocks CLK_CORE]
set_clock_uncertainty -setup 0.080 [get_clocks CLK_HBM]
set_clock_uncertainty -hold  0.040 [get_clocks CLK_HBM]

# ── Clock transition (slew) ──────────────────────────────────
set_clock_transition 0.020 [get_clocks CLK_CORE]
set_clock_transition 0.025 [get_clocks CLK_HBM]

# ── Input/output delays ───────────────────────────────────────
# All inputs assumed to arrive 0.2 ns before clock edge
# All outputs must be stable 0.2 ns after clock edge
set_input_delay  -clock CLK_CORE -max 0.200 [all_inputs]
set_input_delay  -clock CLK_CORE -min 0.050 [all_inputs]
set_output_delay -clock CLK_CORE -max 0.200 [all_outputs]
set_output_delay -clock CLK_CORE -min 0.050 [all_outputs]

# Reset is asynchronous — no input delay constraint
set_false_path -from [get_ports rst_n]

# ── Operating conditions ─────────────────────────────────────
# TSMC N3E: worst-case SS (slow-slow) corner for setup
# Best-case FF (fast-fast) corner for hold
set_operating_conditions -library tsmc_n3e_tt_0p75v_25c \
  -analysis_type on_chip_variation

# Multi-corner analysis
create_scenario -name setup_ss
  set_operating_conditions -library tsmc_n3e_ss_0p70v_125c
  set_scenario_options -setup true -hold false

create_scenario -name hold_ff
  set_operating_conditions -library tsmc_n3e_ff_0p80v_0c
  set_scenario_options -setup false -hold true

# ── Area and power constraints ────────────────────────────────
# Target die area: 300 mm² = 300,000,000 µm²
# (With N3E density: ~160 MTr/mm² standard logic)
set_max_area 300000000

# ── Timing exceptions ─────────────────────────────────────────

# Static sequencer instruction buffer: relaxed timing
# (IBUF writes happen out-of-band, not on critical path)
set_multicycle_path -setup 2 -from [get_cells u_seq/ibuf*]
set_multicycle_path -hold  1 -from [get_cells u_seq/ibuf*]

# Power control DVFS path: 100 µs response time acceptable
# These are quasi-static signals — relax timing aggressively
set_multicycle_path -setup 16 \
  -from [get_cells u_power_ctrl/*] \
  -to   [get_cells u_power_ctrl/vrm*]
set_multicycle_path -hold  15 \
  -from [get_cells u_power_ctrl/*] \
  -to   [get_cells u_power_ctrl/vrm*]

# Temperature sensor readings: asynchronous, use false path
# (Sensors are sampled via BMC at low rate, no timing relation)
set_false_path -from [get_ports temp_sensor*]

# exp() LUT in softmax: ROM — false path from address to output
# (LUT output is registered; combinational path is long but
#  only needs to meet the 1 ns period from LUT addr register)
set_multicycle_path -setup 1 -from [get_cells u_sfu/u_softmax/exp_lut*]

# UCIe TX/RX: clock domain crossing — false paths for static signals
# (Data paths have dedicated synchronizers not modeled here)
set_false_path -from [get_clocks CLK_CORE] -to [get_clocks CLK_UCIE]
set_false_path -from [get_clocks CLK_UCIE] -to [get_clocks CLK_CORE]

# PCIe ↔ Core CDC: false path (PCIe hard IP handles sync internally)
set_false_path -from [get_clocks CLK_PCIE_REF] -to [get_clocks CLK_CORE]
set_false_path -from [get_clocks CLK_CORE] -to [get_clocks CLK_PCIE_REF]

# ── Critical path constraints ─────────────────────────────────

# MAC cell critical path: multiply → accumulate must close in 1 cycle
# The multiply is pipelined (2 stages); the final stage must meet timing
# Force synthesis to keep multiplier outputs registered
set_register_merging [get_cells u_*cluster*/gen_arrays*/gen_col*/u_mac/acc*] false

# Systolic array drain chain: 128 cells in series is too long for 1 ns
# Synthesis must pipeline with retiming — enable register retiming
set_dont_retime [get_cells u_*cluster*/gen_arrays*/gen_row*/gen_col*/u_mac*] false
# (In DC: compile -retime; in Genus: synthesize -effort high -retime)

# Scratchpad read path: SRAM output → cluster input must meet 1 cycle
# SRAM macro timing is defined in the .lib; this constraint covers logic
set_max_delay -datapath_only \
  -from [get_cells u_spad/sram*] \
  -to   [get_cells u_*cluster*/arr_weight*] \
  1.000

# ── Drive strength and load ───────────────────────────────────
# Input ports driven by external logic (I/O pads or PCIe hard IP)
set_driving_cell -lib_cell BUF_X8 -library tsmc_n3e_tt \
  [remove_from_collection [all_inputs] [get_ports {clk* rst_n}]]

# Output ports drive I/O pads (estimate 50 fF load)
set_load 0.050 [all_outputs]

# Clock ports driven by PLL output buffers
set_driving_cell -lib_cell CKBUF_X16 -library tsmc_n3e_tt \
  [get_ports {clk clk_hbm clk_ucie}]

# ── Power intent ──────────────────────────────────────────────
# (UPF/CPF power intent file handles power domains;
#  these constraints supplement for synthesis power optimization)

# Optimization: aggressive clock gating insertion
set_clock_gating_style \
  -num_stages 1 \
  -minimum_bitwidth 4 \
  -positive_edge_logic {latch} \
  -control_point before \
  -control_signal scan_enable

# Power-driven optimization: minimize switching activity on data buses
set_switching_activity -toggle_rate 0.25 -static_probability 0.5 \
  [get_nets u_*cluster*/act*]
set_switching_activity -toggle_rate 0.10 -static_probability 0.5 \
  [get_nets u_*cluster*/weights*]

# ── Design rule constraints ───────────────────────────────────
set_max_transition 0.100 [current_design]   # 100 ps max slew
set_max_fanout     16    [current_design]   # Max fanout before buffering
set_max_capacitance 0.100 [current_design]  # 100 fF max capacitance

# ── Synthesis directives ──────────────────────────────────────
# (These are DC-specific; remove for Genus or OpenROAD)

# SRAM arrays: don't touch (use characterised macros)
set_dont_touch [get_cells u_spad/sram*]
set_dont_touch [get_cells u_*cluster*/local_sram*]

# Hard IP: PCIe controller, HBM PHY — don't touch
set_dont_touch [get_cells u_pcie_hardip*]
set_dont_touch [get_cells u_hbm_phy*]

# ── Report generation after synthesis ─────────────────────────
# (Call these after compile_ultra in DC, or after synthesize in Genus)
# report_timing -nworst 10 -delay_type max > reports/timing_setup.rpt
# report_timing -nworst 10 -delay_type min > reports/timing_hold.rpt
# report_area                               > reports/area.rpt
# report_power -analysis_effort high        > reports/power.rpt
# report_clock_gating                       > reports/clock_gating.rpt
