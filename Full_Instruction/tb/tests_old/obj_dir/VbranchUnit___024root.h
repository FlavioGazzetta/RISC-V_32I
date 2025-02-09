// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VbranchUnit.h for the primary calling header

#ifndef VERILATED_VBRANCHUNIT___024ROOT_H_
#define VERILATED_VBRANCHUNIT___024ROOT_H_  // guard

#include "verilated.h"


class VbranchUnit__Syms;

class alignas(VL_CACHE_LINE_BYTES) VbranchUnit___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(aluControl,3,0);
    VL_OUT8(zero,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VactContinue;
    VL_IN(srcA,31,0);
    VL_IN(srcB,31,0);
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    VbranchUnit__Syms* const vlSymsp;

    // CONSTRUCTORS
    VbranchUnit___024root(VbranchUnit__Syms* symsp, const char* v__name);
    ~VbranchUnit___024root();
    VL_UNCOPYABLE(VbranchUnit___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
