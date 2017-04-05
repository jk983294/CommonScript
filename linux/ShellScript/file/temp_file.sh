#!/bin/bash

tempfile=$(mktemp -t test.XXXXXX)
echo "creating temp file : $tempfile"

exec 3>$tempfile

echo "this " >&3
echo "go to " >&3
echo "file " >&3

exec 3>&-

echo "done creating temp file. contents are:"
cat $tempfile

rm -f $tempfile 2> /dev/null
