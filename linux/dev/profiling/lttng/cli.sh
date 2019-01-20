#!/bin/bash

## Tracing control command-line interface
### below work on the current session if not specified
### add-context/destroy/disable-channel/disable-event/enable-channel/enable-event/load/regenerate/save/snapshot/start/stop/track/untrack/view

### session
lttng-sessiond --daemonize                                                          # start a user session daemon
lttng create my_session                                                             # create a tracing session, default location is $LTTNG_HOME/lttng-trace/name
lttng create my_session --output=/tmp/some_directory
lttng list                                                                          # list all the existing tracing sessions
lttng set-session other-session                                                     # switch session
lttng destroy                                                                       # destroy current session
lttng status                                                                        # get the status of the current session
lttng list my_session                                                               # get the status of specified session
lttng start                                                                         # start tracing current session
lttng stop                                                                          # stop tracing current session
lttng save my_session                                                               # saves tracing session configurations to $LTTNG_HOME/.lttng/sessions
lttng load my_session                                                               #  restores your saved tracing session

### event
lttng enable-event --kernel sched_switch                                            # create an event rule target a Linux kernel tracepoint
lttng enable-event --kernel --syscall open,write,read,close                         # create an event rule matching four Linux kernel system calls
lttng enable-event --kernel sched_switch --filter='prev_comm == "bash"'             #  tracepoints with filter expressions
lttng enable-event --kernel --all --filter='$ctx.tid == 1988 || $ctx.tid == 1534'
lttng enable-event --userspace my_app:'*' --loglevel=TRACE_INFO                     # enable user space tracepoint of a given tracepoint provider with a log level range
lttng enable-event --userspace my_app:my_tracepoint --channel=my-channel            # enable rule attached to a specific channel
lttng enable-event --userspace 'lttng_ust_tracef:*'                                 # enable tracef
lttng enable-event --userspace 'lttng_ust_tracelog:*' --loglevel=TRACE_WARNING      # enable tracelog
lttng disable-event --userspace --all-events                                        # disable all events

### channel
lttng enable-channel --kernel my-channel                                            # create a Linux kernel channel with default attributes.
lttng disable-channel --kernel my-channel                                           # disable existing channel
lttng enable-channel --userspace --num-subbuf=4 my-channel                          # 4 sub-buffers
lttng enable-channel --userspace --subbuf-size=1M my-channel                        # 1 MiB each buffer
lttng enable-channel --userspace --buffers-pid my-channel                           # channel per instrumented process
lttng enable-channel --userspace --overwrite my-channel                             # in overwrite (or flight recorder) mode

### context
### process ID, thread ID, process name, process priority, hostname, performance counters
lttng add-context --list                                                            # list full list of available context fields
lttng add-context --userspace --type=vpid                                           # add the virtual process identifier
lttng add-context --userspace --type=perf:thread:cpu-cycles                         # add per-thread CPU cycles count
lttng add-context --kernel --channel=my-channel --type=tid                          # add tid

### track process id
lttng untrack --pid --all
lttng track --pid=3,4,7,10,13
lttng untrack --pid=3,7,10,13
lttng track --pid --all

### snapshot
lttng create my-session --snapshot
lttng snapshot record --name=my-first-snapshot                                      # take a snapshot of the current sub-buffers of a given tracing session
lttng snapshot list-output                                                          # snapshot file location

### blocking feature
lttng enable-channel --userspace --blocking-timeout=inf blocking-channel
lttng enable-event --userspace --channel=blocking-channel --all
LTTNG_UST_ALLOW_BLOCKING=1 ./a.out

### tracepoint
lttng list --userspace                                                              # list the available user space tracepoints
lttng list --kernel --syscall                                                       # list the available Linux kernel system call tracepoints.
