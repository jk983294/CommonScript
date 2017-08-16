#!/bin/bash

# Collect, report, or save system activity information.
# -A            所有报告的总和
# -u            输出CPU使用情况的统计信息
# -v            输出inode、文件和其他内核表的统计信息
# -d            输出每一个块设备的活动信息
# -r            输出内存和交换空间的统计信息
# -b            显示I/O和传送速率的统计信息
# -R            输出内存页面的统计信息
# -w            输出系统交换活动信息

sar -u 10 3                                         # 每10秒采样一次，连续采样3次，观察CPU 的使用情况
# %user         显示在用户级别(application)运行使用 CPU 总时间的百分比。
# %nice         显示在用户级别，用于nice操作，所占用 CPU 总时间的百分比。
# %system       在核心级别(kernel)运行所使用 CPU 总时间的百分比。
# %iowait       显示用于等待I/O操作占用 CPU 总时间的百分比。
# %steal        管理程序(hypervisor)为另一个虚拟进程提供服务而等待虚拟 CPU 的百分比。
# %idle         显示 CPU 空闲时间占用 CPU 总时间的百分比

sar -r 10 3                                         # 监控内存分页
# kbmemfree     这个值和free命令中的free值基本一致,所以它不包括buffer和cache的空间.
# kbmemused     这个值和free命令中的used值基本一致,所以它包括buffer和cache的空间.
# %memused      这个值是kbmemused和内存总量(不包括swap)的一个百分比.
# kbbuffers和kbcached    这两个值就是free命令中的buffer和cache.
# kbcommit      保证当前系统所需要的内存,即为了确保不溢出而需要的内存(RAM+swap).
# %commit       这个值是kbcommit与内存总量(包括swap)的一个百分比.

sar -B 10 3                                         # 监控内存分页
# pgpgin/s      表示每秒从磁盘或SWAP置换到内存的字节数(KB)
# pgpgout/s     表示每秒从内存置换到磁盘或SWAP的字节数(KB)
# fault/s       每秒钟系统产生的缺页数,即主缺页与次缺页之和(major + minor)
# majflt/s      每秒钟产生的主缺页数.
# pgfree/s      每秒被放入空闲队列中的页个数
# pgscank/s     每秒被kswapd扫描的页个数
# pgscand/s     每秒直接被扫描的页个数
# pgsteal/s     每秒钟从cache中被清除来满足内存需要的页个数
# %vmeff        每秒清除的页(pgsteal)占总扫描页(pgscank+pgscand)的百分比

sar -b 10 3                                         # 报告缓冲区的使用情况
# tps           每秒钟物理设备的 I/O 传输总量
# rtps          每秒钟从物理设备读入的数据总量
# wtps          每秒钟向物理设备写入的数据总量
# bread/s       每秒钟从物理设备读入的数据量，单位为 块/s
# bwrtn/s       每秒钟向物理设备写入的数据量，单位为 块/s

sar -W 10 3                                         # 监控系统交换活动信息
# pswpin/s      每秒系统换入的交换页面（swap page）数量
# pswpout/s     每秒系统换出的交换页面（swap page）数量

sar -d 10 3 -p                                      # 报告设备使用情况
# 参数-p可以打印出sda,hdc等磁盘设备名称,如果不用参数-p,设备节点则有可能是dev8-0,dev22-0
# tps           每秒从物理磁盘I/O的次数.多个逻辑请求会被合并为一个I/O磁盘请求,一次传输的大小是不确定的.
# rd_sec/s      每秒读扇区的次数.
# wr_sec/s      每秒写扇区的次数.
# avgrq-sz      平均每次设备I/O操作的数据大小(扇区).
# avgqu-sz      磁盘请求队列的平均长度.
# await         从请求磁盘操作到系统完成处理,每次请求的平均消耗时间,包括请求队列等待时间,单位是毫秒(1秒=1000毫秒).
# svctm         系统处理每次请求的平均时间,不包括在请求队列中消耗的时间.
# %util         I/O请求占CPU的百分比,比率越大,说明越饱和.
