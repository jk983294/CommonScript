#!/usr/bin/env bash

swapon -s                           # show summary of swap
free -m                             # swap info

# create swap partition
gdisk /dev/sdb
n
+300M
L                                   # show types
8200                                # choose linux swap type
w                                   # write to disk

partprobe /dev/sdb                  # sync partition table
ls /dev/sdb*                        # should see new swap partition
cat /proc/partitions                # should see new swap partition

# create swap file system to swap partition
mkswap /dev/sdb3


swapon /dev/sdb3
swapoff /dev/sdb3
swapon -p 10 /dev/sdb3              # set /dev/sdb3 priority to 10

# config /etc/fstab to make sure swap partition mounted by booting
# /dev/sdb3 none swap sw,pri=10 0 0
swapon -a                           # mount all swap partition in /etc/fstab

