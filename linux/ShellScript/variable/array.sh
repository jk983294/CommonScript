#!/bin/bash

myarray=(0 1 2 3 4 5)
echo "${myarray[0]}"                # 0
echo "${myarray[5]}"                # 5
echo "${myarray[*]}"                # 0 1 2 3 4 5
echo "${myarray[@]}"                # 0 1 2 3 4 5
echo "${#myarray[*]}"               # 6
echo "${#myarray[@]}"               # 6

function array_double {
    local original_array
    local new_array
    local count
    local i
    original_array=($(echo "$@"))
    new_array=($(echo "$@"))
    count=$#
    for (( i = 0; i < $count; i++ )); do
        new_array[$i]=$[ ${original_array[$i]} * 2 ]
    done
    echo ${new_array[*]}
}
arg1=$(echo ${myarray[*]})
result=($(array_double $arg1))
echo "new array is ${result[*]}"
