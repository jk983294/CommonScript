#!/bin/bash

# /etc/services, network service (port, address)
grep http /etc/services                                     # find comon services
wc -l /etc/services                                         # how many services

strace netstat -alt 2>&1 | grep /etc/services               # prove it will read this conf
strace netstat -alt 2>&1 | grep /etc/services               # prove it will not read /etc/services conf
