#!/bin/bash

# create a tracing session which writes its traces to /tmp/my-kernel-trace:
lttng create my_kernel_session --output=/tmp/my_kernel_trace

# list the available kernel trace points and system calls:
lttng list --kernel
lttng list --kernel --syscall

# create event rules
lttng enable-event --kernel sched_switch,sched_process_fork
lttng enable-event --kernel --syscall open,close
lttng enable-event --kernel --all               # it will produce a lot of data, use with caution

# start tracing:
lttng start

# do some operation on your system for a few seconds. For example, load a website, or list the files of a directory.

# destroy the current tracing session:
lttng destroy

# change perm for non root user
chown -R $(whoami) /tmp/my_kernel_trace
