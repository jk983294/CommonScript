#!/bin/bash

# remove all white spaces from a given file
cat data.txt | tr -d " \t"
sed -r 's/ //g' data.txt
perl -pe 's/ //g' data.txt
