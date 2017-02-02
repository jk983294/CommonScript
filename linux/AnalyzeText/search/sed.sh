#!/usr/bin/env bash

# sed
# i                 in place edit
# d                 delete

# search
sed '/^#/d;/^$/d' ntp.conf                      # don't show commented line and empty line


# edit
sed -i '/^#/d;/^$/d' ntp.conf                   # delete commented line and empty line

