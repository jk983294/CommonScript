#!/usr/bin/env bash

yy                          Copies the current line.
yw                          Copies the current word from the character the cursor is on until the end of the word.
p                           Puts the copied text after the cursor.
P                           Puts the yanked text before the cursor.
shift + insert              in edit mode, copy

# Before you paste, type this in normal mode:
:set paste
# Then enter insert mode. You will see the status bar say insert (paste). Paste your code. Hit ESC to return to normal mode, and:
:set nopaste