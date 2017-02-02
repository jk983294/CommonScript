#!/usr/bin/env bash

top                                     # monitor, use q to quit
# l                                     toggle on/off load section from uptime
# t                                     toggle on/off task section
# m                                     toggle on/off memory utilization section
# f                                     edit fields
# up / down arrow                       choose field
# s                                     sort by that field, default is %CPU
# ESC                                   go to monitor screen
# r                                     renice
# k                                     kill
# q                                     quit

top -n 3                                # maximum number of iterations
top -n 2 -d 3                           # 3 seconds delay one iteration, so totally 6 seconds