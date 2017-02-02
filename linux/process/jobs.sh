#!/usr/bin/env bash

# run multiple tasks in single console
ps                              # show current processes
sleep 180 &                     # background job sleep 180 seconds
sleep 200 &
jobs                            # show current background jobs, + means this process gain focus, fg command will bring this default process to foreground
fg 1                            # bring back job 1 to foreground
bg                              # bring current stopped (CRTL + Z) process to background