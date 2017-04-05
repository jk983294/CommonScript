#!/bin/bash

# 0 standard input      STDIN
# 1 standard output     STDOUT
# 2 standard error      STDERR

# standard output, it is default output
echo "hello world" 1> a.txt
echo "aha" 1>> a.txt

# standard error output, it is default output
ls /notexist 2> a.txt
ls /notexist 2>> a.txt

echo "hello world" > a.txt                              # write to file
echo "aha" >> a.txt                                     # append to file

ls /home /notexist > out.txt 2>&1                       # redirect both standard error and output to the same file
ls /home /notexist &> out.txt                           # redirect both standard error and output to the same file
ls /home /notexist 2>>error.log                         # show only standard output, log the error
ls /home /notexist > /dev/null 2>&1                     # not interested in both standard error and output

ls /home /notexist 2>&1 | tee out.txt                   # send msg to both screen and file
ls /home /notexist 2>&1 | tee -a out.txt                # append data in out.txt
