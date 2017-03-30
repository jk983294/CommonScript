#!/usr/bin/awk

which awk
awk --help
awk -f calculate.awk score.txt

# -v option assigns a value to variable
awk -v name=Jerry 'BEGIN{printf "Name = %s\n", name}'
