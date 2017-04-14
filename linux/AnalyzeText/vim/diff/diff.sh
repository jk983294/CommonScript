#!/bin/bash

# open
vim -d file1.txt file2.txt

vim file1.txt
# :vertical diffsplit file2.txt


# merge file
# dp                                                    diff put, put current change to another file
# do                                                    diff get, get change from another file

# operate both files
# :qa                                                   quit all
# :wa                                                   write all
# :wqa                                                  write then quit all
# :qa!                                                  force to quit all

# command
# ]c                                                    jump to next change
# [c                                                    jump to previous change

# zo                                                    open fold (zip open)
# zc                                                    close fold (zip close)

# :diffu
# :diffupdate                                           recalculate the diff, useful when after making several changes

# :set noscrollbind
# :set scrollbind
