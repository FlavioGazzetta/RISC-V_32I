// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VbranchUnit.h for the primary calling header

#include "VbranchUnit__pch.h"
#include "VbranchUnit__Syms.h"
#include "VbranchUnit___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VbranchUnit___024root___dump_triggers__ico(VbranchUnit___024root* vlSelf);
#endif  // VL_DEBUG

void VbranchUnit___024root___eval_triggers__ico(VbranchUnit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VbranchUnit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VbranchUnit___024root___eval_triggers__ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.set(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VbranchUnit___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VbranchUnit___024root___dump_triggers__act(VbranchUnit___024root* vlSelf);
#endif  // VL_DEBUG

void VbranchUnit___024root___eval_triggers__act(VbranchUnit___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VbranchUnit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VbranchUnit___024root___eval_triggers__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VbranchUnit___024root___dump_triggers__act(vlSelf);
    }
#endif
}
