#!/bin/bash

PROMPT_RED="\[\033[1;31m\][\u@\h \w]$\[\033[0m\] "
PROMPT_BLUE="\[\033[1;34m\][\u@\h \w]$\[\033[0m\] "
function prompt {
if [[ $1 = 'red' ]]
then
export PS1=$PROMPT_RED
else
export PS1=$PROMPT_BLUE
fi
}

# call function
prompt red
prompt blue
