#!/usr/bin/env bash

cat file1 file2                                     # concatenate several files' content
cat file3                                           # display from  top to bottom
tac file3                                           # display from bottom to top
cat -vet file3                                      # show invisible character, $ for new line character, ^M$ for new line of windows file
cat -n file1                                        # add line number
cat -b file1                                        # only not empty line has line number
cat -T file1                                        # show tab as ^I
