#!/bin/bash

# trace system call and signal
strace ./a.out
strace cat /dev/null
strace -p pid
strace -fp pid              # trace process also its thread
# record relative timestamp on call entries
strace -r ./a.out
# record time spent in calls
strace -T ./a.out
# histogram of the number of system calls and the time spent at the termination of strace
strace -c ./a.out
# sorting the summary table on any column
strace -c -S calls ./a.out
# enable child process/thread tracing
strace -f ./a.out
# record timestamp and output to file
strace -t -o strace_sleep.txt sleep 1
# filter
strace -e trace=file,open,process,network,ipc ./a.out
strace -e trace=!file ./a.out
strace -Tfe trace=open,read,write ./program         # only trace file related operations
# filter out futex, maybe futex is not under concern
strace strace -Tf ./program 2>&1 | grep -v futex
# find out which config files a program reads on startup
trace ./program 2>&1 | grep .xml
# What is that process doing RIGHT NOW? probably wait on mutex
strace -p 15427
Process 15427 attached - interrupt to quit
futex(0x402f4900, FUTEX_WAIT, 2, NULL
Process 15427 detached
# Why can't I connect to that server?
strace -e poll,select,connect,recvfrom,sendto nc www.news.com 80

# trace library call
ltrace ./a.out
ltrace cat /dev/null
ltrace -p pid
# trace system calls as well
ltrace -S ./a.out
# trace result to file
ltrace -o ltrace_find.txt ./a.out
# record relative timestamp on call entries
ltrace -r ./a.out
# record time spent in calls
ltrace -T ./a.out
# summary of times and errors for each call
ltrace -c ./a.out
# sorting the summary table on any column
ltrace -c -S calls ./a.out
# enable child process tracing
ltrace -f ./a.out
# display only the symbols included in a specific library
ltrace -l /lib64/librt.so.1 sleep 1
# filter
ltrace -e trace=file,open,process,network,ipc ./a.out
ltrace -e trace=!file ./a.out
ltrace -e fnmatch,strlen find /etc -name xorg.conf
