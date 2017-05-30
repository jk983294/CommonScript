#!/bin/bash

# trace system call and signal
strace ./a.out
strace cat /dev/null
strace -p pid
# record relative timestamp on call entries
strace -r ./a.out
# record time spent in calls
strace -T ./a.out
# summary of times and errors for each call
strace -c ./a.out
# sorting the summary table on any column
strace -c -S calls ./a.out
# enable child process tracing
strace -f ./a.out
# filter
strace -e trace=file,open,process,network,ipc ./a.out
strace -e trace=!file ./a.out

# trace library call
ltrace ./a.out
ltrace cat /dev/null
ltrace -p pid
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
# filter
ltrace -e trace=file,open,process,network,ipc ./a.out
ltrace -e trace=!file ./a.out
