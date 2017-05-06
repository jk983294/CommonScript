#!/bin/bash

diff file1 file2                        # compare two files
# <         file1 content
# >         file2 content
# a         add
# c         change
# d         delete

diff -e file1 file2                     # print an ed script

diff -arq folder1/ folder2/             # compare two dirs, treat all file as test file, recursively, briefly
