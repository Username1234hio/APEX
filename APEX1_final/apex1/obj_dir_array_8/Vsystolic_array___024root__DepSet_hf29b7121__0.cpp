// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic_array.h for the primary calling header

#include "Vsystolic_array__pch.h"
#include "Vsystolic_array___024root.h"

VL_INLINE_OPT void Vsystolic_array___024root___ico_sequent__TOP__0(Vsystolic_array___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic_array___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->busy = ((IData)(vlSelf->array_en) & ((IData)(vlSelf->act_valid) 
                                                 | (VL_LTS_III(32, 0U, vlSelf->systolic_array__DOT__stagger_cnt) 
                                                    & VL_GTS_III(32, 0x10U, vlSelf->systolic_array__DOT__stagger_cnt))));
}

void Vsystolic_array___024root___eval_triggers__ico(Vsystolic_array___024root* vlSelf);
void Vsystolic_array___024root___eval_ico(Vsystolic_array___024root* vlSelf);

bool Vsystolic_array___024root___eval_phase__ico(Vsystolic_array___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic_array___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vsystolic_array___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vsystolic_array___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vsystolic_array___024root___eval_act(Vsystolic_array___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic_array___024root___eval_act\n"); );
}

extern const VlWide<8>/*255:0*/ Vsystolic_array__ConstPool__CONST_h9e67c271_0;

VL_INLINE_OPT void Vsystolic_array___024root___nba_sequent__TOP__0(Vsystolic_array___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic_array___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vdly__systolic_array__DOT__stagger_cnt;
    __Vdly__systolic_array__DOT__stagger_cnt = 0;
    // Body
    __Vdly__systolic_array__DOT__stagger_cnt = vlSelf->systolic_array__DOT__stagger_cnt;
    if ((1U & (~ (IData)(vlSelf->rst_n)))) {
        vlSelf->systolic_array__DOT__act_west[0U] = 0U;
        vlSelf->systolic_array__DOT__act_west[1U] = 0U;
        vlSelf->systolic_array__DOT__act_west[2U] = 0U;
        vlSelf->systolic_array__DOT__act_west[3U] = 0U;
        vlSelf->systolic_array__DOT__act_west[4U] = 0U;
        vlSelf->systolic_array__DOT__act_west[5U] = 0U;
        vlSelf->systolic_array__DOT__act_west[6U] = 0U;
        vlSelf->systolic_array__DOT__act_west[7U] = 0U;
    }
    if (vlSelf->rst_n) {
        if (((IData)(vlSelf->weight_load_en) & (IData)(vlSelf->array_en))) {
            vlSelf->systolic_array__DOT__weights[0U][vlSelf->weight_col_idx] 
                = (0xffffU & vlSelf->weight_col_data[0U]);
            vlSelf->systolic_array__DOT__weights[1U][vlSelf->weight_col_idx] 
                = (vlSelf->weight_col_data[0U] >> 0x10U);
            vlSelf->systolic_array__DOT__weights[2U][vlSelf->weight_col_idx] 
                = (0xffffU & vlSelf->weight_col_data[1U]);
            vlSelf->systolic_array__DOT__weights[3U][vlSelf->weight_col_idx] 
                = (vlSelf->weight_col_data[1U] >> 0x10U);
            vlSelf->systolic_array__DOT__weights[4U][vlSelf->weight_col_idx] 
                = (0xffffU & vlSelf->weight_col_data[2U]);
            vlSelf->systolic_array__DOT__weights[5U][vlSelf->weight_col_idx] 
                = (vlSelf->weight_col_data[2U] >> 0x10U);
            vlSelf->systolic_array__DOT__weights[6U][vlSelf->weight_col_idx] 
                = (0xffffU & vlSelf->weight_col_data[3U]);
            vlSelf->systolic_array__DOT__weights[7U][vlSelf->weight_col_idx] 
                = (vlSelf->weight_col_data[3U] >> 0x10U);
        }
        if (((IData)(vlSelf->act_valid) & (IData)(vlSelf->array_en))) {
            vlSelf->systolic_array__DOT__act_stagger[vlSelf->act_row_idx][0U] 
                = (0xffffU & vlSelf->act_row_data[0U]);
            vlSelf->systolic_array__DOT__act_stagger[vlSelf->act_row_idx][1U] 
                = (vlSelf->act_row_data[0U] >> 0x10U);
            vlSelf->systolic_array__DOT__act_stagger[vlSelf->act_row_idx][2U] 
                = (0xffffU & vlSelf->act_row_data[1U]);
            vlSelf->systolic_array__DOT__act_stagger[vlSelf->act_row_idx][3U] 
                = (vlSelf->act_row_data[1U] >> 0x10U);
            vlSelf->systolic_array__DOT__act_stagger[vlSelf->act_row_idx][4U] 
                = (0xffffU & vlSelf->act_row_data[2U]);
            vlSelf->systolic_array__DOT__act_stagger[vlSelf->act_row_idx][5U] 
                = (vlSelf->act_row_data[2U] >> 0x10U);
            vlSelf->systolic_array__DOT__act_stagger[vlSelf->act_row_idx][6U] 
                = (0xffffU & vlSelf->act_row_data[3U]);
            vlSelf->systolic_array__DOT__act_stagger[vlSelf->act_row_idx][7U] 
                = (vlSelf->act_row_data[3U] >> 0x10U);
        }
        if (((IData)(vlSelf->drain_en) & (IData)(vlSelf->array_en))) {
            vlSelf->result_data[0U] = (IData)((((QData)((IData)(
                                                                vlSelf->systolic_array__DOT__drain_bus
                                                                [1U]
                                                                [8U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 vlSelf->systolic_array__DOT__drain_bus
                                                                 [0U]
                                                                 [8U]))));
            vlSelf->result_data[1U] = (IData)(((((QData)((IData)(
                                                                 vlSelf->systolic_array__DOT__drain_bus
                                                                 [1U]
                                                                 [8U])) 
                                                 << 0x20U) 
                                                | (QData)((IData)(
                                                                  vlSelf->systolic_array__DOT__drain_bus
                                                                  [0U]
                                                                  [8U]))) 
                                               >> 0x20U));
            vlSelf->result_data[2U] = (IData)((((QData)((IData)(
                                                                vlSelf->systolic_array__DOT__drain_bus
                                                                [3U]
                                                                [8U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 vlSelf->systolic_array__DOT__drain_bus
                                                                 [2U]
                                                                 [8U]))));
            vlSelf->result_data[3U] = (IData)(((((QData)((IData)(
                                                                 vlSelf->systolic_array__DOT__drain_bus
                                                                 [3U]
                                                                 [8U])) 
                                                 << 0x20U) 
                                                | (QData)((IData)(
                                                                  vlSelf->systolic_array__DOT__drain_bus
                                                                  [2U]
                                                                  [8U]))) 
                                               >> 0x20U));
            vlSelf->result_data[4U] = (IData)((((QData)((IData)(
                                                                vlSelf->systolic_array__DOT__drain_bus
                                                                [5U]
                                                                [8U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 vlSelf->systolic_array__DOT__drain_bus
                                                                 [4U]
                                                                 [8U]))));
            vlSelf->result_data[5U] = (IData)(((((QData)((IData)(
                                                                 vlSelf->systolic_array__DOT__drain_bus
                                                                 [5U]
                                                                 [8U])) 
                                                 << 0x20U) 
                                                | (QData)((IData)(
                                                                  vlSelf->systolic_array__DOT__drain_bus
                                                                  [4U]
                                                                  [8U]))) 
                                               >> 0x20U));
            vlSelf->result_data[6U] = (IData)((((QData)((IData)(
                                                                vlSelf->systolic_array__DOT__drain_bus
                                                                [7U]
                                                                [8U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 vlSelf->systolic_array__DOT__drain_bus
                                                                 [6U]
                                                                 [8U]))));
            vlSelf->result_data[7U] = (IData)(((((QData)((IData)(
                                                                 vlSelf->systolic_array__DOT__drain_bus
                                                                 [7U]
                                                                 [8U])) 
                                                 << 0x20U) 
                                                | (QData)((IData)(
                                                                  vlSelf->systolic_array__DOT__drain_bus
                                                                  [6U]
                                                                  [8U]))) 
                                               >> 0x20U));
        }
        if (vlSelf->array_en) {
            if (((IData)(vlSelf->act_valid) & (0U == (IData)(vlSelf->act_row_idx)))) {
                __Vdly__systolic_array__DOT__stagger_cnt = 0U;
            }
            vlSelf->systolic_array__DOT__act_west[0U] 
                = (VL_LTES_III(32, 0U, vlSelf->systolic_array__DOT__stagger_cnt)
                    ? vlSelf->systolic_array__DOT__act_stagger
                   [0U][(VL_GTS_III(32, 8U, vlSelf->systolic_array__DOT__stagger_cnt)
                          ? (7U & vlSelf->systolic_array__DOT__stagger_cnt)
                          : 0U)] : 0U);
            vlSelf->systolic_array__DOT__act_west[1U] 
                = (VL_LTES_III(32, 1U, vlSelf->systolic_array__DOT__stagger_cnt)
                    ? vlSelf->systolic_array__DOT__act_stagger
                   [1U][(VL_GTS_III(32, 8U, (vlSelf->systolic_array__DOT__stagger_cnt 
                                             - (IData)(1U)))
                          ? (7U & (vlSelf->systolic_array__DOT__stagger_cnt 
                                   - (IData)(1U))) : 0U)]
                    : 0U);
            vlSelf->systolic_array__DOT__act_west[2U] 
                = (VL_LTES_III(32, 2U, vlSelf->systolic_array__DOT__stagger_cnt)
                    ? vlSelf->systolic_array__DOT__act_stagger
                   [2U][(VL_GTS_III(32, 8U, (vlSelf->systolic_array__DOT__stagger_cnt 
                                             - (IData)(2U)))
                          ? (7U & (vlSelf->systolic_array__DOT__stagger_cnt 
                                   - (IData)(2U))) : 0U)]
                    : 0U);
            vlSelf->systolic_array__DOT__act_west[3U] 
                = (VL_LTES_III(32, 3U, vlSelf->systolic_array__DOT__stagger_cnt)
                    ? vlSelf->systolic_array__DOT__act_stagger
                   [3U][(VL_GTS_III(32, 8U, (vlSelf->systolic_array__DOT__stagger_cnt 
                                             - (IData)(3U)))
                          ? (7U & (vlSelf->systolic_array__DOT__stagger_cnt 
                                   - (IData)(3U))) : 0U)]
                    : 0U);
            vlSelf->systolic_array__DOT__act_west[4U] 
                = (VL_LTES_III(32, 4U, vlSelf->systolic_array__DOT__stagger_cnt)
                    ? vlSelf->systolic_array__DOT__act_stagger
                   [4U][(VL_GTS_III(32, 8U, (vlSelf->systolic_array__DOT__stagger_cnt 
                                             - (IData)(4U)))
                          ? (7U & (vlSelf->systolic_array__DOT__stagger_cnt 
                                   - (IData)(4U))) : 0U)]
                    : 0U);
            vlSelf->systolic_array__DOT__act_west[5U] 
                = (VL_LTES_III(32, 5U, vlSelf->systolic_array__DOT__stagger_cnt)
                    ? vlSelf->systolic_array__DOT__act_stagger
                   [5U][(VL_GTS_III(32, 8U, (vlSelf->systolic_array__DOT__stagger_cnt 
                                             - (IData)(5U)))
                          ? (7U & (vlSelf->systolic_array__DOT__stagger_cnt 
                                   - (IData)(5U))) : 0U)]
                    : 0U);
            vlSelf->systolic_array__DOT__act_west[6U] 
                = (VL_LTES_III(32, 6U, vlSelf->systolic_array__DOT__stagger_cnt)
                    ? vlSelf->systolic_array__DOT__act_stagger
                   [6U][(VL_GTS_III(32, 8U, (vlSelf->systolic_array__DOT__stagger_cnt 
                                             - (IData)(6U)))
                          ? (7U & (vlSelf->systolic_array__DOT__stagger_cnt 
                                   - (IData)(6U))) : 0U)]
                    : 0U);
            vlSelf->systolic_array__DOT__act_west[7U] 
                = (VL_LTES_III(32, 7U, vlSelf->systolic_array__DOT__stagger_cnt)
                    ? vlSelf->systolic_array__DOT__act_stagger
                   [7U][(VL_GTS_III(32, 8U, (vlSelf->systolic_array__DOT__stagger_cnt 
                                             - (IData)(7U)))
                          ? (7U & (vlSelf->systolic_array__DOT__stagger_cnt 
                                   - (IData)(7U))) : 0U)]
                    : 0U);
            __Vdly__systolic_array__DOT__stagger_cnt 
                = ((IData)(1U) + vlSelf->systolic_array__DOT__stagger_cnt);
        }
    } else {
        vlSelf->systolic_array__DOT__weights[0U][0U] = 0U;
        vlSelf->systolic_array__DOT__weights[0U][1U] = 0U;
        vlSelf->systolic_array__DOT__weights[0U][2U] = 0U;
        vlSelf->systolic_array__DOT__weights[0U][3U] = 0U;
        vlSelf->systolic_array__DOT__weights[0U][4U] = 0U;
        vlSelf->systolic_array__DOT__weights[0U][5U] = 0U;
        vlSelf->systolic_array__DOT__weights[0U][6U] = 0U;
        vlSelf->systolic_array__DOT__weights[0U][7U] = 0U;
        vlSelf->systolic_array__DOT__weights[1U][0U] = 0U;
        vlSelf->systolic_array__DOT__weights[1U][1U] = 0U;
        vlSelf->systolic_array__DOT__weights[1U][2U] = 0U;
        vlSelf->systolic_array__DOT__weights[1U][3U] = 0U;
        vlSelf->systolic_array__DOT__weights[1U][4U] = 0U;
        vlSelf->systolic_array__DOT__weights[1U][5U] = 0U;
        vlSelf->systolic_array__DOT__weights[1U][6U] = 0U;
        vlSelf->systolic_array__DOT__weights[1U][7U] = 0U;
        vlSelf->systolic_array__DOT__weights[2U][0U] = 0U;
        vlSelf->systolic_array__DOT__weights[2U][1U] = 0U;
        vlSelf->systolic_array__DOT__weights[2U][2U] = 0U;
        vlSelf->systolic_array__DOT__weights[2U][3U] = 0U;
        vlSelf->systolic_array__DOT__weights[2U][4U] = 0U;
        vlSelf->systolic_array__DOT__weights[2U][5U] = 0U;
        vlSelf->systolic_array__DOT__weights[2U][6U] = 0U;
        vlSelf->systolic_array__DOT__weights[2U][7U] = 0U;
        vlSelf->systolic_array__DOT__weights[3U][0U] = 0U;
        vlSelf->systolic_array__DOT__weights[3U][1U] = 0U;
        vlSelf->systolic_array__DOT__weights[3U][2U] = 0U;
        vlSelf->systolic_array__DOT__weights[3U][3U] = 0U;
        vlSelf->systolic_array__DOT__weights[3U][4U] = 0U;
        vlSelf->systolic_array__DOT__weights[3U][5U] = 0U;
        vlSelf->systolic_array__DOT__weights[3U][6U] = 0U;
        vlSelf->systolic_array__DOT__weights[3U][7U] = 0U;
        vlSelf->systolic_array__DOT__weights[4U][0U] = 0U;
        vlSelf->systolic_array__DOT__weights[4U][1U] = 0U;
        vlSelf->systolic_array__DOT__weights[4U][2U] = 0U;
        vlSelf->systolic_array__DOT__weights[4U][3U] = 0U;
        vlSelf->systolic_array__DOT__weights[4U][4U] = 0U;
        vlSelf->systolic_array__DOT__weights[4U][5U] = 0U;
        vlSelf->systolic_array__DOT__weights[4U][6U] = 0U;
        vlSelf->systolic_array__DOT__weights[4U][7U] = 0U;
        vlSelf->systolic_array__DOT__weights[5U][0U] = 0U;
        vlSelf->systolic_array__DOT__weights[5U][1U] = 0U;
        vlSelf->systolic_array__DOT__weights[5U][2U] = 0U;
        vlSelf->systolic_array__DOT__weights[5U][3U] = 0U;
        vlSelf->systolic_array__DOT__weights[5U][4U] = 0U;
        vlSelf->systolic_array__DOT__weights[5U][5U] = 0U;
        vlSelf->systolic_array__DOT__weights[5U][6U] = 0U;
        vlSelf->systolic_array__DOT__weights[5U][7U] = 0U;
        vlSelf->systolic_array__DOT__weights[6U][0U] = 0U;
        vlSelf->systolic_array__DOT__weights[6U][1U] = 0U;
        vlSelf->systolic_array__DOT__weights[6U][2U] = 0U;
        vlSelf->systolic_array__DOT__weights[6U][3U] = 0U;
        vlSelf->systolic_array__DOT__weights[6U][4U] = 0U;
        vlSelf->systolic_array__DOT__weights[6U][5U] = 0U;
        vlSelf->systolic_array__DOT__weights[6U][6U] = 0U;
        vlSelf->systolic_array__DOT__weights[6U][7U] = 0U;
        vlSelf->systolic_array__DOT__weights[7U][0U] = 0U;
        vlSelf->systolic_array__DOT__weights[7U][1U] = 0U;
        vlSelf->systolic_array__DOT__weights[7U][2U] = 0U;
        vlSelf->systolic_array__DOT__weights[7U][3U] = 0U;
        vlSelf->systolic_array__DOT__weights[7U][4U] = 0U;
        vlSelf->systolic_array__DOT__weights[7U][5U] = 0U;
        vlSelf->systolic_array__DOT__weights[7U][6U] = 0U;
        vlSelf->systolic_array__DOT__weights[7U][7U] = 0U;
        vlSelf->result_data[0U] = Vsystolic_array__ConstPool__CONST_h9e67c271_0[0U];
        vlSelf->result_data[1U] = Vsystolic_array__ConstPool__CONST_h9e67c271_0[1U];
        vlSelf->result_data[2U] = Vsystolic_array__ConstPool__CONST_h9e67c271_0[2U];
        vlSelf->result_data[3U] = Vsystolic_array__ConstPool__CONST_h9e67c271_0[3U];
        vlSelf->result_data[4U] = Vsystolic_array__ConstPool__CONST_h9e67c271_0[4U];
        vlSelf->result_data[5U] = Vsystolic_array__ConstPool__CONST_h9e67c271_0[5U];
        vlSelf->result_data[6U] = Vsystolic_array__ConstPool__CONST_h9e67c271_0[6U];
        vlSelf->result_data[7U] = Vsystolic_array__ConstPool__CONST_h9e67c271_0[7U];
        vlSelf->systolic_array__DOT__act_west[0U] = 0U;
        __Vdly__systolic_array__DOT__stagger_cnt = 0U;
        vlSelf->systolic_array__DOT__act_west[1U] = 0U;
        vlSelf->systolic_array__DOT__act_west[2U] = 0U;
        vlSelf->systolic_array__DOT__act_west[3U] = 0U;
        vlSelf->systolic_array__DOT__act_west[4U] = 0U;
        vlSelf->systolic_array__DOT__act_west[5U] = 0U;
        vlSelf->systolic_array__DOT__act_west[6U] = 0U;
        vlSelf->systolic_array__DOT__act_west[7U] = 0U;
    }
    vlSelf->result_valid = ((IData)(vlSelf->rst_n) 
                            && (IData)(vlSelf->drain_en));
    vlSelf->systolic_array__DOT__stagger_cnt = __Vdly__systolic_array__DOT__stagger_cnt;
    vlSelf->busy = ((IData)(vlSelf->array_en) & ((IData)(vlSelf->act_valid) 
                                                 | (VL_LTS_III(32, 0U, vlSelf->systolic_array__DOT__stagger_cnt) 
                                                    & VL_GTS_III(32, 0x10U, vlSelf->systolic_array__DOT__stagger_cnt))));
}

void Vsystolic_array___024root___eval_triggers__act(Vsystolic_array___024root* vlSelf);

bool Vsystolic_array___024root___eval_phase__act(Vsystolic_array___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic_array___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vsystolic_array___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vsystolic_array___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void Vsystolic_array___024root___eval_nba(Vsystolic_array___024root* vlSelf);

bool Vsystolic_array___024root___eval_phase__nba(Vsystolic_array___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic_array___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vsystolic_array___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsystolic_array___024root___dump_triggers__ico(Vsystolic_array___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsystolic_array___024root___dump_triggers__nba(Vsystolic_array___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsystolic_array___024root___dump_triggers__act(Vsystolic_array___024root* vlSelf);
#endif  // VL_DEBUG

void Vsystolic_array___024root___eval(Vsystolic_array___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic_array___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vsystolic_array___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("rtl/core/systolic_array.sv", 10, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vsystolic_array___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vsystolic_array___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("rtl/core/systolic_array.sv", 10, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vsystolic_array___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("rtl/core/systolic_array.sv", 10, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vsystolic_array___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vsystolic_array___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vsystolic_array___024root___eval_debug_assertions(Vsystolic_array___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsystolic_array__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsystolic_array___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((vlSelf->dtype & 0xf8U))) {
        Verilated::overWidthError("dtype");}
    if (VL_UNLIKELY((vlSelf->weight_load_en & 0xfeU))) {
        Verilated::overWidthError("weight_load_en");}
    if (VL_UNLIKELY((vlSelf->weight_col_idx & 0xf8U))) {
        Verilated::overWidthError("weight_col_idx");}
    if (VL_UNLIKELY((vlSelf->act_valid & 0xfeU))) {
        Verilated::overWidthError("act_valid");}
    if (VL_UNLIKELY((vlSelf->act_row_idx & 0xf8U))) {
        Verilated::overWidthError("act_row_idx");}
    if (VL_UNLIKELY((vlSelf->drain_en & 0xfeU))) {
        Verilated::overWidthError("drain_en");}
    if (VL_UNLIKELY((vlSelf->array_en & 0xfeU))) {
        Verilated::overWidthError("array_en");}
}
#endif  // VL_DEBUG
