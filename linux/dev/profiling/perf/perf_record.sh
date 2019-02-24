#!/bin/bash

perf record -g ./bench                              # record call graph
perf record ./bench                                 # default per-thread mode with inherit mode enabled
perf record -F 250 ./bench                          # set sample rate, 250 sample per second
perf record -c 2000 ./bench                         # set sample period, sample every 2000 event occur
perf record -e instructions:u ./bench               # sample on event instructions only at the user level

# perf on per-cpu mode
perf record -a ./bench                              # collect all cpu
perf record -a -C 0,2-3 ./bench                     # only perf cpu 0, 2, 3


# sampling
# collect the samples to a file called perf.data
