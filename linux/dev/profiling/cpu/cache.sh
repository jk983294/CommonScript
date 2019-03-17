#!/bin/bash

# get cache info of a machine:
ls /sys/devices/system/cpu/cpu0/cache/

cat /sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size   # cache line size 64
cat /sys/devices/system/cpu/cpu0/cache/index0/size                  # total cache size 32K
cat /sys/devices/system/cpu/cpu0/cache/index0/ways_of_associativity # associativity 8
