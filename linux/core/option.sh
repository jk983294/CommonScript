#!/usr/bin/env bash

set -o noclobber                                        # prevent an existing file been overwritten, but file could be appended
ls /home >| out.txt                                     # override noclobber, file could be overwritten now
set -o                                                  # display all options

set -o allexport                                        # turn on auto export
set +o allexport                                        # turn off auto export
