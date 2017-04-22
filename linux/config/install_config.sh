#!/bin/bash

if [ ! -e ~/bin ]; then
    mkdir ~/bin
fi

cp functions.sh ~/bin/functions.sh
chmod 777 ~/bin/functions.sh

cp .tmux.conf ~/.tmux.conf
cp .vimrc ~/.vimrc
cp .bashrc ~/.bashrc
