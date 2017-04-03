#!/bin/bash

echo $PATH
echo $USER
echo $PS1                                   # \[\e]0;\u@\h: \w\a\]${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$
echo $HOME
echo $LOGNAME
echo $TERM                                  # xterm-256color
echo $IFS                                   # input field separator, tokenilize
echo $SHELL                                 # /bin/bash

# user defined variables
FRUIT='apple'                               # only local vaiable, sub shell cannot see
echo $FRUIT
export FRUIT                                # export so that sub shell can see
echo FRUIT='apple'                          # one line to achieve local definition and export

# add PATH
export PATH=${PATH}:/home/kun/bin

# check all exported variables
env
printenv
printenv HOME
env | grep FRUIT

# check all exported and local variables
set | grep FRUIT

# delete variable, if variable deleted in child, then parent still has this variable
unset FRUIT

# variable array, index base is 0
my_array=(one two three four)
echo $my_array                              # one
echo ${my_array[2]}                         # three
echo ${my_array[*]}                         # one two three four
my_array[2]=THREE
unset my_array[2]
unset my_array                              # delete whole array
