#!/bin/bash

apropos who                     # search the manual page names and descriptions
man -k who                      # search the manual page with keyword who
whatis ls                       # display one-line manual page descriptions
man ls                          # an interface to the on-line reference manuals
which ls                        # bin path
type ls                         # show alias

man -s 1 intro                  # introduction to user commands in section 1
man -s 3 printf                 # search C function printf

# Section Description
# 1 General commands
# 2 System calls
# 3 Library functions, covering in particular the C standard library
# 4 Special files (usually devices, those found in /dev) and drivers
# 5 File formats and conventions, like /etc/passwd
# 6 Games and screensavers
# 7 Miscellanea
# 8 System administration commands and daemons
