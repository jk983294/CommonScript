#!/bin/bash

g++ -g test.cpp
gdb a.out

start
list
#################### TUI #########################
Ctrl + x + a            # show text UI
Ctrl + x + 2            # show assembly code window
Ctrl + x + 2            # show register window
Ctrl + x + 1            # go back to 1 window
tui reg float           # show float register group window
next                    # go to next line, the UI will also go to next line, pretty cool
Ctrl + l                # repaint UI after some cout or printf screw screen

Crtl + p                # previous command since current up arrow used for scroll text UI
Crtl + p                # next command since current down arrow used for scroll text UI

#################### python interpreter built in #########################
python print('hello world')
# run multiply python commands
python
>import os
>print ('my pid is %d' % os.getpid())
>end
# show breakpoint information
b main
b 9
python print(gdb.breakpoints())
python print(gdb.breakpoints()[0].location)
python gdb.Breakpoint('10')                     # add breakpoint at line 10
