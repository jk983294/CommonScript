#!/usr/bin/env bash

# x                             delete current character
# 3x                            delete next 3 character
# X                             delete previous character
# 3X                            delete previous 3 character
# dw                            delete current word until next word's first character
# de                            delete current word until current word's last character
# 3dw                           delete next 3 words
# d3w                           delete next 3 words
# d^                            delete current to the start
# d$                            delete current to the end
# D                             delete current to the end
# dd                            delete line
# 2dd                           delete 2 lines
# dh                            delete previous character
# dl                            delete next character
# dj                            delete current line and cursor go to next line
# dk                            delete current line and cursor go to previous line

# paste(put) previously deleted text after the cursor
# p                             paste(put) data next line when dd, next cursor when d3w

# change command, Esc to get out of change mode
# ce                            change until the end of a word
# cc                            change whole line, remove contents of the line, leaving you in insert mode.
# cw                            change the word the cursor is on from the cursor to the end of the word.
# c$                            change until the end of line
# c3w                           change 3 words
# s                             delete one character and leave you in insert mode
# S                             delete the line and leave you in insert mode

# replace command
# rx                            replace only one character with  x
# R                             replace multiple characters until ESC
