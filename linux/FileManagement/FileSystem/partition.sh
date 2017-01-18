#!/usr/bin/env bash

# info in /proc/partitions

# fdisk
fdisk -l                                                # print the partition tables for the specified devices
fdisk /dev/sdb                                          # prompt for fdisk
p                                                       # print partition tables
n                                                       # new partition
p                                                       # primary partition
1                                                       # partition number
2048                                                    # first sector
+200M                                                   # last sector
# so (sdb1  8:17  0  200M  0  part) partition created
quit

# parted
parted /dev/sda print                                   # print partition tables
parted /dev/sdb                                         # prompt for parted
mklabel msdos                                           # make label of that partition
mklabel gpt                                             # make label of that partition
print                                                   # print partition tables
quit


# gdisk
gdisk /dev/sdb                                          # prompt for gdisk
?                                                       # help
p                                                       # print partition tables
n                                                       # new partition
p                                                       # primary partition
2                                                       # partition number
2048                                                    # first sector
+200M                                                   # last sector
w                                                       # write to disk
# so (sdb2  8:18  0  200M  0  part) partition created
quit

# lsblk
lsblk                                                   # show block
blkid /dev/sdb1                                         # show UUID of this device
#NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
#sda      8:0    0   10G  0 disk                        # SCSI device A
#©À©¤sda1   8:1    0  9.3G  0 part /                      # root
#©À©¤sda2   8:2    0    1K  0 part                        # extended partition
#©¸©¤sda5   8:5    0  765M  0 part [SWAP]                 # sd5 is the first logical partition
#sdb      8:16   0    1G  0 disk
#sr0     11:0    1 1024M  0 rom
lsblk /dev/sda
ls -l /dev/sda                                          # b, block device