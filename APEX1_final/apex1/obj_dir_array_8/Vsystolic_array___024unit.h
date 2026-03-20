// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsystolic_array.h for the primary calling header

#ifndef VERILATED_VSYSTOLIC_ARRAY___024UNIT_H_
#define VERILATED_VSYSTOLIC_ARRAY___024UNIT_H_  // guard

#include "verilated.h"


class Vsystolic_array__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsystolic_array___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vsystolic_array__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vsystolic_array___024unit(Vsystolic_array__Syms* symsp, const char* v__name);
    ~Vsystolic_array___024unit();
    VL_UNCOPYABLE(Vsystolic_array___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
