#!/usr/bin/env bash

# system up time
# current user count
# load average of last 1 minute / 5 minutes / 15 minutes
# rule of thumb: single core machine values < 1, for dual core machine values < 2, etc.
uptime

# /proc/uptime              how long system up and how long idle in seconds
cat /proc/uptime            # 1689.51 1636.53

# proc/loadavg              load averages and number of processes running
cat /proc/loadavg           # 0.07 0.02 0.00 1/346 2700, 1 running process, 346 total process, 2700 is the last process' id