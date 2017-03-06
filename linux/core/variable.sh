#!/bin/bash

echo $PATH
echo $USER
echo $PS1                                   # \[\e]0;\u@\h: \w\a\]${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$

# user defined variables
FRUIT='apple'                               # only local vaiable, sub shell cannot see
echo $FRUIT
export FRUIT                                # export so that sub shell can see
echo FRUIT='apple'                          # one line to achieve local definition and export

# add PATH
export PATH=$PATH:/home/kun/bin

# check all exported variables
env
env | grep FRUIT

# check all exported and local variables
set | grep FRUIT
