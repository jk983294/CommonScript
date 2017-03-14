#!/bin/bash

# /etc/nologin                          temporary disable logins

last                                    # recent login /var/log/wtmp
lastlog                                 # last login time for all users

ulimit                                  # display/set limit for user
ulimit -a                               # available limits
ulimit -u 8000                          # set max user process count to 8000
less /etc/security/limits.conf          # persist limit config
