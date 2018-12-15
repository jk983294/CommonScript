#!/bin/bash

# 用子网广播地址确定子网中所有主机
ifconfig | grep -w broadcast
#         inet 192.168.2.101  netmask 255.255.255.0  broadcast 192.168.2.255
ping -b 192.168.2.255

# multicast group membership
netstat -gn
