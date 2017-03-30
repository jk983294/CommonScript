#!/bin/bash

uniq file1                                          # get unique lines
uniq -c file1                                       # add count of duplicate line
uniq -d file1                                       # only print duplicate line
uniq -u file1                                       # only print non-duplicate line

uniq file1 | wc -l                                  # count how many unique lines
