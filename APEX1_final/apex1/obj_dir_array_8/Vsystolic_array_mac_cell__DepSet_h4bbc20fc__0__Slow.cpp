// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic_array.h for the primary calling header

#include "Vsystolic_array__pch.h"
#include "Vsystolic_array_mac_cell.h"

VL_ATTR_COLD void Vsystolic_array_mac_cell___ctor_var_reset(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->rst_n = 0;
    vlSelf->dtype = 0;
    vlSelf->act_in = 0;
    vlSelf->act_out = 0;
    vlSelf->wgt_in = 0;
    vlSelf->wgt_out = 0;
    vlSelf->drain_en = 0;
    vlSelf->drain_in = 0;
    vlSelf->drain_out = 0;
    vlSelf->cell_en = 0;
    vlSelf->__PVT__act_reg = 0;
    vlSelf->__PVT__wgt_reg = 0;
    vlSelf->__PVT__acc = 0;
    vlSelf->__PVT__bf16_product = 0;
    vlSelf->__PVT__fp8_product = 0;
    vlSelf->__PVT__u_bf16_mul__DOT__sign_r = 0;
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = 0;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = 0;
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = 0;
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = 0;
    vlSelf->__PVT__u_bf16_mul__DOT__mant_product = 0;
    vlSelf->__PVT__u_bf16_mul__DOT__exp_sum = 0;
    vlSelf->__PVT__u_fp8_mul__DOT__sign_r = 0;
}
