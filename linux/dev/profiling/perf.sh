#!/bin/bash

# set CPU schedule to RR priority 90
chrt -r 90 ./main
# remove cache for performance test
vmtouch -ve ./main
# bind executable to core #12
taskset -c 12 ./main

perf record -e cs ./main
perf report
perf stat ./main
perf list
