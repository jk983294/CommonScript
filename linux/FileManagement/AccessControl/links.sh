#!/usr/bin/env bash

# File Name / Inode(metadata) / Data
# hard link, one file have more than 1 file name
# soft link (symbolic link / symlink), complete different files, they have different inode, but the data the inode pointed to is the same


ls -ld /usr/share/doc
find /usr/share/doc -maxdepth 1 -type d | wc -l
# drwxr-xr-x 1868 root root 69632  Jan 13 22:55 /usr/share/doc, it contains 1866 sub-directories (1868 - 2)
# because every sub-directory has a .. link back to parent directory
# the directory itself have two link count (/usr/share/doc and .)


# hard link
ln file2 file4
ls -li                                                      # show inode, then file2 and file4's inode should be the same
stat file2
stat file4                                                  # stat of file2 and file4's content should be the same except the file name

# symlink
ln -s file3 file5
ls -li                                                      # show inode, then file3 and file5's inode should be different
readlink file5                                              # should display file5 -> file3