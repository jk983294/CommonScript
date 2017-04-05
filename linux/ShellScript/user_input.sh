#!/bin/bash

echo -e "Enter your name: \c"
read something
echo "hello $something"

echo -n "enter something: "
read something
echo "hello $something"

read -p "enter something: " something
echo "hello $something"

read -p "enter several fields: " a b
echo "hello $a"
echo "hello $b"

# read file
count=1
cat data.txt | while read line
do
    echo "Line $count: $line"
    count=$[ $count + 1 ]
done
