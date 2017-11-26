#!/bin/bash

# ============================ system Cron =========================================
# cron files
# /etc/crontab
# /etc/cron.d
# scripts:
# /etc/cron.hourly
# /etc/cron.daily
# /etc/cron.weekly
# /etc/cron.monthly

# 7 fields: minute[0-59], hour[0-23], day of month[0-31], month[1-12], day of week[0-7], user, script
5 20 * * 1-5 root /usr/sbin/backup.sh               # every week from Mon to Fri at 8:05, run backup.sh


# ============================ user Cron =========================================
# var/spool/cron/crontabs
crontab -e                                          # add cron jobs
crontab -l                                          # list my cron jobs
crontab -r                                          # remove my cron jobs

# 6 fields: minute[0-59], hour[0-23], day of month[0-31], month[1-12], day of week[0-7], script/command
*/5 8-16 * * 1 ls /tmp                              # every 5 minutes between 8 am to 4 pm, every Monday run ls /tmp

# /etc/rsyslog.d/50-default.conf uncomment #cron.*
service rsyslog restart
service cron restart
# then check crontab log /var/log/cron.log

# check crontab service status
service cron status

# restart daemon
/etc/init.d/crond restart

# user's crontab live under /var/spool/cron
# /etc/cron.allow       user name line by line

# enable power off
systemctl enable poweroff.target
