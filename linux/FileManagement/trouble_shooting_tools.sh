#!/usr/bin/env bash

# estimate file space usage, h human readable, s summary
du -hs /etc                                             # (file size, directory)
du -h --max-depth=1 /etc                                # one depth <size, dir>

# report file system disk space usage, h human readable, T type, l local
df -hlT

# adjust tunable filesystem parameters on ext2/ext3/ext4 filesystems
# L label
tune2fs -L "DATA" /dev/sda1                             # change filesystem volume name in dumpe2fs cmd

# ext2/ext3/ext4 file system debugger
debugfs /dev/sda1
ls
stat <14>                                               # show deleted info
quit

# dump ext2/ext3/ext4 filesystem information
dumpe2fs /dev/sda1 | less

# find back deleted files
apt-get install extundelete
mkdir dir1
cp /etc/init/* .
ls -li shutdown.conf                                            # 189860 -rw-r--r-- 1 root root 277  1月 13 22:59 shutdown.conf
cat shutdown.conf
rm shutdown.conf
extundelete --inode 189860 /dev/sda1
extundelete --restore-file dir1/shutdown.conf /dev/sda1         # recover deleted file
cd RECOVERED_FILES/dir1/
