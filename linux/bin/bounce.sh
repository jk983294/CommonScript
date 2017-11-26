#!/bin/bash

. log.sh

#
# usage: bounce.sh process
#

case $# in
    1) PROC=$1
        ;;
    *) log_die "Usage: $0 <process>\n"
        ;;
esac

PIDS=`ps -ef | grep iku | grep $PROC | awk '{printf("%s ", $2)}'`

for PID in $PIDS
do
    PNAME=`ps -ef | grep -w $PID | grep iku | awk '{n=split($10,a,"/"); print a[n]}'`
    if [[ $PNAME == $PROC ]]; then
        kill -USR2 $PID
    fi
done
