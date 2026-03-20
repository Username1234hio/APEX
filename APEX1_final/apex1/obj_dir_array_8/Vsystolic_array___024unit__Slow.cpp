// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic_array.h for the primary calling header

#include "Vsystolic_array__pch.h"
#include "Vsystolic_array__Syms.h"
#include "Vsystolic_array___024unit.h"

void Vsystolic_array___024unit___ctor_var_reset(Vsystolic_array___024unit* vlSelf);

Vsystolic_array___024unit::Vsystolic_array___024unit(Vsystolic_array__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsystolic_array___024unit___ctor_var_reset(this);
}

void Vsystolic_array___024unit::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vsystolic_array___024unit::~Vsystolic_array___024unit() {
}
