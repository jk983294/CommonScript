#!/bin/bash

# exit status is the last command of that function's status
# exit status [0 - 255]

func1(){
    ls -l badfile
    echo "this is a test of a bad command"
    return 1
}

func1
echo "the exit status is $?"

# save command output to variable to get return value
func2(){
    x=2
    echo $[ $x * 2 ]
}
result=$(func2)
echo "result is $result"
