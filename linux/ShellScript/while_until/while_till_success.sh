#!/bin/bash

while true; do
    # ping -c 1 google.com > /dev/null 2>&1 && break
    ping -c 1 baidu.com > /dev/null 2>&1 && break
    sleep 1
done
