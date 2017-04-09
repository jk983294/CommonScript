#!/bin/bash

# it only delete lines, if want to delete some words, consider substitute function with empty string

sed 'd' afile                                   # delete all content
sed '4d' afile                                  # delete line 4
sed '2,4d' afile                                # delete line 2 to line 4
sed '3,$d' afile                                # delete line 3 to end
sed '/start/,/end/d' afile                      # delete from start line to end line, if second pattern doesn't found, then it will delete from start line to the end
sed '/^Kun/d' afile                             # delete lines start with Kun
sed '/^#/d;/^$/d' ntp.conf                      # don't show commented line and empty line

sed '/next line to delete/{n; d}' afile         # delete next line of /next line to delete/
sed '/./,/^$/!d' afile                          # delete consective empty line
sed '/./,$!d' afile                             # delete leading empty lines

sed 's/<[^>]*>//g; /^$/d' a.html                # delete html tags
