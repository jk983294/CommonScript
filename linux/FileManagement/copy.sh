#!/usr/bin/env bash

# backup /dev/sda MBR 512 byte in case partition table etc. data lost
dd if=/dev/sda of=/data/file count=1 bs=512
# recover MBR from backup
dd if=/data/file of=/dev/sda count=1 bs=512


# back /etc
tar -cvf /data/sales/etc.tar /etc