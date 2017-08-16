#!/bin/bash

iostat -d -k 1 10           # 查看TPS和吞吐量信息(磁盘读写速度单位为KB)
iostat -d -m 2              # 查看TPS和吞吐量信息(磁盘读写速度单位为MB)
iostat -d -x -k 1 10        # 查看设备使用率（%util）、响应时间（await）
iostat -c 1 10              # 查看cpu状态

iostat -d -k 1 2                        # device info, print KB, 采样间隔1s, 采样次数2次
# tps           该设备每秒的传输次数,一次传输是一次I/O请求。多个逻辑请求可能会被合并为一次I/O请求。一次传输请求的大小是未知的
# kB_read/s     每秒从设备（drive expressed）读取的数据量
# kB_wrtn/s     每秒向设备（drive expressed）写入的数据量
# kB_read       读取的总数据量
# kB_wrtn       写入的总数量数据量

iostat -d -x -k 1 3                     # -x 显示和io相关的扩展数据
# rrqm/s        每秒这个设备相关的读取请求有多少被Merge了（读取请求读取的是相同Block的数据，这个请求合并Merge）
# wrqm/s        每秒这个设备相关的写入请求有多少被Merge了
# rsec/s        每秒读取的扇区数
# wsec/         每秒写入的扇区数
# rKB/s         The number of read requests that were issued to the device per second
# wKB/s         The number of write requests that were issued to the device per second
# avgrq-sz      平均请求扇区的大小
# avgqu-sz      是平均请求队列的长度。毫无疑问，队列长度越短越好
# await         每一个IO请求的处理的平均时间。这里可以理解为IO的响应时间，一般地系统IO响应时间应该低于5ms，如果大于10ms就比较大了
# svctm         表示平均每次设备I/O操作的服务时间（以毫秒为单位）。如果svctm的值与await很接近，表示几乎没有I/O等待，磁盘性能很好，如果await的值远高于svctm的值，则表示I/O队列等待太长，系统上运行的应用程序将变慢
# %util         在统计时间内所有处理IO时间，除以总共统计时间。如果统计间隔1秒，该设备有0.8秒在处理IO，而0.2秒闲置，那么该设备的%util = 0.8/1 = 80%，所以该参数暗示了设备的繁忙程度
