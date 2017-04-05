#!/bin/bash

trap "echo 'sorry! I have trapped Ctrl-C'" SIGINT
trap "echo 'sorry! I have trapped USR1'" USR1
trap "echo 'sorry! I have trapped USR2'" USR2

COUNT=10
while (( COUNT > 0 )); do
    echo -e "$COUNT \c"
    sleep 1
    (( COUNT-- ))
done

trap -- SIGINT                                          # remove trap
trap - SIGINT                                           # restore to default signal action
COUNT=10
while (( COUNT > 0 )); do
    echo -e "$COUNT \c"
    sleep 1
    (( COUNT-- ))
done
