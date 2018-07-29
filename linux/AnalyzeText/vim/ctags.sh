#!/bin/bash

# 跳转到变量或函数的定义处
Ctrl + ]
:ta func_name

# 返回到跳转前的位
Ctrl + o
Ctrl + t

# 局部变量的索引
g + d

# 打开定义该函数的文件并定位到定义首行
vim -t my_func

sudo apt-get install ctags

# 递归的为当前目录及子目录下的所有代码文件生成tags文件
ctags -R
#为某些源码生成tags文件，使用如下命令
ctags filename.c filename1.c file.h
# or
ctags *.c *.h

# fileds 用于指定每条标记的扩展字段域
# extra 选项用于增加额外的条目: f表示为每个文件增加一个条目,q为每个类增加一个条目
ctags -R --c++-kinds=+px --fields=+iaS --extra=+q

# 加入系统函数或全局变量的tag标签
ctags -I __THROW --file-scope=yes --langmap=c:+.h --languages=c,c++ --links=yes --c-kinds=+p --fields=+S -R -f ~/.vim/systags /usr/include /usr/local/include
# add tags file at ~/.vimrc
set tags+=~/.vim/systags

# how to use tags file generated by ctags, input below in vim command mode
:set tags=./tags
