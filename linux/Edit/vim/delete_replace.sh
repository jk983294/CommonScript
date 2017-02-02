#!/usr/bin/env bash

# x                             delete current character
# 3x                            delete next 3 character
# X                             delete previous character
# 3X                            delete previous 3 character
# dw                            delete current word.
# 3dw                           delete next 3 words
# d^                            delete current to the start
# d$                            delete current to the end
# D                             delete current to the end
# dd                            delete line

# cc                            remove contents of the line, leaving you in insert mode.
# cw                            change the word the cursor is on from the cursor to the end of the word.
# r                             replace the character under the cursor. vi returns to command mode after the replacement is entered.
# R                             overwrite multiple characters beginning with the character currently under the cursor. You must use Esc to stop the overwriting.
# s                             replace the current character with the character you type. Afterward, you are left in insert mode.
# S                             delete the line the cursor is on and replaces with new text. After the new text is entered, vi remains in insert mode.
