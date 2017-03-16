#!/usr/bin/env bash

yy                          yank the current line
yw                          yank the current word
y$                          yank to the end of line
p                           paste(put) the yanked text after the cursor.
P                           paste(put) the yanked text before the cursor.
shift + insert              in edit mode, copy

# Before you paste, to disable auto indent temporarily, type this in normal mode:
:set paste
# Then enter insert mode. You will see the status bar say insert (paste). Paste your code. Hit ESC to return to normal mode, and:
:set nopaste
