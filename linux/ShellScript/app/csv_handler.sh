#!/bin/bash

IFS.OLD=$IFS
IFS=$'\n'                                                                       # handle every line
for line in $(cat data.csv); do
    echo "line: $line"
    IFS=,                                                                       # handle every cloumn
    for column in $line; do
        echo "    value: $column"
    done
done
IFS=$IFS.OLD
