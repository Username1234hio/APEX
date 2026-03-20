// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsystolic_array.h for the primary calling header

#ifndef VERILATED_VSYSTOLIC_ARRAY_MAC_CELL_H_
#define VERILATED_VSYSTOLIC_ARRAY_MAC_CELL_H_  // guard

#include "verilated.h"


class Vsystolic_array__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsystolic_array_mac_cell final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(dtype,2,0);
    VL_IN8(drain_en,0,0);
    VL_IN8(cell_en,0,0);
    CData/*0:0*/ __PVT__u_bf16_mul__DOT__sign_r;
    CData/*0:0*/ __PVT__u_bf16_mul__DOT__a_zero;
    CData/*0:0*/ __PVT__u_bf16_mul__DOT__b_zero;
    CData/*0:0*/ __PVT__u_bf16_mul__DOT__a_inf;
    CData/*0:0*/ __PVT__u_bf16_mul__DOT__b_inf;
    CData/*0:0*/ __PVT__u_fp8_mul__DOT__sign_r;
    VL_IN16(act_in,15,0);
    VL_OUT16(act_out,15,0);
    VL_IN16(wgt_in,15,0);
    VL_OUT16(wgt_out,15,0);
    SData/*15:0*/ __PVT__act_reg;
    SData/*15:0*/ __PVT__wgt_reg;
    SData/*15:0*/ __PVT__u_bf16_mul__DOT__mant_product;
    SData/*9:0*/ __PVT__u_bf16_mul__DOT__exp_sum;
    VL_IN(drain_in,31,0);
    VL_OUT(drain_out,31,0);
    IData/*31:0*/ __PVT__acc;
    IData/*31:0*/ __PVT__bf16_product;
    IData/*31:0*/ __PVT__fp8_product;

    // INTERNAL VARIABLES
    Vsystolic_array__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsystolic_array_mac_cell(Vsystolic_array__Syms* symsp, const char* v__name);
    ~Vsystolic_array_mac_cell();
    VL_UNCOPYABLE(Vsystolic_array_mac_cell);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
