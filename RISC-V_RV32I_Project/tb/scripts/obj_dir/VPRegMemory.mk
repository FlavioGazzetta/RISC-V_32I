# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Makefile for building Verilated archive or executable
#
# Execute this makefile from the object directory:
#    make -f VPRegMemory.mk

default: /home/fg723/Documents/iac/lab0-devtools/autumn/workspace/iac-riscv-cw-24/RISC-V_RV32I_Project/tb/scripts/obj_dir/VPRegMemory

### Constants...
# Perl executable (from $PERL)
PERL = perl
# Path to Verilator kit (from $VERILATOR_ROOT)
VERILATOR_ROOT = /usr/local/share/verilator
# SystemC include directory with systemc.h (from $SYSTEMC_INCLUDE)
SYSTEMC_INCLUDE ?= 
# SystemC library directory with libsystemc.a (from $SYSTEMC_LIBDIR)
SYSTEMC_LIBDIR ?= 

### Switches...
# C++ code coverage  0/1 (from --prof-c)
VM_PROFC = 0
# SystemC output mode?  0/1 (from --sc)
VM_SC = 0
# Legacy or SystemC output mode?  0/1 (from --sc)
VM_SP_OR_SC = $(VM_SC)
# Deprecated
VM_PCLI = 1
# Deprecated: SystemC architecture to find link library path (from $SYSTEMC_ARCH)
VM_SC_TARGET_ARCH = linux

### Vars...
# Design prefix (from --prefix)
VM_PREFIX = VPRegMemory
# Module prefix (from --prefix)
VM_MODPREFIX = VPRegMemory
# User CFLAGS (from -CFLAGS on Verilator command line)
VM_USER_CFLAGS = \
	-I/usr/include/gtest \

# User LDLIBS (from -LDFLAGS on Verilator command line)
VM_USER_LDLIBS = \
	-L/usr/lib -lgtest -lgtest_main \

# User .cpp files (from .cpp's on Verilator command line)
VM_USER_CLASSES = \
	PRegMemory_tb \

# User .cpp directories (from .cpp's on Verilator command line)
VM_USER_DIR = \
	/home/fg723/Documents/iac/lab0-devtools/autumn/workspace/iac-riscv-cw-24/RISC-V_RV32I_Project/tb/tests \


### Default rules...
# Include list of all generated classes
include VPRegMemory_classes.mk
# Include global rules
include $(VERILATOR_ROOT)/include/verilated.mk

### Executable rules... (from --exe)
VPATH += $(VM_USER_DIR)

PRegMemory_tb.o: /home/fg723/Documents/iac/lab0-devtools/autumn/workspace/iac-riscv-cw-24/RISC-V_RV32I_Project/tb/tests/PRegMemory_tb.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<

### Link rules... (from --exe)
/home/fg723/Documents/iac/lab0-devtools/autumn/workspace/iac-riscv-cw-24/RISC-V_RV32I_Project/tb/scripts/obj_dir/VPRegMemory: $(VK_USER_OBJS) $(VK_GLOBAL_OBJS) $(VM_PREFIX)__ALL.a $(VM_HIER_LIBS)
	$(LINK) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) $(LIBS) $(SC_LIBS) -o $@


# Verilated -*- Makefile -*-
