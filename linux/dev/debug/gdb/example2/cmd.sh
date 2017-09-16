#!/bin/bash

g++ -g test.cpp
gdb a.out

# setup allow coredump
ulimit -c unlimited
ulimit -c
cat /proc/sys/kernel/core_pattern
sudo bash -c 'echo core.%p.%s.%c.%P > /proc/sys/kernel/core_pattern'

# load core
gdb ./a.out core

# read execuable symbol table
file a.out

# move up and down the call stacks
bt              # trace stack
up              # move up call stack
down            # move down call stack

# check vaiable
p x             # show variable x
p crash         # show pointer variable crash, which is its address
p *crash        # show content crash pointer point to

# other check
p $pc           # show pc
disas           # disassembly
