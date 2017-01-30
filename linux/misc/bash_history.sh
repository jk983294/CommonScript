#!/usr/bin/env bash

# history
cat .bash_history               # show history
history                         # show history

!g                              # run last command starting with g

cd /etc
cd /usr
!?etc                           # execute the last command that etc string anywhere, !cd only gives you cd /usr

!$                              # represents the last argument
mkdir dir1
cd !$                           # go to dir1

!30                             # run 30th command in command history

# Ctrl + r                      # reverse search command history for your input
# type something to search history command
# press ESC to edit the searched command
# press ENTER to run the searched command

HISTCONTROL=erasedups           # set history remove duplicates

history -c                      # clear history
history -r                      # restore history by reading history file

# clear history completely
# first clear history, then write empty content to history file, then read that file into memory history
history -c
history -w
history -r
