#!/usr/bin/awk

# count and print matched pattern
awk '/a/{++cnt} END {print "Count = ", cnt}' score.txt

# sum integers, one per line
grep -i symbol file | awk '{s+=$NF} END {print s}'
