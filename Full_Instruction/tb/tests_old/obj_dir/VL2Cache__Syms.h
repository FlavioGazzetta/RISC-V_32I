// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VL2CACHE__SYMS_H_
#define VERILATED_VL2CACHE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VL2Cache.h"

// INCLUDE MODULE CLASSES
#include "VL2Cache___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VL2Cache__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VL2Cache* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VL2Cache___024root             TOP;

    // CONSTRUCTORS
    VL2Cache__Syms(VerilatedContext* contextp, const char* namep, VL2Cache* modelp);
    ~VL2Cache__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
