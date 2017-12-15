#!/bin/bash

if [[ -n "$1" ]]; then
    echo "clean up emit file for process $1"
    /bin/rm /var/tmp/emit.$1.pids
    /bin/rm /var/tmp/emit.$1.lock
else
    echo "clean up all emit files"
    /bin/rm /var/tmp/emit.*.pids
    /bin/rm /var/tmp/emit.*.lock
fi
