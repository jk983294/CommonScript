#!/bin/bash

function print {
    echo "var1 $1 var2 $2"
}

cat test.txt | grep -v '^#' | while read line; do
    var1=$(echo $line | cut -f1)
    var2=$(echo $line | cut -f2)
    print $var1 $var2
done

while read line; do
    var1=$(echo $line | cut -f1)
    var2=$(echo $line | cut -f2)
    print $var1 $var2
done < test.txt
