#!/usr/bin/awk

which awk
awk --help
awk -f calculate.awk score.txt
awk -f lib.awk -f calculate.awk score.txt               # load lib first, then run script

# -v option assigns a value to variable
awk -v name=Jerry 'BEGIN{printf "Name = %s\n", name}'
