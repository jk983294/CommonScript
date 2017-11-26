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

# substring
string="home/testUser/testfolder"
# # 删除从左往右第一个匹配的字符以及它左边的字符
newString1=${string#*/}                                                         # "testUser/testfolder"
# ## 删除从左往右最后一个匹配字符以及它左边的字符
newString2=${string##*/}                                                        # "testfolder"
# % 删除从右往左第一个匹配的字符以及它右边的字符
newString3=${string%/*}                                                         # "home/testUser"
# %% 删除从右往左最后一个匹配的字符以及它右边的字符
newString4=${string%%/*}                                                        # "home"

# ${var:index:count}  index > 0 from left, index < 0 from right, count is how many characters
newString5=${string:0-6:4}                                                      # "fold"
newString6=${string:0-6}                                                        # "folder"
newString7=${string:6}                                                          # "/testUser/testfolder"

# string concatenation
newString8=${newString5}${newString6}                                           # "foldfolder"
