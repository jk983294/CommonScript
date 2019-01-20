#!/bin/bash

g++ -c -I. hello_trace_point.cpp
g++ -c hello.cpp
g++ -o hello hello.o hello_trace_point.o -llttng-ust -ldl

./hello world and beyond

# start an LTTng session daemon:
lttng-sessiond --daemonize

# list the available user space tracepoints:
lttng list --userspace

#  create a tracing session:
lttng create my-user-space-session

# create an event rule which matches the hello_world:my_first_tracepoint event name:
lttng enable-event --userspace hello_world:my_first_tracepoint

# start tracing:
lttng start

# go back to the running hello application and press Enter.
# The program executes all tracepoint() instrumentation points and exits.

# destroy the current tracing session:
lttng destroy


babeltrace /home/kun/lttng-traces/my-user-space-session-20190117-232103/* > /tmp/user.space.log
