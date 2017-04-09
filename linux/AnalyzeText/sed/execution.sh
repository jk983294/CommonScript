#!/bin/bash

# sed
# -e script -f file
# -n do not produce output

# number line address
sed '4s/RE/RS/' afile                                       # substitute RE for RS only line 4
sed '2,4s/RE/RS/' afile                                     # substitute RE for RS for line 2 to 4
sed '1,$s/RE/RS/' afile                                     # substitute RE for RS globally

# pattern address
sed '/ERROR/s/RE/RS/' afile                                 # substitute for all ERROR lines

# group
sed '1,${s/RE/RS/;s/dog/cat/}' afile                        # apply several cmd to the same line

# in place edit
sed -i '/^#/d;/^$/d' ntp.conf                   # delete commented line and empty line

# apply multiply cmd, -e
sed -e 's/brown/green/; s/dog/cat/; s/fox/elephant/' afile
