#!/usr/bin/env bash

cp file* ..                                 # * match zero or any characters
cp file? ..                                 # ? match one character
mkdir -p /a/b/{c,d}                         # make two directories

# *             any number of characters
# ?             any single character
# [az]          a or z
# [a-z]         specified range
# [!a]          not a

ls f*
ls *.c
ls f?le
ls f??e
ls f[az]le
ls f[a-z]le
ls f[!a]le
