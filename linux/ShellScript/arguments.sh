#!/bin/bash

# $0 $1 ... ${10}
# $0 script path
# $* all parameters except script name
# $# parameter count except script name
echo "running script $0"
echo "script parameter count: $#"

echo -e "Enter your name: \c"
read INPUT_NAME
echo "hello $INPUT_NAME"
exit 0
