#!/bin/bash

# N         copy next line content into workspace
# D         only delete the first line of multi-line
# P         only print the first line of multi-line

sed '/to merge/{N; s/\n/ /}' afile                          # merge next line, replace '\n' with ' '
sed 'N; s/a.b/ab/' afile                                    # find 'a\nb' multi-line pattern

sed 'N; /a.b/d' afile                                       # delete two lines when found 'a\nb'
sed 'N; /a.b/D' afile                                       # delete first line when found 'a\nb'

sed -n 'N; /a.b/p' afile                                    # print two lines when found 'a\nb'
sed -n 'N; /a.b/P' afile                                    # print first line when found 'a\nb'
