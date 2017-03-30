#!/usr/bin/env bash

# check what and who are in our linux box
tty                                                                         # print the file name of the terminal connected to standard input
who                                                                         # show who is logged on
w                                                                           # show who is logged on
sudo chvt 1                                                                 # go to terminal tty1
ssh localhost                                                               # login to pesudo-terminal with ssh, probably /dev/pts/3, i.e. pesudo-terminal 3
exit                                                                        # logout

which uptime                                                                # locate a command
id                                                                          # print real and effective user and group IDs
whoami                                                                      # show login id
