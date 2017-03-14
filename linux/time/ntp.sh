#!/bin/bash

# /etc/ntp.conf
man 5 ntp.conf
sed -i.$(date +%F) '/^#/d;/^$/d' /etc/ntp.conf              # clean up comment and empty line, create a backup file
cat /etc/ntp.conf.2017-03-12                                # read backup

# statsdir /ver/log/ntpstats                                # setup stats file location
# server 192.168.0.3 iburst prefer                          # use local ntp server
# server 0.debian.pool.ntp.org iburst
# restrict 127.0.0.1                                        # ipv4 local host
# restrict ::1                                              # ipv6 local host

service ntp restart                                         # after configuration, restart service
