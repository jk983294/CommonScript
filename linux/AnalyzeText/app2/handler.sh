#!/bin/bash

# merge two files, using FNR will be set per file
# read b.csv first, record all data in a[book id] = 'book description,price'
# then read a.csv, using book id key to do merge
awk -F, 'FNR==NR{a[$1]=$2 FS $3;next} { print $0 FS a[$2]}' b.csv a.csv
