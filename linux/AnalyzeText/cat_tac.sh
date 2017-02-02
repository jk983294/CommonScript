#!/usr/bin/env bash

cat file1 file2                                     # concatenate several files' content
cat file3                                           # display from  top to bottom
tac file3                                           # display from bottom to top
cat -vet file3                                      # show invisible character, $ for new line character, ^M$ for new line of windows file