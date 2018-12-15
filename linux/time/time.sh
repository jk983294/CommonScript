#!/usr/bin/env bash

uptime                                                              # how long the system has been running, how many users currently logged on, and the system load averages for the past 1, 5, 15 minutes

cal                                                                 # show calendar
cal -3                                                              # previous, current and next month surrounding today
cal 3 2017                                                          # show March 2017

# system time, time in memory
date                                                                # current date
date +%x                                                            # format current date with locale
date +%F                                                            # 2017-03-12
date "+%Y%m%d_%H%M%S"                                               # 20181215_102340 for log file name generation
date --date "4:30pm"
date --date "1 day 4:30pm"
date --date "-1 day 4:30pm"
date --date "30 days"                                               # current date + 30 days
date --date "30 days ago"                                           # current date - 30 days
date -d @1491530248                                                 # 2017年 04月 07日 星期五 09:57:28 CST
date -d @1491530248 +"%Y-%m-%d %H:%M:%S"                            # 2017-04-07 09:57:28

# hardware time, BIOS time
hwclock -r                                                          # show hardware clock
hwclock --systohc                                                   # set hwclock to system time
hwclock --hctosys                                                   # set system time to hwclock

time tar -czvf etc.tgz /etc                                         # measure the archive process with compress
