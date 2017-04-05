#!/bin/bash

# fd 3 works as a temp variable, point to STDOUT
# use the temp variable to recover original STDOUT

exec 3>&1
exec 1> test.out

echo "this should display in file"

exec 1>&3

echo "this should display back on the console"

# recover input
exec 4<&0
exec 0< test.in

count=1
while read line
do
    echo "Line $count: $line"
    count=$[ $count + 1 ]
done

exec 0<&4

read -p "Are you done now? " answer                         # read from STDIN
case $answer in
    Y|y) echo "goodbye";;
    N|n) echo "sorry, this is the end";;
esac
