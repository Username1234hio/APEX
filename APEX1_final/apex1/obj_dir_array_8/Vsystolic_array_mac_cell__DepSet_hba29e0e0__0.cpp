// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic_array.h for the primary calling header

#include "Vsystolic_array__pch.h"
#include "Vsystolic_array__Syms.h"
#include "Vsystolic_array_mac_cell.h"

VL_INLINE_OPT void Vsystolic_array_mac_cell___ico_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___ico_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0\n"); );
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_west
                [0U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [0U][0U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [0U][0U]);
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_west
                [0U];
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [0U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__act_reg = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][0U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [0U][1U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [0U][1U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [0U][1U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][1U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [0U][2U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [0U][2U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [0U][2U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][1U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][2U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [0U][3U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [0U][3U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [0U][3U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][2U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][3U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [0U][4U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [0U][4U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [0U][4U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][3U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][4U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [0U][5U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [0U][5U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [0U][5U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][4U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][5U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [0U][6U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [0U][6U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [0U][6U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][5U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][6U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [0U][7U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [0U][7U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [0U][7U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [0U][6U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_west
                [1U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [1U][0U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [1U][0U]);
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_west
                [1U];
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [1U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__act_reg = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][0U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [1U][1U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [1U][1U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [1U][1U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][1U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [1U][2U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [1U][2U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [1U][2U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][1U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][2U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [1U][3U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [1U][3U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [1U][3U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][2U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][3U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [1U][4U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [1U][4U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [1U][4U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][3U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][4U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [1U][5U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [1U][5U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [1U][5U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][4U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][5U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [1U][6U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [1U][6U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [1U][6U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][5U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][6U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [1U][7U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [1U][7U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [1U][7U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [1U][6U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_west
                [2U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [2U][0U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [2U][0U]);
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_west
                [2U];
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [2U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__act_reg = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][0U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [2U][1U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [2U][1U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [2U][1U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][1U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [2U][2U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [2U][2U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [2U][2U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][1U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][2U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [2U][3U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [2U][3U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [2U][3U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][2U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][3U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [2U][4U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [2U][4U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [2U][4U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][3U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][4U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [2U][5U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [2U][5U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [2U][5U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][4U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][5U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [2U][6U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [2U][6U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [2U][6U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][5U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][6U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [2U][7U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [2U][7U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [2U][7U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [2U][6U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_west
                [3U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [3U][0U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [3U][0U]);
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_west
                [3U];
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [3U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__act_reg = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][0U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [3U][1U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [3U][1U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [3U][1U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][1U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [3U][2U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [3U][2U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [3U][2U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][1U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][2U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [3U][3U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [3U][3U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [3U][3U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][2U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][3U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [3U][4U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [3U][4U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [3U][4U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][3U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][4U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [3U][5U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [3U][5U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [3U][5U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][4U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][5U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [3U][6U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [3U][6U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [3U][6U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][5U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][6U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [3U][7U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [3U][7U]);
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [3U][7U];
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_e_wire
                [3U][6U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
        vlSelf->__PVT__act_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__b_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__wgt_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
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

VL_INLINE_OPT void Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0(Vsystolic_array_mac_cell* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vsystolic_array_mac_cell___nba_sequent__TOP__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac__0\n"); );
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
    IData/*31:0*/ __Vdly__acc;
    __Vdly__acc = 0;
    // Body
    __Vdly__acc = vlSelf->__PVT__acc;
    if (vlSymsp->TOP.rst_n) {
        if (vlSymsp->TOP.array_en) {
            __Vdly__acc = ((IData)(vlSymsp->TOP.drain_en)
                            ? 0U : (vlSelf->__PVT__acc 
                                    + ((4U & (IData)(vlSymsp->TOP.dtype))
                                        ? ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? 0U : 
                                           ((1U & (IData)(vlSymsp->TOP.dtype))
                                             ? 0U : vlSelf->__PVT__fp8_product))
                                        : ((2U & (IData)(vlSymsp->TOP.dtype))
                                            ? ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? vlSelf->__PVT__fp8_product
                                                : vlSelf->__PVT__bf16_product)
                                            : ((1U 
                                                & (IData)(vlSymsp->TOP.dtype))
                                                ? VL_EXTENDS_II(32,9, 
                                                                (0x1ffU 
                                                                 & (VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))) 
                                                                    + 
                                                                    VL_EXTENDS_II(9,8, 
                                                                                (0xffU 
                                                                                & VL_MULS_III(8, 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__act_reg) 
                                                                                >> 4U)))), 
                                                                                (0xffU 
                                                                                & VL_EXTENDS_II(8,4, 
                                                                                (0xfU 
                                                                                & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                                                >> 4U))))))))))
                                                : VL_EXTENDS_II(32,16, 
                                                                (0xffffU 
                                                                 & VL_MULS_III(16, 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__act_reg)))), 
                                                                               (0xffffU 
                                                                                & VL_EXTENDS_II(16,8, 
                                                                                (0xffU 
                                                                                & (IData)(vlSelf->__PVT__wgt_reg))))))))))));
        }
        vlSelf->__PVT__bf16_product = (((IData)(((0x7f80U 
                                                  == 
                                                  (0x7f80U 
                                                   & (IData)(vlSelf->__PVT__act_reg))) 
                                                 & (0U 
                                                    != 
                                                    (0x7fU 
                                                     & (IData)(vlSelf->__PVT__act_reg))))) 
                                        | (IData)((
                                                   (0x7f80U 
                                                    == 
                                                    (0x7f80U 
                                                     & (IData)(vlSelf->__PVT__wgt_reg))) 
                                                   & (0U 
                                                      != 
                                                      (0x7fU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))))))
                                        ? 0x7fc00000U
                                        : ((((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                             & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero)) 
                                            | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf) 
                                               & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero)))
                                            ? 0x7fc00000U
                                            : (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_inf) 
                                                | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_inf))
                                                ? (0x7f800000U 
                                                   | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU))
                                                : (
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__a_zero) 
                                                    | (IData)(vlSelf->__PVT__u_bf16_mul__DOT__b_zero))
                                                    ? 
                                                   ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                    << 0x1fU)
                                                    : 
                                                   ((IData)(
                                                            (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum) 
                                                              >> 9U) 
                                                             | (0U 
                                                                == (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))))
                                                     ? 
                                                    (0x7f800000U 
                                                     | ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                        << 0x1fU))
                                                     : 
                                                    (((IData)(vlSelf->__PVT__u_bf16_mul__DOT__sign_r) 
                                                      << 0x1fU) 
                                                     | ((0x7f800000U 
                                                         & (((0x8000U 
                                                              & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                              ? 
                                                             ((IData)(1U) 
                                                              + (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum))
                                                              : (IData)(vlSelf->__PVT__u_bf16_mul__DOT__exp_sum)) 
                                                            << 0x17U)) 
                                                        | ((0x8000U 
                                                            & (IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product))
                                                            ? 
                                                           (0x7fff00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 8U))
                                                            : 
                                                           (0x7ffe00U 
                                                            & ((IData)(vlSelf->__PVT__u_bf16_mul__DOT__mant_product) 
                                                               << 9U))))))))));
        if (vlSymsp->TOP.array_en) {
            vlSelf->act_out = vlSymsp->TOP.systolic_array__DOT__act_west
                [4U];
            vlSelf->drain_out = ((IData)(vlSymsp->TOP.drain_en)
                                  ? (vlSelf->__PVT__acc 
                                     + vlSymsp->TOP.systolic_array__DOT__drain_bus
                                     [4U][0U]) : vlSymsp->TOP.systolic_array__DOT__drain_bus
                                 [4U][0U]);
            vlSelf->__PVT__act_reg = vlSymsp->TOP.systolic_array__DOT__act_west
                [4U];
            vlSelf->__PVT__wgt_reg = vlSymsp->TOP.systolic_array__DOT__weights
                [4U][0U];
        }
    } else {
        __Vdly__acc = 0U;
        vlSelf->drain_out = 0U;
        vlSelf->__PVT__bf16_product = 0U;
        vlSelf->__PVT__act_reg = 0U;
        vlSelf->__PVT__wgt_reg = 0U;
    }
    vlSelf->__PVT__acc = __Vdly__acc;
    vlSelf->__PVT__u_bf16_mul__DOT__a_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__act_reg))));
    vlSelf->__PVT__u_bf16_mul__DOT__a_inf = (IData)(
                                                    (0x7f80U 
                                                     == 
                                                     (0x7fffU 
                                                      & (IData)(vlSelf->__PVT__act_reg))));
    if ((3U != (IData)(vlSymsp->TOP.dtype))) {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__act_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & ((IData)(vlSelf->__PVT__act_reg) 
                                                 >> 2U));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (6U & 
                                              ((IData)(vlSelf->__PVT__wgt_reg) 
                                               << 1U)));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                 >> 2U));
    } else {
        __PVT__u_fp8_mul__DOT__man_a = (7U & (IData)(vlSelf->__PVT__act_reg));
        __PVT__u_fp8_mul__DOT__exp_a = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__act_reg) 
                                                    >> 3U)));
        __PVT__u_fp8_mul__DOT__man_b = (7U & (IData)(vlSelf->__PVT__wgt_reg));
        __PVT__u_fp8_mul__DOT__exp_b = (0x1fU & (0xfU 
                                                 & ((IData)(vlSelf->__PVT__wgt_reg) 
                                                    >> 3U)));
    }
    vlSelf->__PVT__u_bf16_mul__DOT__b_zero = (IData)(
                                                     (0U 
                                                      == 
                                                      (0x7fffU 
                                                       & (IData)(vlSelf->__PVT__wgt_reg))));
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
