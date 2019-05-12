#!/bin/bash

# compile
nasm -f elf64 -o hello.o hello.asm
ld -o hello hello.o

# install
sudo apt-get install nasm
