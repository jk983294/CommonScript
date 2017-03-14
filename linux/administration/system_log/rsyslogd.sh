#!/bin/bash

rsyslogd -v                             # version

cat /etc/rsyslog.conf                   # check configuration
# /var/log/messages                     nearly everything
# /var/log/secure                       su/sudo events
# /var/log/dmesg                        kernel ring buffer messages

# rule entry example:
# local5.info /var/log/local5.log       # all local5 info above messages go to /var/log/local5.log

systemctl restart rsyslog.service       # after configuration then restart service
systemctl status rsyslog.service        # check status of service

logger -p local5.info "log begin"       # fire a log action, then check /var/log/local5.log
tail /var/log/local5.log
