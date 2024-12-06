// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Valu__pch.h"
#include "Valu.h"
#include "Valu___024root.h"

// FUNCTIONS
Valu__Syms::~Valu__Syms()
{
}

Valu__Syms::Valu__Syms(VerilatedContext* contextp, const char* namep, Valu* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(25);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
<<<<<<< HEAD
=======
    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
    }
>>>>>>> e196d578041264977e0c3743a08c2822d1681fa1
}
