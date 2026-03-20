// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic_array.h for the primary calling header

#include "Vsystolic_array__pch.h"
#include "Vsystolic_array__Syms.h"
#include "Vsystolic_array_mac_cell.h"

VL_ATTR_COLD void Vsystolic_array_mac_cell___stl_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___stl_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0\n"); );
    // Init
    CData/*4:0*/ __PVT__u_fp8_mul__DOT__exp_a;
    __PVT__u_fp8_mul__DOT__exp_a = 0;
    CData/*4:0*/ __PVT__u_fp8_mul__DOT__exp_b;
    __PVT__u_fp8_mul__DOT__exp_b = 0;
    CData/*2:0*/ __PVT__u_fp8_mul__DOT__man_a;
    __PVT__u_fp8_mul__DOT__man_a = 0;
    CData/*2:0*/ __PVT__u_fp8_mul__DOT__man_b;
    __PVT__u_fp8_mul__DOT__man_b = 0;
    CData/*7:0*/ __PVT__u_fp8_mul__DOT__mant_product;
    __PVT__u_fp8_mul__DOT__mant_product = 0;
    CData/*7:0*/ u_fp8_mul__DOT____VdfgExtracted_hee7dedf3__1;
    u_fp8_mul__DOT____VdfgExtracted_hee7dedf3__1 = 0;
    // Body
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__sign_r = (1U & 
                                              (((IData)(vlSelf->__PVT__act_reg) 
                                                ^ (IData)(vlSelf->__PVT__wgt_reg)) 
                                               >> 0xfU));
    vlSelf->__PVT__u_bf16_mul__DOT__mant_product = 
        (0xffffU & ((0x80U | (0x7fU & (IData)(vlSelf->__PVT__act_reg))) 
                    * (0x80U | (0x7fU & (IData)(vlSelf->__PVT__wgt_reg)))));
    vlSelf->__PVT__u_bf16_mul__DOT__exp_sum = (0x3ffU 
                                               & (((0xffU 
                                                    & ((IData)(vlSelf->__PVT__act_reg) 
                                                       >> 7U)) 
                                                   + 
                                                   (0xffU 
                                                    & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                       >> 7U))) 
                                                  - (IData)(0x7fU)));
    vlSelf->__PVT__u_fp8_mul__DOT__sign_r = (1U & (
                                                   ((IData)(vlSelf->__PVT__act_reg) 
                                                    ^ (IData)(vlSelf->__PVT__wgt_reg)) 
                                                   >> 7U));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
    }
    __PVT__u_fp8_mul__DOT__mant_product = (0xffU & 
                                           ((8U | (IData)(__PVT__u_fp8_mul__DOT__man_a)) 
                                            * (8U | (IData)(__PVT__u_fp8_mul__DOT__man_b))));
    u_fp8_mul__DOT____VdfgExtracted_hee7dedf3__1 = 
        (0xffU & (((0x1ffU & ((IData)(0x7fU) + ((IData)(__PVT__u_fp8_mul__DOT__exp_a) 
                                                - (
                                                   (3U 
                                                    != (IData)(vlSymsp->TOP.dtype))
                                                    ? 0xfU
                                                    : 7U)))) 
                   + (0x1ffU & ((IData)(0x7fU) + ((IData)(__PVT__u_fp8_mul__DOT__exp_b) 
                                                  - 
                                                  ((3U 
                                                    != (IData)(vlSymsp->TOP.dtype))
                                                    ? 0xfU
                                                    : 7U))))) 
                  - (IData)(0x7fU)));
    vlSelf->__PVT__fp8_product = ((((0U == (IData)(__PVT__u_fp8_mul__DOT__exp_a)) 
                                    & (0U == (IData)(__PVT__u_fp8_mul__DOT__man_a))) 
                                   | ((0U == (IData)(__PVT__u_fp8_mul__DOT__exp_b)) 
                                      & (0U == (IData)(__PVT__u_fp8_mul__DOT__man_b))))
                                   ? ((IData)(vlSelf->__PVT__u_fp8_mul__DOT__sign_r) 
                                      << 0x1fU) : (
                                                   ((IData)(vlSelf->__PVT__u_fp8_mul__DOT__sign_r) 
                                                    << 0x1fU) 
                                                   | ((0x7f800000U 
                                                       & (((0x80U 
                                                            & (IData)(__PVT__u_fp8_mul__DOT__mant_product))
                                                            ? 
                                                           ((IData)(1U) 
                                                            + (IData)(u_fp8_mul__DOT____VdfgExtracted_hee7dedf3__1))
                                                            : (IData)(u_fp8_mul__DOT____VdfgExtracted_hee7dedf3__1)) 
                                                          << 0x17U)) 
                                                      | ((0x80U 
                                                          & (IData)(__PVT__u_fp8_mul__DOT__mant_product))
                                                          ? 
                                                         (0x7f0000U 
                                                          & ((IData)(__PVT__u_fp8_mul__DOT__mant_product) 
                                                             << 0x10U))
                                                          : 
                                                         (0x7e0000U 
                                                          & ((IData)(__PVT__u_fp8_mul__DOT__mant_product) 
                                                             << 0x11U))))));
}
