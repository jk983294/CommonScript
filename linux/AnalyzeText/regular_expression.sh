#!/bin/bash

##########################################################
# BRE Basic ReExp
##########################################################
# anchor
sed -n '/^start/p' afile
sed -n '/end$/p' afile
sed '/^$/d' afile                                           # empty lines

# wildcard
sed -n '/.at/p' afile                                       # any one character
sed -n '/tre*/p' afile                                      # 0 or more times, (tr, tre, tree)
sed -n '/regular.*expression/p' afile
sed -n '/b[ae]*t/p' afile                                   # (bt bat bet)

# range
sed -n '/[Cc]at/p' afile                                    # Cat or cat
sed -n '/[^ch]at/p' afile                                   # not cat, not hat
sed -n '/[0-9][0-9][0-9]/p' afile                           # three number
awk '/[0-9][0-9][0-9]/{print $0}' afile                     # awk range query

# special group
sed -n '/[[:alpha:]]/p' afile
sed -n '/[[:digit:]]/p' afile
sed -n '/[[:alnum:]]/p' afile
sed -n '/[[:lower:]]/p' afile
sed -n '/[[:upper:]]/p' afile
sed -n '/[[:space:]]/p' afile                               # '' '\t' '\n'
sed -n '/[[:blank:]]/p' afile                               # '' '\t'

##########################################################
# ERE Extended ReExp
##########################################################
#wildcard
awk '/tre?/{print $0}' afile                                # 0 or 1 time, (tr, tre)
awk '/b[ae]?t/{print $0}' afile                             # 0 or 1 time, (bt bat bet)
awk '/tre+/{print $0}' afile                                # 1 or more time, (tre, tree)
awk '/b[ae]+t/{print $0}' afile                             # 1 or more time, (bat bet beat)
awk '/tre{1,2}/{print $0}' afile                            # 1 or 2 time, (tre, tree)
awk '/b[ae]{1,2}t/{print $0}' afile                         # 1 or 2 time, (bat bet beat)

# or
awk '/cat|dog/{print $0}' afile                             # cat or dog

# group
awk '/Sat(urday)?/{print $0}' afile                         # Sat or Saturday
awk '/(c|b)a(b|t)/{print $0}' afile                         # Sat or Saturday
