// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdmem.h for the primary calling header

#include "Vdmem__pch.h"
#include "Vdmem__Syms.h"
#include "Vdmem___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdmem___024root___dump_triggers__ico(Vdmem___024root* vlSelf);
#endif  // VL_DEBUG

void Vdmem___024root___eval_triggers__ico(Vdmem___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vdmem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdmem___024root___eval_triggers__ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.set(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdmem___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdmem___024root___dump_triggers__act(Vdmem___024root* vlSelf);
#endif  // VL_DEBUG

void Vdmem___024root___eval_triggers__act(Vdmem___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vdmem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdmem___024root___eval_triggers__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.set(0U, (((IData)(vlSelfRef.clk_i) 
                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk_i__0))) 
                                       | ((~ (IData)(vlSelfRef.rst_ni)) 
                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_ni__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk_i__0 = vlSelfRef.clk_i;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_ni__0 = vlSelfRef.rst_ni;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdmem___024root___dump_triggers__act(vlSelf);
    }
#endif
}
