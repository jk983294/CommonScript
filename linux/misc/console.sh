#!/usr/bin/env bash

# physical console: tty1 - tty6, tty stands for tel type
# tty1 - tty6 are permanent files in system
# physical console means it will turn off GUI, only offer you a console
chvt 1                                                                      # change virtual terminal
tty                                                                         # print the file name of the terminal connected to standard input
who                                                                         # show who is logged on
exit
logout

# graphical console normally tty7, it is pesudo console, it is under graphical environment
# pesudo console: telnet TCP 23 / SSH TCP 22
# represent remote connections from telnet or SSH, dynamic created /dev/pts/x
echo $SSH_TTY                                                               # /dev/pts/2
echo $SSH_CONNECTION                                                        # 10.0.2.2 2273 10.0.2.15 22
echo $SSH_CLIENT                                                            # 10.0.2.2 2273 22

# shell type: bash / bsh / ksh / zsh
chsh -l                                                                     # list all available shell
cat /etc/shells                                                             # list all available shell
cat /etc/passwd                                                             # check your default shell
