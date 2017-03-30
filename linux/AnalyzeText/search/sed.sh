#!/usr/bin/env bash

# sed

# 1,$p                                      print from first line to last line
# 1,$s/G/Greg                               substitute G for Greg globally
# g/Greg/p                                  print all lines match Greg

# display
sed -n '1,2p' afile                             # surpress output with -n, only print first two lines
sed -n '1,$p' afile                             # print from first line to last line
sed -n '/Greg/p' afile                          # print all lines match Greg
sed -n '/^g/,/^d/s/p[0-9]//p' afile             # substitute p[0-9] with empty for lines start with g or d, then print

# substitute
sed 's/RE/RS/' afile                            # substitute RE for RS once
sed 's/RE/RS/g' afile                           # substitute RE for RS globally
sed -n '4s/RE/RS/p' afile                       # substitute RE for RS only line 4, and print
sed -n '1,$s/G/Greg/p' afile                    # substitute G for Greg globally, and print

# delete
sed '/^#/d;/^$/d' ntp.conf                      # don't show commented line and empty line
sed 4d afile                                    # delete line 4
sed '/^Kun/d' afile                             # delete lines start with Kun

# write & read
sed -n '3,$w tmp.txt' afile                     # write from line 3 to last line to tmp.txt
sed '/dpm/r tmp.txt' afile                      # read tmp.txt content under dpm line

# in place edit
sed -i '/^#/d;/^$/d' ntp.conf                   # delete commented line and empty line
