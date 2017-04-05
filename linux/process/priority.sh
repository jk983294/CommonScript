#!/bin/bash

# nice [-20, 19] high - low, default is 0
nice -n 10 ./test.sh > test.out &
nice -n -10 ./test.sh > test.out &

# renice
# normal user can only renice his process, he can only decrease priority
# root can renice to any priority
ps -p 5505 -o pid,ppid,ni,cmd
renice -n 10 -p 5505
ps -p 5505 -o pid,ppid,ni,cmd
