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

# replace space in file name
for f in *\ *; do mv "$f" "${f// /_}"; done

# convert
for file in $(ls *.flv); do
    ffmpeg -i $file -codec copy $file.mp4
done

# concat
# $ cat list.txt
# file '1.mp4'
# file '2.mp4'
ffmpeg -safe 0 -f concat -i list.txt -c copy output.mp4
