#!/bin/bash

for (( i = 0; i < 3; i++ )); do
    echo "number is $i"
done

for (( a = 0, b = 10; a < 3; a++, b-- )); do
    echo "number is $a <==> $b"
done

for (( i = 0; i < 3; i++ )); do
    echo "out loop number is $i"
    for (( j = 0; j < 3; j++ )); do
        echo "    inner loop number is $j"
    done
done

echo "finished"
