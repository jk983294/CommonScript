#!/bin/bash

# ./case.sh /etc directory should work

if [[ ! -d $1 ]]; then
    echo "usage: $0 <directory>"
    exit 1
fi

case $2 in
    "directory" | "dir")
        find $1 -maxdepth 1 -type d
        ;;
    "link")
        find $1 -maxdepth 1 -type l
        ;;
    *)
        echo "usage: $0 <directory> directory|link"
        ;;
esac

exit 0
