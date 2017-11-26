#!/usr/bin/env bash

ps
ps -l                                       # fork state user_id pid parent_pid cpu_usage priority nice address size working tty cpu_time cmd
ps -f                                       # show user name instead of user id, add start time
ps -ef                                      # show every process
ps -efl                                     # show all process with long info
ps --forest                                 # show children relationship

# search for process
ps -ef | grep nginx
pgrep nginx

# search pid for process
pidof chrome

# kill those process
kill -USR2 $(pidof chrome)

# kill those process
pkill -f chrome

# sort by memory usage
ps aux | sort -rnk 4

# sort by CPU usage
ps aux | sort -nk 3
