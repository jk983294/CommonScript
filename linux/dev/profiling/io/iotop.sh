#!/bin/bash

# 通过磁盘写入对进程排序，并显示程序写入到磁盘的数量与频次
# need root perm
iotop
iotop --only                            # only show those has IO operations
iotop -u kun                            # show kun's stats

# <- left arrow -> right arrow          change sort column
# R                                     reverse sort order
# P                                     show thread or process level
# A                                     current or accumulated IO
# O                                     only show those has IO operations
