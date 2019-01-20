#!/bin/bash

# command                         操作的行
:d                              # 当前行
:.d                             # 当前行
:1d                             # 第一行
:$d                             # 最后一行
:1,$d                           # 所有行
:%d                             # 所有行（这是 1,$ 的语法糖）
:.,5d                           # 当前行至第5行
:,5d                            # 同样是当前行至第5行
:,+3d                           # 当前行及接下来的5行
:1,+3d                          # 第一行至当前行再加5行
:,-3d                           # 当前行及向上的5行（Vim 会弹出提示信息，因为这是一个保留的范围）
:3,'xdelete                     # 第三行至标注为x的那一行
:/^foo/,$delete                 # 当前行以下，以字符 "foo" 开头的那一行至结尾
:/^foo/+1,$delete               # 当前行以下，以字符 "foo" 开头的那一行的下一行至结尾


# 对象标识符操作
# i表示在对象内（英文inner）操作，a 表示对整个对象（英文around）操作，这时开头和结尾的空格都会被考虑进来。
diw                             # 可以删除当前单词
ci(                             # 可以改变括号中的内容
d2a(                            # 将会删除从最内层开始的两对括号，以及他们之间的所有内容
di{                             # 删除当前{}中内容

# Mark
mark        user                usage
a-z         user                仅对当前的一个文件生效，也就意味着只可以在当前文件中跳转
A-Z         user                全局标注，可以作用于不同文件。大写标注也称为「文件标注」。跳转时有可能会切换到另一个缓冲区
0-9         viminfo             0 代表 viminfo 最后一次被写入的位置。实际使用中，就代表 Vim 进程最后一次结束的位置。1 代表 Vim 进程倒数第二次结束的位置，以此类推
# command mode
mm                              # mark loaclly current line to m
mM                              # mark globally current line to M
# last line mode
:'m                             # go to mark m
:'M                             # go to mark M
:marks                          # show all marks
