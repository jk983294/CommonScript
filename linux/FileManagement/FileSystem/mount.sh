#!/usr/bin/env bash

mount                                                       # list all file system including pesudo file system
mount | grep mnt                                            # list all file system mounted under folder /mnt

mount -t ext4 /dev/sdb1 /mnt                                # mount /dev/sdb1 to /mnt folder, the type of /dev/sdb1 is ext4
mount -t ext4 -o acl,noexec /dev/sdb1 /mnt                  # add option, no execute permission
mount -a                                                    # mount all files in /etc/fstab

umount /mnt                                                 # un-mount all file system under /mnt
umount /dev/sdb1                                            # un-mount device

# boot time device mount
vim /etc/fstab
blkid /dev/sdb1                                             # show UUID of this device
mount -a                                                    # mount all files in /etc/fstab
# /dev/sdb1 /mnt ext4 noexec,defaults 0 2
# UUID=4283a7ee-4ef0-4a42-9d00-15c535b24627 /mnt ext4 noexec,defaults 0 2