#!/bin/bash

# "..."                                         quote spaces & wildcards
# '...'                                         quote ^ $ "
# \.                                            quote next character


echo hello     world                            # hello world
echo "hello     world"                          # hello     world
echo p*                                         # pub pint pissed
echo "p*"                                       # p*
echo $USER                                      # kun
echo "$USER"                                    # kun
echo '$USER'                                    # $USER
echo `which ls`                                 # /bin/ls  the same with echo $(which ls)
