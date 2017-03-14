#!/usr/bin/env bash

# start/stop services manually
service sshd start
service sshd stop
service sshd restart
service sshd status                             # check status, like if this service is running

systemctl restart rsyslog.service               # after configuration then restart service
systemctl status rsyslog.service                # check status of service

# start services at startup
# Red Hat / SUSE / CentOS
chkconfig --list sshd                           # check sshd auto start status under different run level
chkconfig sshd on
chkconfig sshd off
# Debian / Ubuntu
update-rc.d ssh defaults                        # create symlink to /etc/init.d/ssh
update-rc.d -f ssh remove
