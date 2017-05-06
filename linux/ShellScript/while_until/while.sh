#!/bin/bash

COUNT=10
while (( COUNT > 0 )); do
    echo -e "$COUNT \c"
    sleep 1
    (( COUNT-- ))
done

while true; do
    sleep 1
    if (( COUNT > 10 )); then
        break
    fi
    (( COUNT++ ))
    echo "Heartbeat check."
done
