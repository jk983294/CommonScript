#!/bin/bash

echo "--help" | cat                                 # cat, content is --help
echo "--help" | xargs cat                           # cat --help, cmd parameters


find /sbin -perm 700 | xargs ls -l
find /sbin -name "mkf*" | xargs ls -l
