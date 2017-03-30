#!/usr/bin/env bash

# File Name / Inode(metadata) / Data
# hard link, one file have more than 1 file name
# hard link cannot cross file system, because root's inode start from 1
# soft link (symbolic link / symlink), complete different files, they have different inode, but the data the inode pointed to is the same
# symbolic file contains pathname of file it refers to

# danger!!! cat will read symbolic link, it could trap into infinite loop when symlink is loop

# hard link
ln file2 file4
ls -li                                                      # show inode, then file2 and file4's inode should be the same
stat file2
stat file4                                                  # stat of file2 and file4's content should be the same except the file name

# symlink
ln -s file3 file5
ls -li                                                      # show inode, then file3 and file5's inode should be different
readlink file5                                              # should display file5 -> file3
