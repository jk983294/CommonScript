#!/bin/bash

diff file1 file2                        # compare two files
# <         file1 content
# >         file2 content
# a         add
# c         change
# d         delete

diff -e file1 file2                     # print an ed script

diff /tmp/r/ /tmp/s/                    # compare two directory structure
