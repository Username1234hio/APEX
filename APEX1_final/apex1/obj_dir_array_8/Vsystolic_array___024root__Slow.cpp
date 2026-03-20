// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic_array.h for the primary calling header

#include "Vsystolic_array__pch.h"
#include "Vsystolic_array__Syms.h"
#include "Vsystolic_array___024root.h"

void Vsystolic_array___024root___ctor_var_reset(Vsystolic_array___024root* vlSelf);

Vsystolic_array___024root::Vsystolic_array___024root(Vsystolic_array__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsystolic_array___024root___ctor_var_reset(this);
}

void Vsystolic_array___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vsystolic_array___024root::~Vsystolic_array___024root() {
}
