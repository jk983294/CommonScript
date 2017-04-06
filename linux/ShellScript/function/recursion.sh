#!/bin/bash

function factorial {
    if [[ $1 -eq 1 ]]; then
        echo 1
    else
        local temp=$[ $1 - 1 ]
        local result=$(factorial $temp)
        echo $[ $result * $1 ]
    fi
}

result=$(factorial 5)
echo "result is $result"
