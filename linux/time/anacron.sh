#!/bin/bash

# anacron only support system level anacron, not user level
# anacron files
# /etc/anacrontab
# /var/spool/anacron/
# scripts scheduled by anacron:
# /etc/cron.daily
# /etc/cron.weekly
# /etc/cron.monthly

# 4 fields:
# 1) day
# 2) delay minutes after restart
# 3) job identifier (timestamp file in /var/spool/anacron indicating when job was last run)
# 4) command
1 15 daily.backup /usr/sbin/backup.sh
@weekly 15 weekly_backup /usr/sbin/weekly_backup.sh

cat /etc/anacrontab                                 # check all anacron jobs
ls /var/spool/anacron/                              # list all timestamp files
