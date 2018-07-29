#!/bin/bash

# How to remove a column or multiple columns from file using shell command?
# will print all but very first column
awk '{$1=""; print $0}' somefile

# will print all but two first columns
awk '{$1=$2=""; print $0}' somefile
