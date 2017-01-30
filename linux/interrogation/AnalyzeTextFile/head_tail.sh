#!/usr/bin/env bash

head /etc/passwd                            # default first 10 lines
tail /etc/passwd                            # default last 10 lines
head -n 3 /etc/passwd                       # show first 3 line
tail -n 1 /etc/passwd                       # show last line
tail -f /var/log/message                    # leave the log file open, continue to watch last 10 lines in log file, Ctrl + C to leave