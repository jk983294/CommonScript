#!/bin/bash

# run a command immune to hangups, with output to a non-tty
# basicly command won't be killed when shell session got killed

nohup command > myout.file 2>&1 &
