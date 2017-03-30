#!/usr/bin/env bash

sort file4.csv
sort -r file4.csv                           # show in reverse order
sort -k4 -t"," file4.csv                    # sort by column 4, delimiter is ,
sort -k4 -r -t"," file4.csv                 # sort by column 4 reverse order, delimiter is ,
sort -k5 -n -t"," file4.csv                 # sort by column 5 numerically
sort -M file4.csv                           # sort by month, three character (Jan, Feb ...)
sort -b file4                               # ignore leading blank
sort -f file4                               # ignore case
sort -g file4                               # treat number as float, -n is integer
sort -m file1 file2                         # merge two sorted files

cut -f4 -d"," file4.csv | sort -u           # get column 4, sort uniquely (remove duplicates)
