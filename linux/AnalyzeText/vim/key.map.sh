#!/bin/bash

# key map
# 递归        非递归             模式
:map        :noremap        normal, visual, operator-pending
:nmap       :nnoremap       normal
:xmap       :xnoremap       visual
:cmap       :cnoremap       command-line
:omap       :onoremap       operator-pending
:imap       :inoremap       insert
:nnoremap a b   # press a as if you press b
