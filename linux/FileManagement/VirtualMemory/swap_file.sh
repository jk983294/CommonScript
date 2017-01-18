#!/usr/bin/env bash


dd if=/dev/zero of=/root/swapfile count=1000 bs=1024        # copy 1000 blocks from /dev/zero to /root/swapfile, block size is 1024 bytes

# for temp swap space, use swap file for short time
mkswap /root/swapfile
swapon -p 10 /root/swpfile
swapon -s                                                   # should see /root/swapfile file 996 0 10

