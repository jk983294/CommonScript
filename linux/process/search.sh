#!/usr/bin/env bash

ps
ps -l                                       # fork state user_id pid parent_pid cpu_usage priority nice address size working tty cpu_time cmd
ps -f                                       # show user name instead of user id, add start time
ps -ef                                      # show every process
ps -efl                                     # show all process with long info

# search for process
ps -ef | grep nginx
pgrep nginx
