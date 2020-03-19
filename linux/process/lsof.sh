#!/bin/bash

# -p    process
# -d    file descriptor
# $$    current pid
lsof -a -p $$ -d 0,1,2


sudo lsof -i TCP            # list all using TCP protocol
lsof -i                     # list all TCP/UDP
