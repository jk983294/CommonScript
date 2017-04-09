#!/bin/bash

# write selected content to specific file
sed -n '1,3w tmp.txt' afile                     # write first three lines to tmp.txt
sed -n '3,$w tmp.txt' afile                     # write from line 3 to last line to tmp.txt
sed -n '/line match/w tmp.txt' afile            # write matched lines to tmp.txt

# insert specific file's content to selected area
sed '3r tmp.txt' afile                          # insert tmp.txt content after line 3
sed '$r tmp.txt' afile                          # insert tmp.txt content to the end of afile
sed '/dpm/r tmp.txt' afile                      # insert tmp.txt content after dpm matched line

# replace with another file's content
sed '/PlaceHolder/{r tmp.txt; d}' afile         # delete PlaceHolder line and replace with tmp.txt data
