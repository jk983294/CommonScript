#!/usr/bin/env bash

# %                             specify the whole document
# 103,199                       range of document

# CTRL + O                      go back to where you came, repeat to go back further.
# CTRL + I                      opposite of CTRL + O

# Search
# /str                          find str, press n for next occurrence, N for previous occurrence
# ?str                          searches backwards (upwards), press n for previous occurrence, N for next occurrence
# f                             search forwards for a character on the current line only
# F                             search backwards for a character on the current line only
# t                             search for a character on the current line only, for t, the cursor moves to the position before the character
# T                             search for a character on the current line only, for t, the cursor moves to the position after the character
# mx                            插入书签（x为小写字母），以后可以用`x跳转到该书签处
# `.                            上次编辑的位置
# special character
# ^                             Search at the beginning of the line. (Use at the beginning of a search expression.)
# $                             End of the line (Use at the end of the search expression.)
# .                             Matches a single character.
# *                             Matches zero or more of the previous character.
# [                             Starts a set of matching, or non-matching expressions.
# <                             Put in an expression escaped with the backslash to find the ending or beginning of a word.
# >                             See the '<' character description above.

# Replacing Text
# :s/search/replace/g           substitute search with replace
# :s/s1/s2                      下一个s1替换为s2
# :%s/s1/s2                     s1全部替换为s2
# :s/s1/s2/g                    当前行的s1替换为s2
# :5,20s/s1/s2/g                从5到20行的s1替换为s2
# :5,20s/^/    /                indent 5-20 lines
