#!/bin/bash

# source level analysis with perf annotate
perf record ./bench
perf annotate -d ./bench    # code disassembled and each instruction will have its relative percentage
perf annotate -k /tmp/vmlinux -d symbol     # perf annotate on kernel code

# you can get more informative output via compile your bin with -ggdb
