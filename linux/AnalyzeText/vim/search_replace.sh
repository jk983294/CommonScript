#!/usr/bin/env bash

# %                             specify the whole document
# 103,199                       range of document

# n                             go to next occurrence
# N                             go to previous occurrence
# CTRL + O                      go back to where you came, repeat to go back further.
# CTRL + I                      opposite of CTRL + O

# Search
# /str                          find str, press n for next occurrence, N for previous occurrence
# ?str                          searches backwards (upwards), press n for previous occurrence, N for next occurrence

# special character
# ^                             Search at the beginning of the line. (Use at the beginning of a search expression.)
# $                             End of the line (Use at the end of the search expression.)
# .                             Matches a single character.
# *                             Matches zero or more of the previous character.
# [                             Starts a set of matching, or non-matching expressions.
# <                             Put in an expression escaped with the backslash to find the ending or beginning of a word.
# >                             See the '<' character description above.

# matching parentheses search () [] {}
# %                             go to matching parentheses



# Replacing Text, substitute
# :s/s1/s2                      substitute s1 with s2, only once
# :s/search/replace/g           substitute search with replace
# :%s/s1/s2/gc                  substitute s1 with s2 globally with a prompt whether to substitute or not.
# :%s/s1/s2                     substitute search with replace globally
# :5,20s/s1/s2/g                substitute s1 with s2 from line 5 to line 20
# :5,20s/^/    /                indent 5-20 lines
