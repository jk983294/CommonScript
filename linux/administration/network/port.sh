#!/bin/bash

# check local machine
lsof -i                                     # list open socket
lsof -i 4                                   # only ipv4
lsof -i :22                                 # only show port 22 information
lsof -p 1385                                # show open files for process

# check remote machine
nmap                                        # network map
nmap localhost
nmap www.baidu.com
nmap -v www.baidu.com
nmap -v 192.168.0.1-5                       # group ip port check
nmap -iL to_check_ips.txt                   # monitor ip ports defined in file

# p             program
# l             only listening sockets
# a             both listening and non-listening sockets
# n             show numerical addresses instead of trying to determine symbolic host, port or user names, no need to load /etc/services
# t             tcp
# u             udp
# w             raw
# e             user
# s             statistics
# i             interface
# g             multicast group
# nr            route table
netstat -alt                                                # show all listening TCP
netstat -altpe
netstat -s
netstat -auntp | grep 60059                 # check if port be used


# ss (show socket)
# t             tcp
# u             udp
# a             all
# o             show timer information
# x             display Unix domain sockets (alias for -f unix)
ss                                                          # show established socket
ss -o state established '( dport = :ssh or sport = :ssh )'  #
ss -alt                                                     # show all listening TCP
ss -x src /dev/log
