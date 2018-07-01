#!/bin/bash

# -p    process
# -d    file descriptor
# $$    current pid
lsof -a -p $$ -d 0,1,2

# list all using TCP protocol
sudo lsof -i TCP
