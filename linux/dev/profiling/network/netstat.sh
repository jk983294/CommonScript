#!/bin/bash

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
# nr            route table with numerical addresses
netstat -a                                                  # show all connections
netstat -at                                                 # show all tcp connections
netstat -au                                                 # show all udp connections
netstat -alt                                                # show all listening TCP
netstat -ant                                                # disable dns lookup for faster output
netstat -tnl                                                # show all listening TCP

sudo netstat -nlpt                                          # show process, must root privileges, otherwise only see connections started by particular user
sudo netstat -ltpe                                          # show user information

netstat -ct                                                 # output connection information continuously

netstat -g                                                  # display the multicast group information

netstat -s                                                  # print out network statistics like total number of packets received and transmitted by protocol type
netstat -st                                                 # only tcp statistics
netstat -su                                                 # only udp statistics

netstat -rn                                                 # kernel routing information

netstat -i                                                  # network interfaces
netstat -ie                                                 # human readable NIC

# print active connections, active socket connections are in "ESTABLISHED" state
netstat -atnp | grep ESTABLISHED
# continous list of active connections
watch -d -n0 "netstat -atnp | grep ESTABLISHED"
# check if a service is running
sudo netstat -aple | grep ntp
