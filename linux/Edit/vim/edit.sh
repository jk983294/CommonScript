#!/usr/bin/env bash

# J                             Join the current line with the next one. A count joins that many lines.
# <<                            tab, Shifts the current line to the left by one shift width.
# >>                            shift + tab, Shifts the current line to the right by one shift width.
# ~                             switch the case of the character under the cursor.

# U                             undo all the changes on a line
# u                             undo the last change
# Ctrl + r                      redo

# :r file                       read file and inserts it after current line
# :nr file                      read file and inserts it after line n.
# :r! id                        run command id, then insert the content to current cursor
# :r! hostname                  run command hostname, then insert the content to current cursor

# :w filename                   write to file filename.
# :23,27w /tmp/file             Write 23-27 lines to /tmp/file
