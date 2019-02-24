#!/bin/bash

# in call graph, you first see callee, then you expand it, you can see the caller
perf report -g                      # show call graph report
# show reverted graph, filter out 50% contribution calls
perf report -g 'graph,0.5,caller'

# dig into code press 'a' key, which is annotate
# '->' key to follow branch, i.e. mov family

# cpu mode
perf record -a ./bench
perf report --sort=cpu              # useful to determine if the workload is well balanced

perf report
# Samples: 8K of event 'cycles:u', Event count (approx.): 4731527587
# Overhead  Command       Shared Object        Symbol                                                                                                                                          ◆
#   27.92%  vector_bench  libc-2.17.so         [.] malloc

# privilege level
# [.] : user level
# [k]: kernel level
# [g]: guest kernel level (virtualization)
# [u]: guest os user space
# [H]: hypervisor

# view
perf report --sort=dso
perf report --sort=srcline

# kernel reporting
# tool does not know how to extract symbols form compressed kernel images (vmlinuz). Therefore,
# users must pass the path of the uncompressed kernel using the -k option,
# this works only if the kernel is compiled to with debug symbols
perf report -k /tmp/vmlinux
