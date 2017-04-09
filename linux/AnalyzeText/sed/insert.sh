#!/bin/bash

# insert will before match lines
# append will after match lines

echo "original data" | sed 'i\to be inserted'                       # insert before original data
sed '3i\to be inserted' data.txt                                    # insert before line 3
sed '1i\to be appended' data.txt                                    # append before file start

echo "original data" | sed 'a\to be appended'                       # append after original data
sed '3a\to be appended' data.txt                                    # append after line 3
sed '$a\to be appended' data.txt                                    # append after file end
