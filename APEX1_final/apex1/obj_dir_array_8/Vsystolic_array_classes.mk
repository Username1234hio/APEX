# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Make include file with class lists
#
# This file lists generated Verilated files, for including in higher level makefiles.
# See Vsystolic_array.mk for the caller.

### Switches...
# C11 constructs required?  0/1 (always on now)
VM_C11 = 1
# Timing enabled?  0/1
VM_TIMING = 0
# Coverage output mode?  0/1 (from --coverage)
VM_COVERAGE = 0
# Parallel builds?  0/1 (from --output-split)
VM_PARALLEL_BUILDS = 1
# Tracing output mode?  0/1 (from --trace/--trace-fst)
VM_TRACE = 0
# Tracing output mode in VCD format?  0/1 (from --trace)
VM_TRACE_VCD = 0
# Tracing output mode in FST format?  0/1 (from --trace-fst)
VM_TRACE_FST = 0

### Object file lists...
# Generated module classes, fast-path, compile with highest optimization
VM_CLASSES_FAST += \
	Vsystolic_array \
	Vsystolic_array___024root__DepSet_h5dc85085__0 \
	Vsystolic_array___024root__DepSet_hf29b7121__0 \
	Vsystolic_array_mac_cell__DepSet_hba29e0e0__0 \
	Vsystolic_array_mac_cell__DepSet_hba29e0e0__1 \

# Generated module classes, non-fast-path, compile with low/medium optimization
VM_CLASSES_SLOW += \
	Vsystolic_array__ConstPool_0 \
	Vsystolic_array___024root__Slow \
	Vsystolic_array___024root__DepSet_h5dc85085__0__Slow \
	Vsystolic_array___024root__DepSet_hf29b7121__0__Slow \
	Vsystolic_array___024unit__Slow \
	Vsystolic_array___024unit__DepSet_h1935212e__0__Slow \
	Vsystolic_array_mac_cell__Slow \
	Vsystolic_array_mac_cell__DepSet_hba29e0e0__0__Slow \
	Vsystolic_array_mac_cell__DepSet_h4bbc20fc__0__Slow \

# Generated support classes, fast-path, compile with highest optimization
VM_SUPPORT_FAST += \

# Generated support classes, non-fast-path, compile with low/medium optimization
VM_SUPPORT_SLOW += \
	Vsystolic_array__Syms \

# Global classes, need linked once per executable, fast-path, compile with highest optimization
VM_GLOBAL_FAST += \
	verilated \
	verilated_threads \

# Global classes, need linked once per executable, non-fast-path, compile with low/medium optimization
VM_GLOBAL_SLOW += \


# Verilated -*- Makefile -*-
