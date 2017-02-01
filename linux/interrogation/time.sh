#!/usr/bin/env bash

uptime                                                              # how long the system has been running, how many users currently logged on, and the system load averages for the past 1, 5, 15 minutes

cal                                                                 # show calendar
cal -3                                                              # previous, current and next month surrounding today
cal 3 2017                                                          # show March 2017

date                                                                # current date
date --date "30 days"                                               # current date + 30 days
date --date "30 days ago"                                           # current date - 30 days

time tar -czvf etc.tgz /etc                                         # measure the archive process with compress