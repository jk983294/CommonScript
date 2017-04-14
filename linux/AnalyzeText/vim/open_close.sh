#!/bin/bash

vim newfile
vim -R read_only_file                               # open with read only perm
vim +127 a.cpp                                      # open a.cpp, jump to 127th line
vim +/pattern a.cpp                                 # open a.cpp, search text pattern, locate to that line
vim +?/dev/sda1 /etc/fstab                          # open /etc/fstab, search the occurrence of /dev/sda1, locate the cursor to that line
vim -On file1 file2 ...                             # open multiple files with vertical mode
vim -on file1 file2 ...                             # open multiple files with horizontal mode


# :e!                                               return to last saved state, basicly give up current edit
# :q                                                quit without save
# :q!                                               quit without save
# :x                                                quit with save
# :wq                                               quit with save
# :w filename2                                      save to another file filename2
# :23,27w /tmp/file                                 Write 23-27 lines to /tmp/file

# CRTL + G                                          show the current filename and the status.
# :f                                                Displays current position in the file in % and file name, total number of file.
# :cd dirname                                       Changes current working directory to dirname.

# :f filename                                       Renames current file to filename.
# :e filename                                       Opens another file with filename.

# multiple files
# :e #                                              toggle between two opened files.
# :n                                                go to next file in the series.
# :N                                                go to previous file in the series.
# :p                                                go to previous file in the series.

# ctrl+w s                                          vertical split current file
# ctrl+w v                                          horizontal split current file
# :sp filename                                      vertical split new file
# :vsp filename                                     horizontal split new file
# ctrl+w h/j/k/l/w                                  cut to next screen, with direction h/j/k/l
# ctrl+w =                                          every screen has the same height
# ctrl+w -                                          decrease height
# ctrl+w +                                          increase height
