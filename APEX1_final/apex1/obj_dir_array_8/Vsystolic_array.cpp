// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vsystolic_array__pch.h"

//============================================================
// Constructors

Vsystolic_array::Vsystolic_array(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vsystolic_array__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , dtype{vlSymsp->TOP.dtype}
    , weight_load_en{vlSymsp->TOP.weight_load_en}
    , weight_col_idx{vlSymsp->TOP.weight_col_idx}
    , act_valid{vlSymsp->TOP.act_valid}
    , act_row_idx{vlSymsp->TOP.act_row_idx}
    , drain_en{vlSymsp->TOP.drain_en}
    , result_valid{vlSymsp->TOP.result_valid}
    , array_en{vlSymsp->TOP.array_en}
    , busy{vlSymsp->TOP.busy}
    , weight_col_data{vlSymsp->TOP.weight_col_data}
    , act_row_data{vlSymsp->TOP.act_row_data}
    , result_data{vlSymsp->TOP.result_data}
    , __PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__0__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__1__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__2__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__3__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__4__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__5__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__6__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__0__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__1__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__2__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__3__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__4__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__5__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__6__KET____DOT__u_mac}
    , __PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac{vlSymsp->TOP.__PVT__systolic_array__DOT__gen_row__BRA__7__KET____DOT__gen_col__BRA__7__KET____DOT__u_mac}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vsystolic_array::Vsystolic_array(const char* _vcname__)
    : Vsystolic_array(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vsystolic_array::~Vsystolic_array() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vsystolic_array___024root___eval_debug_assertions(Vsystolic_array___024root* vlSelf);
#endif  // VL_DEBUG
void Vsystolic_array___024root___eval_static(Vsystolic_array___024root* vlSelf);
void Vsystolic_array___024root___eval_initial(Vsystolic_array___024root* vlSelf);
void Vsystolic_array___024root___eval_settle(Vsystolic_array___024root* vlSelf);
void Vsystolic_array___024root___eval(Vsystolic_array___024root* vlSelf);

void Vsystolic_array::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsystolic_array::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vsystolic_array___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vsystolic_array___024root___eval_static(&(vlSymsp->TOP));
        Vsystolic_array___024root___eval_initial(&(vlSymsp->TOP));
        Vsystolic_array___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vsystolic_array___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vsystolic_array::eventsPending() { return false; }

uint64_t Vsystolic_array::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vsystolic_array::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vsystolic_array___024root___eval_final(Vsystolic_array___024root* vlSelf);

VL_ATTR_COLD void Vsystolic_array::final() {
    Vsystolic_array___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vsystolic_array::hierName() const { return vlSymsp->name(); }
const char* Vsystolic_array::modelName() const { return "Vsystolic_array"; }
unsigned Vsystolic_array::threads() const { return 1; }
void Vsystolic_array::prepareClone() const { contextp()->prepareClone(); }
void Vsystolic_array::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vsystolic_array::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vsystolic_array::trace()' called on model that was Verilated without --trace option");
}
