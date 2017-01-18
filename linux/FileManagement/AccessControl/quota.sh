#!/usr/bin/env bash

# quota can be applied to space / inode, it used to limit the space usage of user / group
# user quota / group quota on top of file system

vim +?/dev/sda1 /etc/fstab                          # open /etc/fstab, search the occurrence of /dev/sda1, locate the cursor to that line
# /dev/sda1 /data ext4 defaults,usrquota,grpquota 0 2
mount
mount -o remount /data
mount


getenforce                                          # get the current mode of SELinux
quotacheck -cu /data                                # generate aquota.user under /data
repquota -auv                                       # report of quota
quotaon /dev/sda1                                   # continue monitoring the space usage
edquota -u jk                                       # edit quota for user jk
setquota -u jk 21000 26000 0 0 /dev/sda1