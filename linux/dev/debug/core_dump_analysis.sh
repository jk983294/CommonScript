#!/bin/bash

# analyze Linux crash dump data or a live system
crash

# Core dump file analysis
# You just need a binary (with debugging symbols included) that is identical to the one that generated the core.
# Then you can run gdb path/to/the/binary path/to/the/core to debug it.
# When it starts up, you can use bt (for backtrace) to get a stack trace from the time of the crash.
# In the backtrace, each function invocation is given a number.
# You can use frame number (replacing number with the corresponding number in the stack trace)
# to select a particular stack frame. You can then use list to see code around that function,
# and info locals to see the local variables.
# You can also use print name_of_variable (replacing "name_of_variable" with a variable name) to see its value.
# Typing help within GDB will give you a prompt that will let you see additional commands.
gdb path/to/the/binary path/to/the/core
bt
