// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcontroller.h for the primary calling header

#include "verilated.h"

#include "Vcontroller__Syms.h"
#include "Vcontroller___024root.h"

void Vcontroller___024root___ctor_var_reset(Vcontroller___024root* vlSelf);

Vcontroller___024root::Vcontroller___024root(Vcontroller__Syms* symsp, const char* name)
    : VerilatedModule{name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcontroller___024root___ctor_var_reset(this);
}

void Vcontroller___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vcontroller___024root::~Vcontroller___024root() {
}
