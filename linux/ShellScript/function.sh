#!/bin/bash

# function call make more human readable

ExtractBashComments(){
    egrep "^#"
}

cat test.sh | ExtractBashComments | wc

comments=$(ExtractBashComments < test.sh)

echo $comments
