#!/bin/bash

vim /etc/network/interfaces
# add below
auto enp3s0
iface enp3s0 inet static
address 192.168.2.182
netmask 255.255.255.0
gateway 192.168.31.1
dns-nameserver 192.168.31.1

sudo /etc/init.d/networking restart
