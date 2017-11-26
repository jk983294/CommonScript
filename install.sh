#!/bin/bash

if [ ! -e ~/bin ]; then
    mkdir ~/bin
fi

cd /home/$USER/github/CommonScript/

cp ./linux/config/functions.sh ~/bin/functions.sh
# cp -r ./linux/bin ~/
cp ./linux/dev/compile/*.pl ~/bin/
# cp ./python/bin/*.py ~/bin/
chmod +x ~/bin/*

cp ./linux/config/.clang-format ~/.clang-format
cp ./linux/config/.uncrustify ~/.uncrustify
