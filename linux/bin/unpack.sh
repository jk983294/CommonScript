#!/bin/bash

target_module=$1
if [[ $target_module == "." ]]; then
    target_module=$(basename "$cur_path")
    echo "target_module changed $target_module"
fi
tar -xzvf $target_module.tgz
cd $target_module
mkdir install
cd install
cmake ..
make
cd ..

if [[ -d math ]]; then
    ln -s install/Makefile Makefile
fi