#!/bin/bash

babeltrace /tmp/my_kernel_trace/* > /tmp/trace.log
cat /tmp/trace.log | grep sched_switch | wcl
cat /tmp/trace.log | grep syscall_entry_close | wcl

# python script
python3 top5proc.py /tmp/my_kernel_trace/kernel
