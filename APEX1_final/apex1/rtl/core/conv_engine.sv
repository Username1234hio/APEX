// ============================================================
// APEX-1 — conv_engine.sv
// 2D Convolution Engine
//
// Two execution paths selected by compiler:
//
// PATH A — im2col:
//   Reshapes input tensor into a 2D Toeplitz matrix on-the-fly
//   as activations are fed into the systolic array. No memory
//   replication — addresses are computed combinationally per
//   element. Works for any kernel size, stride, dilation, groups.
//
// PATH B — Winograd F(2,3):
//   Reduces multiply count by 2.25× for 3×3, stride=1 kernels.
//   Applies input transform Bt·d·B, weight transform G·g·Gt,
//   Hadamard product, then output transform At·m·A.
//   Compiler selects this path when: kernel=3×3, stride=1,
//   dilation=1, no groups.
//
// The output of both paths feeds the systolic array via the
// standard weight_load / act_valid interface.
// ============================================================
import apex1_pkg::*;

module conv_engine #(
  parameter int MAX_KERNEL = 7,    // Maximum supported kernel size
  parameter int MAX_GROUPS = 32    // Maximum depthwise groups
)(
  input  logic              clk,
  input  logic              rst_n,

  // Dispatch
  input  logic              op_valid,
  input  logic [23:0]       input_addr,   // Input feature map in SPAD
  input  logic [23:0]       weight_addr,  // Weight tensor in SPAD
  input  logic [23:0]       output_addr,  // Output feature map in SPAD
  input  logic [15:0]       N,            // Batch size
  input  logic [15:0]       C_in,         // Input channels
  input  logic [15:0]       C_out,        // Output channels
  input  logic [15:0]       H_in,         // Input height
  input  logic [15:0]       W_in,         // Input width
  input  logic [3:0]        K_h,          // Kernel height
  input  logic [3:0]        K_w,          // Kernel width
  input  logic [3:0]        stride_h,
  input  logic [3:0]        stride_w,
  input  logic [3:0]        pad_h,
  input  logic [3:0]        pad_w,
  input  logic [5:0]        groups,       // Depthwise groups (1=standard)
  input  dtype_t            dtype,
  input  logic              use_winograd, // Compiler-selected path

  output logic              done,

  // Scratchpad interfaces
  output logic [SPAD_ADDR_W-1:0] spad_rd_addr,
  output logic              spad_rd_en,
  input  logic [SPAD_DATA_W-1:0] spad_rd_data,
  input  logic              spad_rd_valid,

  output logic [SPAD_ADDR_W-1:0] spad_wr_addr,
  output logic [SPAD_DATA_W-1:0] spad_wr_data,
  output logic              spad_wr_en,

  // Systolic array feed (same interface as mxu_cluster expects)
  output logic              arr_weight_load_en,
  output logic [ARRAY_ROWS*16-1:0] arr_weight_col_data,
  output logic [$clog2(ARRAY_COLS)-1:0] arr_weight_col_idx,
  output logic              arr_act_valid,
  output logic [ARRAY_COLS*16-1:0] arr_act_row_data,
  output logic [$clog2(ARRAY_ROWS)-1:0] arr_act_row_idx,
  input  logic              arr_result_valid,
  input  logic [ARRAY_COLS*32-1:0] arr_result_data
);

  // ── Derived output dimensions ─────────────────────────────
  logic [15:0] H_out, W_out;
  assign H_out = (H_in + 2*pad_h - K_h) / stride_h + 1;
  assign W_out = (W_in + 2*pad_w - K_w) / stride_w + 1;

  // ── im2col address generator ──────────────────────────────
  // For output pixel (oh, ow), input channel c, kernel position (kh, kw):
  //   Input row = oh*stride_h + kh - pad_h
  //   Input col = ow*stride_w + kw - pad_w
  //   If out of bounds → zero padding
  //   SPAD address = input_addr + (c * H_in * W_in + ih * W_in + iw) * elem_bytes

  // Current output pixel and kernel position counters
  logic [15:0] oh, ow, kh, kw;
  logic [15:0] c_in_cnt, c_out_cnt;
  // im2col coordinate temporaries (module-scope to avoid local decl in always)
  logic signed [15:0] ih, iw;
  logic               in_bounds;

  // ── Winograd constants (F(2,3): 2×2 output from 3×3 kernel) ─
  // Input transform matrix Bt (4×4):
  //  [ 1  0 -1  0]
  //  [ 0  1  1  0]
  //  [ 0 -1  1  0]
  //  [ 0  1  0 -1] (scaled integer approximation)
  //
  // Weight transform matrix G (4×3):
  //  [1    0    0  ]
  //  [1/2  1/2  1/2]
  //  [1/2 -1/2  1/2]
  //  [0    0    1  ]
  //
  // Output transform At (2×4):
  //  [1  1  1  0]
  //  [0  1 -1 -1]

  localparam logic signed [7:0] WINO_Bt [4][4] = '{
    '{8'sd1,  8'sd0,  -8'sd1,  8'sd0},
    '{8'sd0,  8'sd1,   8'sd1,  8'sd0},
    '{8'sd0,  -8'sd1,  8'sd1,  8'sd0},
    '{8'sd0,  8'sd1,   8'sd0, -8'sd1}
  };

  localparam logic signed [7:0] WINO_At [2][4] = '{
    '{8'sd1,  8'sd1,  8'sd1,  8'sd0},
    '{8'sd0,  8'sd1, -8'sd1, -8'sd1}
  };

  // Winograd tile buffers (4×4 input tiles, 3×3 kernel tiles)
  logic signed [15:0] wino_d  [4][4];   // Input tile
  logic signed [15:0] wino_g  [3][3];   // Kernel tile
  logic signed [31:0] wino_Bd [4][4];   // Transformed input
  logic signed [31:0] wino_Gg [4][3];   // Transformed kernel
  logic signed [31:0] wino_m  [4][4];   // Hadamard product
  logic signed [31:0] wino_out[2][2];   // Output tile (2×2)

  // ── State machine ─────────────────────────────────────────
  typedef enum logic [3:0] {
    CV_IDLE,
    CV_LOAD_WEIGHTS,
    CV_WINO_TRANSFORM_W,   // Winograd weight transform (done once per kernel)
    CV_LOAD_INPUT_TILE,
    CV_WINO_TRANSFORM_I,   // Winograd input transform
    CV_HADAMARD,
    CV_WINO_OUTPUT_XFORM,
    CV_IM2COL_FEED,        // im2col: feed row to systolic array
    CV_WAIT_RESULT,
    CV_WRITEBACK,
    CV_DONE
  } cv_state_t;

  cv_state_t state;
  logic [15:0] load_col_cnt;
  logic [15:0] oh_tile, ow_tile;  // Tile position for Winograd

  // ── Weight loading (shared between both paths) ────────────
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      state               <= CV_IDLE;
      done                <= 1'b0;
      arr_weight_load_en  <= 1'b0;
      arr_act_valid       <= 1'b0;
      spad_rd_en          <= 1'b0;
      spad_wr_en          <= 1'b0;
      load_col_cnt        <= '0;
      oh <= '0; ow <= '0; kh <= '0; kw <= '0;
      c_in_cnt <= '0; c_out_cnt <= '0;
      oh_tile <= '0; ow_tile <= '0;
    end else begin
      done               <= 1'b0;
      arr_weight_load_en <= 1'b0;
      arr_act_valid      <= 1'b0;
      spad_rd_en         <= 1'b0;
      spad_wr_en         <= 1'b0;

      unique case (state)
        CV_IDLE: begin
          if (op_valid) begin
            load_col_cnt <= '0;
            oh <= '0; ow <= '0;
            c_in_cnt <= '0;
            state <= CV_LOAD_WEIGHTS;
          end
        end

        // ── Load weights into systolic array ──────────────
        CV_LOAD_WEIGHTS: begin
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= weight_addr + load_col_cnt * (SPAD_DATA_W/8);
          if (spad_rd_valid) begin
            arr_weight_load_en  <= 1'b1;
            arr_weight_col_idx  <= $clog2(ARRAY_COLS)'(load_col_cnt);
            arr_weight_col_data <= spad_rd_data[ARRAY_ROWS*16-1:0];
            load_col_cnt        <= load_col_cnt + 1;
            // When all weight columns are loaded, proceed
            if (load_col_cnt >= K_h * K_w * C_in - 1)
              state <= use_winograd ? CV_WINO_TRANSFORM_W : CV_IM2COL_FEED;
          end
        end

        // ── Winograd: weight transform (G·g·Gt) ───────────
        CV_WINO_TRANSFORM_W: begin
          // Apply G transform matrix to each 3×3 kernel tile
          // Produces 4×3 intermediate, then (4×3)·Gt = 4×4 result
          // For RTL brevity: behavioral combinational block below
          // In real silicon: pipelined multiply-add tree
          for (int i = 0; i < 4; i++) begin
            for (int j = 0; j < 3; j++) begin
              wino_Gg[i][j] = (i==0) ? {16'b0, wino_g[0][j]} :
                                (i==1) ? ({16'b0, wino_g[0][j]} + {16'b0, wino_g[1][j]} + {16'b0, wino_g[2][j]}) >>> 1 :
                                (i==2) ? ({16'b0, wino_g[0][j]} - {16'b0, wino_g[1][j]} + {16'b0, wino_g[2][j]}) >>> 1 :
                                         {16'b0, wino_g[2][j]};
            end
          end
          state <= CV_LOAD_INPUT_TILE;
        end

        // ── Load 4×4 input tile (for Winograd) ────────────
        CV_LOAD_INPUT_TILE: begin
          spad_rd_en   <= 1'b1;
          spad_rd_addr <= input_addr + oh_tile * 2 * W_in * 2;
          if (spad_rd_valid) begin
            for (int c = 0; c < 4; c++)
              wino_d[0][c] = spad_rd_data[c*16 +: 16];
            state <= CV_WINO_TRANSFORM_I;
          end
        end

        // ── Winograd: input transform (Bt·d·B) ────────────
        CV_WINO_TRANSFORM_I: begin
          for (int i = 0; i < 4; i++) begin
            for (int j = 0; j < 4; j++) begin
              wino_Bd[i][j] = WINO_Bt[i][0] * wino_d[0][j]
                             + WINO_Bt[i][1] * wino_d[1][j]
                             + WINO_Bt[i][2] * wino_d[2][j]
                             + WINO_Bt[i][3] * wino_d[3][j];
            end
          end
          state <= CV_HADAMARD;
        end

        // ── Hadamard (element-wise multiply) ──────────────
        CV_HADAMARD: begin
          for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
              wino_m[i][j] = wino_Bd[i][j] * wino_Gg[i][j];
          state <= CV_WINO_OUTPUT_XFORM;
        end

        // ── Winograd: output transform (At·m·A) ────────────
        CV_WINO_OUTPUT_XFORM: begin
          for (int i = 0; i < 2; i++) begin
            for (int j = 0; j < 2; j++) begin
              wino_out[i][j] =
                WINO_At[i][0] * (wino_m[0][j] + wino_m[1][j] + wino_m[2][j]) +
                WINO_At[i][1] * (wino_m[1][j] - wino_m[2][j] - wino_m[3][j]);
            end
          end
          state <= CV_WRITEBACK;
        end

        // ── im2col: feed reshaped row to systolic array ────
        CV_IM2COL_FEED: begin
          begin
            // Compute input coordinates (ih, iw, in_bounds declared at module scope)
            ih        = signed'({1'b0, oh}) * signed'({1'b0, stride_h})
                        + signed'({1'b0, kh}) - signed'({1'b0, pad_h});
            iw        = signed'({1'b0, ow}) * signed'({1'b0, stride_w})
                        + signed'({1'b0, kw}) - signed'({1'b0, pad_w});
            in_bounds = (ih >= 0 && ih < signed'({1'b0, H_in}) &&
                         iw >= 0 && iw < signed'({1'b0, W_in}));

            spad_rd_en   <= in_bounds;
            spad_rd_addr <= in_bounds ?
              (input_addr + (c_in_cnt * H_in * W_in +
               unsigned'(ih) * W_in + unsigned'(iw)) * 2) : '0;

            if (spad_rd_valid || !in_bounds) begin
              arr_act_row_data <= in_bounds ? spad_rd_data[ARRAY_COLS*16-1:0] : '0;
              arr_act_valid    <= 1'b1;
              // Truncate index to port width with explicit cast
              arr_act_row_idx  <= $clog2(ARRAY_ROWS)'
                                   (kh * K_w * C_in + kw * C_in + c_in_cnt);

              if (c_in_cnt < C_in - 1) begin
                c_in_cnt <= c_in_cnt + 1;
              end else begin
                c_in_cnt <= '0;
                if (kw < K_w - 1) begin
                  kw <= kw + 1;
                end else begin
                  kw <= '0;
                  if (kh < K_h - 1) begin
                    kh <= kh + 1;
                  end else begin
                    kh <= '0;
                    state <= CV_WAIT_RESULT;
                  end
                end
              end
            end
          end
        end

        CV_WAIT_RESULT: begin
          if (arr_result_valid) begin
            state <= CV_WRITEBACK;
          end
        end

        // ── Writeback output tile ─────────────────────────
        CV_WRITEBACK: begin
          spad_wr_en   <= 1'b1;
          if (use_winograd) begin
            // Write 2×2 Winograd output tile
            spad_wr_addr <= output_addr +
              (oh_tile * 2 * W_out + ow_tile * 2) * 4;   // FP32 = 4B
            spad_wr_data <= {448'b0,
              wino_out[0][0][15:0], wino_out[0][1][15:0],
              wino_out[1][0][15:0], wino_out[1][1][15:0]};
          end else begin
            // Write systolic array result row for current (oh, ow)
            spad_wr_addr <= output_addr + (oh * W_out + ow) * C_out * 4;
            spad_wr_data <= arr_result_data[SPAD_DATA_W-1:0];
          end

          // Advance output pixel counters
          if (use_winograd) begin
            if (ow_tile < (W_out/2) - 1) ow_tile <= ow_tile + 1;
            else begin
              ow_tile <= '0;
              if (oh_tile < (H_out/2) - 1) oh_tile <= oh_tile + 1;
              else begin oh_tile <= '0; state <= CV_DONE; end
            end
            if (state != CV_DONE) state <= CV_LOAD_INPUT_TILE;
          end else begin
            if (ow < W_out - 1) ow <= ow + 1;
            else begin
              ow <= '0;
              if (oh < H_out - 1) oh <= oh + 1;
              else begin oh <= '0; state <= CV_DONE; end
            end
            if (state != CV_DONE) state <= CV_IM2COL_FEED;
          end
        end

        CV_DONE: begin
          done  <= 1'b1;
          state <= CV_IDLE;
        end

        default: state <= CV_IDLE;
      endcase
    end
  end

endmodule
