#!/usr/bin/awk

# count and print matched pattern
awk '/a/{++cnt} END {print "Count = ", cnt}' score.txt
