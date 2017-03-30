#!/usr/bin/env bash

head /etc/passwd                            # default first 10 lines
tail /etc/passwd                            # default last 10 lines

head -n 3 /etc/passwd                       # show first 3 line
head -3 /etc/passwd

tail -n 1 /etc/passwd                       # show last line
tail -n +2 file.csv                         # skip first 1 line, index base is 1, often used to skip header of csv file
tail -1 /etc/passwd
tail -f /var/log/message                    # leave the log file open, continue to watch last 10 lines in log file, Ctrl + C to leave

head -10 afile | tail -1                    # only show exactly 10th line
