#!/bin/bash

# substitute
tr '[a-z]' '[A-Z]' < input
tr '[aeiou]' '[AEIOU]' < input
tr ' ' '\n' < input
tr 'aeiou' '-' < input                              # map aeiou to -
tr 'aeiou' '-+' < input                             # map a to -, eiou to +
tr -s 'aeiou' '-' < input                           # squeeze option, remove adjacent '-'

# delete
tr -d '[aeiou]' < input                             # remove vowel
tr -cd '[aeiou]' < input                            # keep only vowel

# common type
tr '[:lower:]' '[:upper:]' < input
# [:lower:] [:upper:] [:digit:] [:alpha:] [:alnum:] [:punct:]
