#!/bin/bash

a='data'
no_interpret='no interpret for single quote $a'
interpret="need interpret for double quote $a"

echo $no_interpret
echo $interpret

your_name="kun"
greeting="hello, ${your_name} !"                                                # string concatnate
len=${#greeting}                                                                # string length
sub_str=${greeting:0:5}                                                         # sub string
sub_str_index=`expr index "$greeting" kun`                                      # sub string index

echo $greeting
echo $len
echo $sub_str
echo $sub_str_index

echo $(expr "accounts.doc" : "acc")                                             # 3
echo $(expr match "accounts.doc" "acc")                                         # 3
echo $(expr "accounts.doc" : '\(.*\).doc')                                      # accounts
echo $(expr substr "accounts.doc" 1 3)                                          # acc
echo $(expr index "accounts.doc" "d")                                           # 10
echo $(expr length "accounts.doc")                                              # 12
