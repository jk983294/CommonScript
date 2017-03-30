#!/usr/bin/env bash

# field list index from 1 to n
cut -f1,3 -d":" /etc/passwd                         # column delimiter is :, only show column 1 and 3
cut -f2,3,4 -d"," file4.csv                         # column delimiter is , only show column 2, 3 and 4
cut -c17-23 file.csv                                # character offsets for cut region
