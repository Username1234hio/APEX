// ============================================================
// APEX-1 — power_ctrl.sv
// Power Management Controller
//
// Responsibilities:
//   1. Dynamic Voltage & Frequency Scaling (DVFS)
//      Three operating points: PERF / BALANCED / EFFICIENCY
//      Interfaces with external VRM via PMBus (I2C-like)
//   2. Cluster power gating
//      Each MXU cluster independently power-gated when idle
//      for > IDLE_THRESH cycles
//   3. Clock gating enable signals
//      Fine-grained: individual systolic array clock enables
//   4. Thermal throttling
//      Reads 8 temperature sensors; reduces OPP if T > T_thresh
//   5. PMBus telemetry
//      Reports voltage, current, temperature to BMC via I2C
// ============================================================
`include "apex1_pkg.sv"
import apex1_pkg::*;

module power_ctrl #(
  parameter int IDLE_THRESH = 16,     // Cycles before power gating
  parameter int TEMP_WARN   = 80,     // Warning temperature (°C)
  parameter int TEMP_CRIT   = 90      // Critical throttle temperature
)(
  input  logic              clk,
  input  logic              rst_n,

  // Cluster activity signals (from sequencer/clusters)
  input  logic [CLUSTERS_PER_DIE-1:0] cluster_busy,
  input  cluster_status_t   cluster_status [CLUSTERS_PER_DIE],

  // Cluster power gate outputs
  output logic [CLUSTERS_PER_DIE-1:0] cluster_pg_en,    // 1=powered, 0=gated
  output logic [CLUSTERS_PER_DIE-1:0] cluster_clk_en,

  // Temperature sensor inputs (8 sensors, raw ADC value, 8-bit)
  // Mapping: 100 = 100°C, 0 = 0°C (1°C/LSB)
  input  logic [7:0]        temp_sensor [8],

  // DVFS operating point
  output logic [1:0]        dvfs_opp,   // 0=PERF, 1=BALANCED, 2=EFFICIENCY
  // PLL frequency select (to PLL controller)
  output logic [7:0]        pll_div,    // Clock divider: 0=1GHz, 1=800MHz, 2=500MHz

  // VRM interface (PMBus command, simplified)
  output logic              vrm_req,
  output logic [7:0]        vrm_cmd,    // 0x21=VOUT_SET
  output logic [15:0]       vrm_data,   // Target voltage in mV (e.g., 750 = 0.75V)
  input  logic              vrm_ack,

  // BMC I2C telemetry (simplified: parallel register interface)
  output logic [7:0]        telem_temp_max,    // Hottest sensor reading
  output logic [7:0]        telem_opp,         // Current OPP
  output logic [15:0]       telem_voltage_mv,  // Core voltage in mV

  // Status
  output logic              throttling,
  output logic              thermal_warn,
  output logic              thermal_crit
);

  // ── DVFS operating point parameters ──────────────────────
  typedef enum logic [1:0] {
    OPP_PERF      = 2'b00,   // 1.0 GHz / 0.75V
    OPP_BALANCED  = 2'b01,   // 800 MHz / 0.70V
    OPP_EFFICIENCY= 2'b10    // 500 MHz / 0.65V
  } opp_t;

  localparam logic [15:0] VOLT_PERF  = 16'd750;  // 750 mV
  localparam logic [15:0] VOLT_BAL   = 16'd700;  // 700 mV
  localparam logic [15:0] VOLT_EFF   = 16'd650;  // 650 mV

  localparam logic [7:0]  PLL_PERF  = 8'd0;   // Full speed
  localparam logic [7:0]  PLL_BAL   = 8'd1;   // 800 MHz
  localparam logic [7:0]  PLL_EFF   = 8'd2;   // 500 MHz

  // ── Idle counters per cluster ─────────────────────────────
  logic [5:0] idle_cnt [CLUSTERS_PER_DIE];

  // ── Temperature monitoring ────────────────────────────────
  logic [7:0] temp_max;
  always_comb begin
    temp_max = '0;
    for (int i = 0; i < 8; i++)
      if (temp_sensor[i] > temp_max) temp_max = temp_sensor[i];
  end

  assign thermal_warn = (temp_max >= TEMP_WARN);
  assign thermal_crit = (temp_max >= TEMP_CRIT);
  assign telem_temp_max = temp_max;

  // ── DVFS state machine ─────────────────────────────────────
  typedef enum logic [1:0] {
    DVFS_STABLE,
    DVFS_SCALE_UP,
    DVFS_SCALE_DOWN,
    DVFS_VRM_WAIT
  } dvfs_state_t;

  dvfs_state_t dvfs_state;
  opp_t        current_opp, target_opp;
  logic [15:0] target_voltage;
  logic [15:0] dvfs_timer;  // Hysteresis timer

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      dvfs_state      <= DVFS_STABLE;
      current_opp     <= OPP_PERF;
      target_opp      <= OPP_PERF;
      dvfs_opp        <= OPP_PERF;
      pll_div         <= PLL_PERF;
      vrm_req         <= 1'b0;
      vrm_cmd         <= 8'h21;
      vrm_data        <= VOLT_PERF;
      telem_voltage_mv<= VOLT_PERF;
      telem_opp       <= '0;
      throttling      <= 1'b0;
      dvfs_timer      <= '0;
    end else begin
      vrm_req <= 1'b0;

      unique case (dvfs_state)
        DVFS_STABLE: begin
          dvfs_timer <= dvfs_timer + 1;
          // Thermal throttling takes priority
          if (thermal_crit) begin
            target_opp  <= OPP_EFFICIENCY;
            throttling  <= 1'b1;
            dvfs_state  <= DVFS_SCALE_DOWN;
          end else if (thermal_warn) begin
            if (current_opp == OPP_PERF) begin
              target_opp <= OPP_BALANCED;
              dvfs_state <= DVFS_SCALE_DOWN;
            end
            throttling <= 1'b1;
          end else begin
            throttling <= 1'b0;
            // Normal OPP management based on cluster utilization
            // (simplified: always target PERF when not throttling)
            if (current_opp != OPP_PERF && dvfs_timer > 16'd10000) begin
              target_opp <= OPP_PERF;
              dvfs_state <= DVFS_SCALE_UP;
              dvfs_timer <= '0;
            end
          end
        end

        DVFS_SCALE_UP: begin
          // When scaling up: raise voltage first, then frequency
          target_voltage <= (target_opp == OPP_PERF)    ? VOLT_PERF :
                            (target_opp == OPP_BALANCED) ? VOLT_BAL  : VOLT_EFF;
          vrm_req  <= 1'b1;
          vrm_cmd  <= 8'h21;
          vrm_data <= target_voltage;
          dvfs_state <= DVFS_VRM_WAIT;
        end

        DVFS_SCALE_DOWN: begin
          // When scaling down: reduce frequency first, then voltage
          pll_div <= (target_opp == OPP_PERF)    ? PLL_PERF :
                     (target_opp == OPP_BALANCED) ? PLL_BAL  : PLL_EFF;
          // Now request VRM voltage reduction
          target_voltage <= (target_opp == OPP_PERF)    ? VOLT_PERF :
                            (target_opp == OPP_BALANCED) ? VOLT_BAL  : VOLT_EFF;
          vrm_req    <= 1'b1;
          vrm_cmd    <= 8'h21;
          vrm_data   <= target_voltage;
          dvfs_state <= DVFS_VRM_WAIT;
        end

        DVFS_VRM_WAIT: begin
          if (vrm_ack) begin
            current_opp      <= target_opp;
            dvfs_opp         <= {2'(target_opp)};
            telem_voltage_mv <= target_voltage;
            telem_opp        <= {6'b0, target_opp};
            // For scale-up: apply frequency after VRM confirms new voltage
            if (target_opp == OPP_PERF)       pll_div <= PLL_PERF;
            else if (target_opp == OPP_BALANCED) pll_div <= PLL_BAL;
            dvfs_state <= DVFS_STABLE;
          end
        end

        default: dvfs_state <= DVFS_STABLE;
      endcase
    end
  end

  // ── Cluster power gating ──────────────────────────────────
  generate
    for (genvar c = 0; c < CLUSTERS_PER_DIE; c++) begin : gen_pg
      always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
          idle_cnt[c]      <= '0;
          cluster_pg_en[c] <= 1'b1;
          cluster_clk_en[c]<= 1'b1;
        end else begin
          if (cluster_busy[c]) begin
            // Active: reset idle counter, ensure powered
            idle_cnt[c]       <= '0;
            cluster_pg_en[c]  <= 1'b1;
            cluster_clk_en[c] <= 1'b1;
          end else begin
            // Idle: count up
            if (idle_cnt[c] < 6'(IDLE_THRESH))
              idle_cnt[c] <= idle_cnt[c] + 1;
            else begin
              // Threshold exceeded: gate cluster
              cluster_clk_en[c] <= 1'b0;
              // Power gate after 4 extra cycles (allow clock gating to settle)
              if (idle_cnt[c] >= 6'(IDLE_THRESH + 4))
                cluster_pg_en[c] <= 1'b0;
              else
                idle_cnt[c] <= idle_cnt[c] + 1;
            end
          end
        end
      end
    end
  endgenerate

endmodule
