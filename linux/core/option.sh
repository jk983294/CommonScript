#!/usr/bin/env bash

set -o                                                  # display all options

set -o allexport                                        # turn on auto export
set +o allexport                                        # turn off auto export

# clobber
set -o noclobber                                        # prevent an existing file been overwritten
ls /home >> out.txt                                     # although noclobber is on, file could still be appended
ls /home >| out.txt                                     # override noclobber, file could be overwritten now
