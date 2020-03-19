#!/bin/bash

# report virtual memory statistics
# Procs
#    r: The number of runnable processes (running or waiting for run time).
#    b: The number of processes in uninterruptible sleep. (high means I/O problem, newwork or disk)
# Memory
#    swpd: the amount of virtual memory used. (KB)
#    free: the amount of idle memory. (KB)
#    buff: the amount of memory used as buffers (contains file system metadata). (KB)
#    cache: the amount of memory used as cache (contains actual contents of files). (KB)
#    inact: the amount of inactive memory.  (-a option)
#    active: the amount of active memory.  (-a option)
# Swap
#    si: Amount of memory swapped in from disk (/s).
#    so: Amount of memory swapped to disk (/s). (high means memory leak, the leaked memory swapped out)
# IO
#    bi: Blocks received from a block device (blocks/s).
#    bo: Blocks sent to a block device (blocks/s).
# System
#    in: The number of interrupts per second, including the clock. (cat /proc/interrupts to identify the source)
#    cs: The number of context switches per second.
# CPU
#    These are percentages of total CPU time.
#    us: Time spent running non-kernel code.  (user time, including nice time)
#    sy: Time spent running kernel code.  (system time)
#    id: Time spent idle.  Prior to Linux 2.5.41, this includes IO-wait time.
#    wa: Time spent waiting for IO.  Prior to Linux 2.5.41, included in idle. (high means a hardware bottleneck)
#    st: Time stolen from a virtual machine.  Prior to Linux 2.6.11, unknown.

vmstat                      # show average stats since last reboot
vmstat 5                    # sampling every 5 second
