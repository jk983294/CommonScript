#!/bin/bash

# example compile
protoc --cpp_out=. addressbook.proto

# install protobuf
git clone https://github.com/google/protobuf.git
sudo apt-get install autoconf automake libtool curl make g++ unzip
cd protobuf/
./autogen.sh
./configure --prefix=/usr
make
make check
sudo make install
sudo ldconfig               # refresh shared library cache
which protoc                # 查看软件的安装位置
protoc --version            # 检查是否安装成功

# grpc
git clone https://github.com/grpc/grpc.git
cd grpc
git submodule update --init
make
sudo make install
sudo ldconfig

# python install
pip install grpcio
