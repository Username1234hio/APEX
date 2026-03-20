// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsystolic_array.h for the primary calling header

#include "Vsystolic_array__pch.h"
#include "Vsystolic_array__Syms.h"
#include "Vsystolic_array_mac_cell.h"

void Vsystolic_array_mac_cell___ctor_var_reset(Vsystolic_array_mac_cell* vlSelf);

Vsystolic_array_mac_cell::Vsystolic_array_mac_cell(Vsystolic_array__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsystolic_array_mac_cell___ctor_var_reset(this);
}

void Vsystolic_array_mac_cell::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vsystolic_array_mac_cell::~Vsystolic_array_mac_cell() {
}
