#!/bin/bash

g++ -g test.cpp
gdb a.out

# load core
gdb ./a.out core

bt              # trace stack
frame 4         # go to frame 4

(gdb) p a
$1 = std::vector of length 0, capacity 0
(gdb) p a[0]
Cannot access memory at address 0x0
