#!/usr/bin/env bash

# DISK
# MBR Partition Table 2TB (Primary Max 4 / Logical Max 15)
# GPT (GUID Partition Table 8ZB) (Partition Max 128)
# File System: ext2, ext3, ext4, ReiserFS, XFS ...

# general use choose ext4
# XFS for specialized use

mkfs.ext4 -b 4096 /dev/sdb1                                 # build /dev/sdb1 to ext4 file system with block size of 4K
mkfs.xfs -b size=64k /dev/sdb2                              # build /dev/sdb2 to xfs file system with block size of 64k
mkfs.xfs -b size=64k /dev/sdb2                              # -f means force