#!/bin/bash

# logrotate, delete old logs, compress logs together to save disk space
cat /etc/logrotate.conf
cd /etc/logrotate.d/
cat /etc/cron.daily/logrotate           # cron daily logrotate script
