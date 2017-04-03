#!/bin/bash

# $0 $1 ... ${10}
# $0 script path
# $* all parameters except script name, only one word
# $@ all parameters except script name, several words
# $# parameter count except script name
# ${!#} last parameter
echo "running script $0"
script_name=$(basename $0)
echo "base script name $script_name"
echo "script parameter count: $#"
echo "last parameter: ${!#}"

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

# read in
echo -e "Enter your name: \c"
read INPUT_NAME
echo "hello $INPUT_NAME"
exit 0
