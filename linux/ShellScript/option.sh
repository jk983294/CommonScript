#!/bin/bash

# : means argument with value
# ./option.sh -ab jk -c
# ./option.sh -ab "j k" -c
# ./option.sh -abjk
# ./option.sh -ab jk -c arg1 arg2

while getopts :ab:c opt; do
    case "$opt" in
        a) echo "found option a";;
        b) echo "found option b, with value $OPTARG, option index is $OPTIND";;
        c) echo "found option c";;
        *) echo "unknown option: $opt";;
    esac
done

shift $[ $OPTIND - 1 ]

for param in "$@"; do
    echo "\$@ parameter: $param"
done
