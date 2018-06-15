#!/bin/bash

# packet drop/error details
ethtool -S enp3s0

# socket buffer size
sysctl net.core.wmem_default
sysctl net.core.wmem_max
sysctl net.core.rmem_default
sysctl net.core.rmem_max

sysctl -w net.core.wmem_default=262144
sysctl -w net.core.wmem_max=4194304
sysctl -w net.core.rmem_default=262144
sysctl -w net.core.rmem_max=4194304

# maximum queue size
sysctl net.core.netdev_max_backlog

# minimum, average and maximum size of the TCP read and send buffers
sysctl net.ipv4.tcp_rmem
sysctl net.ipv4.tcp_wmem

sysctl -w net.ipv4.tcp_rmem="65535 131072 4194304"
sysctl -w net.ipv4.tcp_wmem="65535 131072 194304"

# maximum pending connections
sysctl net.core.somaxconn

# UDP buffer size
sysctl net.core.rmem_max
