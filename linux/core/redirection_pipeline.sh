#!/usr/bin/env bash

# 0 standard input
# 1 standard output
# 2 standard error

# standard output, it is default output
echo "hello world" 1> a.txt
echo "aha" 1>> a.txt

# standard error output, it is default output
ls /notexist 2> a.txt
ls /notexist 2>> a.txt

echo "hello world" > a.txt                              # write to file
echo "aha" >> a.txt                                     # append to file

ls /home /notexist > out.txt 2>&1                       # redirect both standard error and output to the same file
ls /home /notexist 2>>error.log                         # show only standard output, log the error
ls /home /notexist > /dev/null 2>&1                     # not interested in both standard error and output
ls /home /notexist 2>&1 | tee out.txt                   # send msg to both screen and file

set -o noclobber                                        # prevent an existing file been overwritten
ls /home >> out.txt                                     # although noclobber is on, file could still be appended
ls /home >| out.txt                                     # override noclobber, file could be overwritten now

# unnamed pipe |
ls -l | wc -l                                           # count file

# named pipe
# it support IPC(inter-process communication), one shell redirect the output to the file, while another read from it
# better to create pipe in /tmp folder since it allows different users could communicate
mkfifo /tmp/jkpipe
ls -l > /tmp/jkpipe                                     # shell process 1
wc -l < /tmp/jkpipe                                     # shell process 2
