#!/bin/bash

cur_path=$(pwd)
target_folder=$(pwd)
target_module=$(basename "$cur_path")
if [[ $target_module == "." ]]; then
    target_module=$(basename "$cur_path")
    echo "target_module changed $target_module"
fi
tmp_folder=/tmp/$USER$(date '+%Y%m%d%H%M%S')/$target_module
mkdir -p $tmp_folder
cp -r $target_folder/include $target_folder/src $target_folder/etc $tmp_folder
cp $target_folder/*.xml $tmp_folder
cp $target_folder/Makefile $tmp_folder
cp $target_folder/CMakeLists.txt $tmp_folder
if [[ -f $target_folder/submakefile ]]; then
    cp $target_folder/submakefile $tmp_folder
fi
if [[ -d $target_folder/python ]]; then
    echo "pack python"
    cp -r $target_folder/python $tmp_folder
fi
if [[ -d $target_folder/test ]]; then
    echo "pack test"
    cp -r $target_folder/test $tmp_folder
fi
if [[ -d $target_folder/example ]]; then
    echo "pack example"
    cp -r $target_folder/example $tmp_folder
fi
cd $(dirname "$tmp_folder")
tar -czvf $target_module.tgz ./$target_module
cp $target_module.tgz $cur_path
rm -rf $(dirname "$tmp_folder")
echo "$cur_path $target_folder $target_module $tmp_folder"
#tar -xzvf $target_module.tgz