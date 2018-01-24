#!/bin/bash

# example compile
protoc --cpp_out=. addressbook.proto

# install
git clone https://github.com/google/protobuf.git
sudo apt-get install autoconf automake libtool curl make g++ unzip
cd protobuf/
./autogen.sh
./configure --prefix=/usr
make
make check
sudo make install
sudo ldconfig               # refresh shared library cache
