#!/bin/bash

IFS.OLD=$IFS
IFS=$'\n'                                                                       # output by lines
for file in $(ls -l ~/github/); do
    echo $file
done
IFS=$IFS.OLD                                                                    # restore old field seporator

for word in Perl "data with space" "data with 'single quote'" Shell Python; do
    echo "Aha! ${word}Script"                                                   # {} for word boundary
done

list="a b c d"
list=$list" append"
for word in $list; do
    echo "word: $word"
done
