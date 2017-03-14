#!/usr/bin/env bash

vim newfile
vim +127 a.cpp                                      # open a.cpp, jump to 127th line
vim +/pattern a.cpp                                 # open a.cpp, search text pattern, locate to that line
vim +?/dev/sda1 /etc/fstab                          # open /etc/fstab, search the occurrence of /dev/sda1, locate the cursor to that line
vim -On file1 file2 ...                             # 垂直分屏打开多个文件
vim -on file1 file2 ...                             # 水平分屏打开多个文件


# q                             quit without save
# :q!                           quit without save
# :x                            quit with save
# :wq                           quit with save
# ZZ                            quit with save
# :w filename2                  save to another file filename2

# CRTL + G                      show the current filename and the status.
# :f                            Displays current position in the file in % and file name, total number of file.
# :f filename                   Renames current file to filename.
# :e filename                   Opens another file with filename.
# :cd dirname                   Changes current working directory to dirname.
# :r file                       read file and inserts it after current line
# :nr file                      read file and inserts it after line n.
# :r! id                        run command id, then insert the content to current cursor
# :r! hostname                  run command hostname, then insert the content to current cursor
# :w filename                   write to file filename.
# :23,27w /tmp/file             Write 23-27 lines to /tmp/file

# multiple files
# :e #                          toggle between two opened files.
# :n                            go to next file in the series.
# :p                            go to previous file in the series.
# :N                            go to previous file in the series.
# ctrl+w s                      上下分割当前文件
# ctrl+w v                      水平分割当前文件
# :sp filename                  上下分割打开新文件
# :vsp filename                 水平分割打开新文件
# ctrl+w h/j/k/l/w              切换工作屏幕, h/j/k/l是按照方向移动，w是移动到下一个屏幕
# ctrl+w =                      所有屏幕都一样的高度
# ctrl+w -                      降低高度
# ctrl+w +                      增加高度
