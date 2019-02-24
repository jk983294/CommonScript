#!/bin/bash

# printing sampled functions in real time
# default sampling event is cycles and default order is descending
# it operates in processor-wide mode, monitoring all online CPUs at both user and kernel levels
perf top
perf top -C 0           # only monitor cpu 0
