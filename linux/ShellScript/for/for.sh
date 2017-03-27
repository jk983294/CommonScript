#!/bin/bash

for file in `ls ~/crobdata/`; do
    echo $file
done

for word in Perl Shell Python; do
    echo "Aha! ${word}Script"			# {} for word boundary
done
