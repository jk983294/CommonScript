#!/bin/bash

co -l somefile                  # -l lock the retrieved revision for the caller
ci -u somefile                  # checkin + unlocked checkout
rlog somefile                   # print log messages and other information about RCS files
rcsdiff -r1.5 -r1.4 somefile    # compare 1.5 against 1.4
rcsdiff somefile                # compare local against latest revision on the default branch,  useful for determining what you changed since the last checkin.
