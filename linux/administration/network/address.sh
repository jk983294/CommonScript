#!/bin/bash

# IPv4 32 bits, 127.0.0.1
# IPv6 128 bits, 2a00:1450:4009:800::100e
# vanity IPv6 address

# ifconfig (interface config)
ifconfig                            # display the status of the currently active interfaces
ip addr show                        # display the status of the currently active interfaces
ip addr show up                     # show only running network interfaces
ip -s link show enp0s3              # show specified NIC
ip a s                              # alias of ip address show
ip -4 a                             # IPv4
ip -6 a                             # IPv6
ip r s                              # ip route show
ip route                            # ip route show
ip n s                              # ip neighbor show
ip ma s                             # ip multicast address show
ip l                                # display link, interface
ip -s l                             # show statistics for every interface

# change ip dynamic
ifconfig eth0 192.168.0.99 netmask 255.255.255.0 up
ip address add 192.168.0.99/24 dev eth0                 # assign address to dev/eth0
systemctl restart network.service

# up/down interface
ifdown ens32
ifup ens32

# static address configuration
# CentOS /etc/sysconfig/network-scripts/
# Debian /etc/network/interfaces
# SUSE /etc/sysconfig/network/

# DHCP assign
# Link-Local

# subnet
# class A: 255.0.0.0
# class B: 255.255.0.0
# class C: 255.255.255.0
