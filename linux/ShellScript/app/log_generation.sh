#!/bin/bash

time=$(date +%y%m%d%H%M%S)
ls /usr/bin -al > log.$time                                                     # new log for every execution

time1=$(date +%y%m%d)
ls /usr/bin -al >> log.$time1                                                   # same log for the same day
