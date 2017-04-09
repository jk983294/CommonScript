#!/bin/bash

# multi-line record, use empty line as record separator
awk 'BEGIN{FS="\n"; RS=""} {print $1, $2, $3}' data.txt
