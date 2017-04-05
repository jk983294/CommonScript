#!/bin/bash

add(){
    echo $[ $1 + $2 ]
}

value=$(add 10 20)
echo "result is $value"

add_array(){
    local sum=0
    local newarray
    newarray=($(echo "$@"))
    for value in ${newarray[*]}; do
        sum=$[ $sum + $value ]
    done
    echo $sum
}

myarray=(0 1 2 3 4 5)
arg1=$(echo ${myarray[*]})
result=$(add_array $arg1)
echo "result is $result"
