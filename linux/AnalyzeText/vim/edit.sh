#!/usr/bin/env bash

# i                               inserts text before current cursor location.
# I                               inserts at start of current line.
# a                               append after current cursor location.
# A                               append at end of current line.
# o                               open a new line for text entry below cursor location.
# O                               open a new line for text entry above cursor location.

# J                             Join the current line with the next one. A count joins that many lines.
# <<                            tab, Shifts the current line to the left by one shift width.
# >>                            shift + tab, Shifts the current line to the right by one shift width.
# ~                             switch the case of the character under the cursor.

# U                             undo all the changes on a line
# u                             undo the last change
# Ctrl + r                      redo

# insert content into current file
# :r file                       read file and inserts it after current line
# :nr file                      read file and inserts it after line n.
# :r !id                        run command id, then insert the content to current cursor
# :r !hostname                  run command hostname, then insert the content to current cursor
# :r !ls

# write content to another file
# :w filename                   write to file filename.
# :23,27w /tmp/file             Write 23-27 lines to /tmp/file
