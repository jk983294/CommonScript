#!/bin/bash

# temporary redirect to STDERR
# usage: ./temporary.sh 2> error.log
# then error msg will be record in error.log and normal output will show in console
echo "this is an error" >&2
