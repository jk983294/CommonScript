#!/usr/bin/env bash
# TO-DELETE
# dd        duplicate disk, image, create file with certain bytes, backup file, complete disks

# backup /dev/sda MBR 512 byte in case partition table etc. data lost
dd if=/dev/sda of=/data/file count=1 bs=512
# clear MBR
dd if=/dev/zero of=/dev/sda count=1 bs=512
# recover MBR from backup
dd if=/data/file of=/dev/sda count=1 bs=512


# back /etc
tar -cvf /data/sales/etc.tar /etc