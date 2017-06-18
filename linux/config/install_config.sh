#!/bin/bash

if [ ! -e ~/bin ]; then
    mkdir ~/bin
fi

cp functions.sh ~/bin/functions.sh
chmod 777 ~/bin/functions.sh

cp .clang-format ~/.clang-format
cp .uncrustify ~/.uncrustify
