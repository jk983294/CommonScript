#!/bin/bash

# compress
gzip file
gzip -c file > file.gz              # compress while keep original file
gzip < file > file.gz               # compress while keep original file

# decompress
gzip -d file.gz
gunzip -c file.gz > file            # compress while keep original file
zcat file.gz > file                 # compress while keep original file
