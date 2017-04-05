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

# an other approach
outfile='output.sql'
input='data.csv'
IFS=','
while read field1 field2
do
    cat >> $outfile << EOF
INSERT INTO my_table (field1, field2) VALUES ("$field1", "$field2");
EOF
done < "$input"
