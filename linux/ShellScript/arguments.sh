#!/bin/bash

# $0 $1 ... ${10}
# $0 script path
# $* all parameters except script name, only one word
# $@ all parameters except script name, several words
# $# parameter count except script name
# ${!#} last parameter
# $? exit status of the most recently executed foreground pipeline
# $$ the process ID of the shell
# $! process ID of the job most recently placed into the background
# $- set to the absolute pathname used to invoke the shell
echo "script absolute pathname: $_"
echo "running script $0"
script_name=$(basename $0)
echo "base script name $script_name"
echo "script parameter count: $#"
echo "last parameter: ${!#}"

echo "exit status of the most recently executed foreground pipeline: $?"

echo "the process ID of the shell: $$"
sleep 100 &
echo "process ID of the job most recently placed into the background: $!"

# test parameter exist
if [[ -n "$1" ]]; then
    echo "parameter 1 exists"
else
    echo "parameter 1 not exists"
fi
# test parameter count correct
if (( $# != 2 )); then
    echo "must two parameters supplied"
else
    echo "two parameters supplied"
fi

# difference of $* and $@
for param in "$*"; do
    echo "\$* parameter: $param"
done

for param in "$@"; do
    echo "\$@ parameter: $param"
done

exit 0
