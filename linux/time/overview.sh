#!/bin/bash

# regular tasks:
#   1) cron, more than once a day but misses job if turned off
#   2) anacron, run jobs missed on restart, once a day is the most frequent
# once off:
#   1) at, runs at specified time and date
#   2) batch, runs when load average drops below 0.8

# security
# /etc/cron.allow and /etc/cron.deny for user own cron job
# /etc/at.allow and /etc/at.deny for user own at job
# usually /etc/*.deny contains daemon accounts
# if no .allow file exists, then use .deny files for security check
# but when .allow file does exist, then only use .allow files instead of .deny files
