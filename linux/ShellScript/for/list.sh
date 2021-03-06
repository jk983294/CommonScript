#!/bin/bash

for file in $(ls); do
    [[ ! -f "$file" ]] && continue                      # if not file then continue
    LA=$(stat -c %x "$file" | cut -d " " -f1)           # get last access time
    FSIZE=$(du -b "$file" | cut -f1)                    # get file size in bytes
    echo "$file is $FSIZE bytes and was last accessed on $LA"
done

for file in ~/github/CommonScript/* ~/github/Explore/*; do
    if [[ -d "$file" ]]; then
        echo "$file is directory"
    elif [[ -f "$file" ]]; then
        echo "$file is file"
    fi
done

echo "finished"
