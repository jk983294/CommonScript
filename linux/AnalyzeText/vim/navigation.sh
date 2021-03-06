#!/bin/bash

# Cursor go
# Ctrl + g                          show your location in the file and the file status, for further nav prepare
# h/j/k/l                           left / down / up / right
# $/0/^                             line end / line start / line start
# H/M/L                             screen top(High) / middle / bottom(Low)
# */#                               current word's (next / previous) occurrence
# w/b                               start of [ next word / back(previous) ] word
# e                                 end of next word
# 5w                                next 5 words, count excluding current word
# 5e                                next 5 words, count including current word
# 2b                                previous 2 words
# 0                                 start of line.
# |                                 start of line.
# (                                 start of current sentence.
# )                                 start of next sentence.
# E                                 go to the end of Blank delimited word
# {                                 move a paragraph back
# }                                 move a paragraph forward
# [[                                move a section back
# ]]                                move a section forward
# n|                                go to column n in the current line
# gg                                move you to the start of the file
# G                                 go to last line
# nG                                go to line n
# :n                                go to line n
# nH                                go to nth line from the top of the screen
# nL                                go to nth line from the bottom of the screen

# Control Commands
# ctrl+f/b                          page up / page down
# ctrl+d/u                          half page up / half page down
# CTRL+e                            move screen up one line
# CTRL+y                            move screen down one line

# 按键                    跳转至
:'[ 与 `[                上一次修改或复制的第一行或第一个字符
:'] 与 `]                上一次修改或复制的最后一行或最后一个字符
:'< 与 `<                上一次在可视模式下选取的第一行或第一个字符
:'> 与 `>                上一次在可视模式下选取的最后一行或最后一个字符
:'' 与 `'                上一次跳转之前的光标位置
:'" 与 `"                上一次关闭当前缓冲区时的光标位置
:'^ 与 `^                上一次插入字符后的光标位置
:'. 与 `.                上一次修改文本后的光标位置
:'( 与 `(                当前句子的开头
:') 与 `)                当前句子的结尾
:'{ 与 `{                当前段落的开头
:'} 与 `}                当前段落的结尾
