#!/usr/bin/env bash

# default signal is -15, -term or -sigterm
# to really kill it is -9, -kill or -sigkill, shell itself doesn't response to -15, so we need -9 to kill it
kill -l                             # show all signals
kill -9 2759                        # kill bash shell
kill -s HUP 2759
sleep 900 &
pgrep sleep                         # 2758
kill 2758                           # send term signal to process 2758
pkill sleep                         # send term signal to sleep process
killall sleep                       # send term signal to all sleep process
pkill -ujk                          # kill all jk's process
