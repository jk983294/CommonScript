#!/usr/bin/env bash

# grep
# i             case insensitive
# v             reverse the search
# e             more than one expression
# E             enhanced complex expressions (egrep)

grep Server /etc/ntp.conf                                   # search 'Server'
grep -i Server /etc/ntp.conf                                # search 'Server' in case insensitive mode
grep '\bserver\b' /etc/ntp.conf                             # search for word 'server' so that 'servers' won't show
grep '^server\b' /etc/ntp.conf                              # search for word 'server' which is start of line
grep '\bserver$' /etc/ntp.conf                              # search for word 'server' which is end of line
grep -ve'^#' -ve'^$' /etc/ntp.conf                          # don't show commented line and empty line
grep -E '[A-Z]{1,2}[0-9]{1,2}[A-Z]?\s[0-9][A-Z]{2}' a.txt   # search for postcode