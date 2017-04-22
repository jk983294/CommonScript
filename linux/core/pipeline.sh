#!/bin/bash

# unnamed pipe |
ls -l | wc -l                                           # count file

# named pipe
# it support IPC(inter-process communication), one shell redirect the output to the file, while another read from it
# better to create pipe in /tmp folder since it allows different users could communicate
mkfifo /tmp/jkpipe
ls -l > /tmp/jkpipe                                     # shell process 1
wc -l < /tmp/jkpipe                                     # shell process 2
