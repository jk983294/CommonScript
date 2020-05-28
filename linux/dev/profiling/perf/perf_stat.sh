#!/bin/bash

perf stat -e cycles ./bench                                     # measure cycles event both user and kernel levels
perf stat -e cycles:u ./bench                                   # measure cycles event only user levels
perf stat -e cycles:uk ./bench                                  # measure cycles event both user and kernel levels
perf stat -e cycles,instructions,cache-misses ./bench           # measure multi events
perf stat -r 5 sleep ./bench                                    # repeated measurement with stddev info
perf stat -e cycles:u -a -C 0,2-3 ./bench                       # only perf cpu 0, 2, 3
perf stat -e dTLB-loads,dTLB-load-misses,iTLB-loads,iTLB-load-misses -p $PID

# attach to existing process
perf stat -p 2262                                               # perf pid 2262 until it get killed
perf stat -p 2262 sleep 2                                       # perf pid 2262 for 2 second
perf stat -t 2262                                               # perf tid 2262 until it get killed
perf stat -t 2262 sleep 2                                       # perf tid 2262 for 2 second

# nice format
perf stat -B ./bench                                            # comma separator
perf stat  -x, ./bench                                          # csv format with , as field delimiter

$ perf stat ./bench
# Performance counter stats for './vector_bench':
#
#          1,580.75 msec task-clock                #    0.988 CPUs utilized     # CPU time
#                12      context-switches          #    0.008 K/sec
#                 0      cpu-migrations            #    0.000 K/sec
#               137      page-faults               #    0.087 K/sec
#     5,456,818,148      cycles                    #    3.452 GHz
#    20,811,736,468      instructions              #    3.81  insn per cycle
#     5,610,991,869      branches                  # 3549.572 M/sec
#            43,588      branch-misses             #    0.00% of all branches
#
#       1.599167082 seconds time elapsed
#
#       1.580966000 seconds user
#       0.000000000 seconds sys

$ perf stat -h
# Usage: perf stat [<options>] [<command>]
#    -a, --all-cpus        system-wide collection from all CPUs
#    -C, --cpu <cpu>       list of cpus to monitor in system-wide
#    -c, --scale           scale/normalize counters
#    -D, --delay <n>       ms to wait before starting measurement after program start
#    -e, --event <event>   event selector. use 'perf list' to list available events
#    -i, --no-inherit      child tasks do not inherit counters. when attached, child will not be monitored
#    -n, --null            null run - dont start any counters
#    -o, --output <file>   output file name
#    -p, --pid <pid>       stat events on existing process id
#    -t, --tid <tid>       stat events on existing thread id
#    -r, --repeat <n>      repeat command and print average + stddev (max: 100, forever: 0)
#        --per-core        aggregate counts per physical processor core
#        --per-socket      aggregate counts per processor socket
#        --per-thread      aggregate counts per thread

# event
# software events: event are pure kernel counters
# hardware events: events is sourced from the processor itself and its Performance Monitoring Unit (PMU)
$ perf list                         # list pre defined events

# Modifiers
#Modifiers	Description	                                                Example
#u	        monitor at priv level 3, 2, 1 (user)	                    event:u
#k	        monitor at priv level 0 (kernel)	                        event:k
#h	        monitor hypervisor events on a virtualization environment	event:h
#H	        monitor host machine on a virtualization environment	    event:H
#G	        monitor guest machine on a virtualization environment	    event:G

# Limits
# there is one file descriptor used per event and either per-thread (per-thread mode) or per-cpu (system-wide),
# it is possible to reach the maximum number of open file descriptor per process as imposed by the kernel

# mode
# In per-thread mode, the counter only monitors the execution of a designated thread. When the thread is scheduled out,
#   monitoring stops. When a thread migrated from one processor to another, counters are saved on the current processor
#   and are restored on the new one.
# The per-process mode is a variant of per-thread where all threads of the process are monitored. Counts and samples
#   are aggregated at the process level. The perf_events interface allows for automatic inheritance on fork() and
#   pthread_create(). By default, the perf tool activates inheritance.
# In per-cpu mode, all threads running on the designated processors are monitored. Counts and samples are thus
#   aggregated per CPU. An event is only monitoring one CPU at a time. To monitor across multiple processors,
#   it is necessary to create multiple events. The perf tool can aggregate counts and samples across
#   multiple processors. It can also monitor only a subset of the processors.
# !!! By default, perf stat in per-thread mode, -a option go to per-cpu mode
