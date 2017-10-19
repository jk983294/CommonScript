#!/bin/bash

# bytes         表示收发的字节数
# packets       表示收发正确的包量
# errs          表示收发错误的包量
# drop          表示收发丢弃的包量
cat /proc/net/dev

# monitor TCP & UDP
# 平均每秒新增TCP连接数           通过/proc/net/snmp文件得到最近240秒内PassiveOpens的增量，除以240得到每秒的平均增量
# 机器的TCP连接数                通过/proc/net/snmp文件的CurrEstab得到TCP连接数
# 平均每秒的UDP接收数据报         通过/proc/net/snmp文件得到最近240秒内InDatagrams的增量，除以240得到平均每秒的UDP接收数据报
# 平均每秒的UDP发送数据报         通过/proc/net/snmp文件得到最近240秒内OutDatagrams的增量，除以240得到平均每秒的UDP发送数据报
cat /proc/net/snmp

# TCP连接的套接口
cat /proc/net/tcp

# UDP连接的套接口
cat /proc/net/udp

# UNIX域套接口的套接口表
cat /proc/net/unix

# 使用的tcp/udp/raw/pac/syc_cookies的数量
cat /proc/net/sockstat

# 静态路由表
cat /proc/net/route

# 路由缓存表
cat /proc/net/rt_cache

# 网络流量的多种统计
cat /proc/net/netstat

# 组播包统计
cat /proc/net/dev_mcast
