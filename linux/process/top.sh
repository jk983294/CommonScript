#!/usr/bin/env bash

top                                     # monitor, use q to quit
# l                                     toggle on/off load section from uptime
# t                                     toggle on/off task section
# m                                     toggle on/off memory utilization section
# f                                     edit fields
# up / down arrow                       choose field
# s                                     sort by that field, default is %CPU
# ESC                                   go to monitor screen
# r                                     renice
# k                                     kill
# q                                     quit

top -n 3                                # maximum number of iterations
top -n 2 -d 3                           # 3 seconds delay one iteration, so totally 6 seconds


# 进程查看器
# \ - 增量进程过滤器
# / - 搜索进程
# , - 选择排序标准
# k - 终止进程
# u - 筛选某一特定用户进程
# t - 显示/隐藏树形结构
# - 和 + - 展开/折叠选定的进程树
# H - 显示/隐藏用户线程
htop
