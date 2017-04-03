#!/bin/bash

for (( i = 0; i < 3; i++ )); do
    echo "out loop number is $i"
    for (( j = 0; j < 3; j++ )); do
        echo "    inner loop number is $j"
    done
done > output.txt

for word in z x v c; do
    echo $word
done | sort > data.txt
