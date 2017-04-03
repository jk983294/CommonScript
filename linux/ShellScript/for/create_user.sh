#!/bin/bash

# use arguments
# ./create_user.sh a b c d

for u in $*; do
    echo "add user $u"
done

echo "finished"
