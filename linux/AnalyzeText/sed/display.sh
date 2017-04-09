#!/bin/bash

sed -n '1,2p' afile                             # surpress output with -n, only print first two lines
sed -n '1,$p' afile                             # print from first line to last line
sed -n '/Greg/p' afile                          # print all lines match Greg
sed -n '/^g/,/^d/s/p[0-9]//p' afile             # substitute p[0-9] with empty for lines start with g or d, then print
sed -n '/Greg/{p; s/dog/cat/}' afile            # print original line, then perform substitution, then print changed line

# print line number
sed '=' afile
sed '=' afile | sed 'N;s/\n/ /'                 # line number is the same line with actual line
sed -n '/Greg/{=; p;}' afile                    # print line number with line number

# print non-printable character
sed -n 'l' afile
