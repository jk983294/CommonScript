#!/bin/bash

$ gcc -g hello.c
$ addr2line -e a.out 0x400536
hello.c:21
