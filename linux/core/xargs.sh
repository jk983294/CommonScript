#!/bin/bash

echo "--help" | cat                                 # cat, content is --help
echo "--help" | xargs cat                           # cat --help, cmd parameters


find /sbin -perm 700 | xargs ls -l
find /sbin -name "mkf*" | xargs ls -l
find. -name *.png -type f -print | xargs tar -cvzf images.tar.gz

cat urls.txt | xargs wget

# 第一个命令的输出会在 xargs命令结尾处传递
# 如果命令需要中间过程的输出, 只需要使用 {} 并结合 -i 参数就行了
ls /etc/*.conf | xargs -i cp {} /home/likegeeks/Desktop/out
