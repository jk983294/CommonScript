#!/bin/bash

grep ERROR data.txt                                                             # show ERROR lines
grep -n ERROR data.txt                                                          # show ERROR lines with original row number
grep -c ERROR data.txt                                                          # get how many error lines

sort -k6 -n -t"|" data.txt                                                      # sort by column 6 numerically
sort -k5 -t"|" data.txt                                                         # sort by column 5
sort -k6 -nr -t"|" data.txt | head -5                                           # show top 5 max of column 6

cut -f2 -d"|" data.txt | uniq                                                   # get distinct of column 2
cut -f2 -d"|" data.txt | uniq | wc -l                                           # get how many distinct of column 2
