#!/bin/bash

# refresh DNS ubuntu
sudo /etc/init.d/networking restart
systemctl restart network.service

# Debian/Ubuntu
sudo /etc/rc.d/init.d/nscd restart
# Linux with systemd:
sudo systemctl restart network.service
# Fedora Linux:
sudo systemctl restart NetworkManager.service
# Arch Linux/Manjaro with Network Manager:
sudo systemctl restart NetworkManager.service
# Arch Linux/Manjaro with Wicd:
sudo systemctl restart wicd.service


hostname                                # show current hostname
cat /etc/hostname                       # show current hostname
hostname some                           # change hostname

dig www.baidu.com                       # dig DNS information
dig www.baidu.com @8.8.4.4              # ask DNS server 8.8.4.4 information
dig -t MX www.baidu.com                 # dig mail server type
dig -t AAAA ipv6.bbc.co.uk
dig -t AAAA baidu.com

host www.baidu.com                      # from domain name to ip address
host 127.0.0.1                          # from ip address to domain name

whois www.baidu.com                     # whos host/register this domian
