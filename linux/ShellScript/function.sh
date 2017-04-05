#!/bin/bash

# function call make more human readable

ExtractBashComments(){
    egrep "^#"
}

function ExtractBashComments1 {
    egrep "^#"
}

cat test.sh | ExtractBashComments | wc

comments=$(ExtractBashComments < test.sh)
echo $comments

comments=$(ExtractBashComments1 < test.sh)
echo $comments
