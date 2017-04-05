#!/bin/bash

function test_gloabl {
    value=$[ $value * 2 ]
}

function test_local {
    local temp=$[ $value + 1 ]              # this local temp won't change global temp variable
    result=$[ $temp * 2 ]
}

temp=4
value=3

test_gloabl
echo "value is $value"                      # 6

test_local
echo "temp is $temp"                        # 4
echo "result is $result"                    # 14
