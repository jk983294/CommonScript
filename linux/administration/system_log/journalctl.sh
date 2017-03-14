#!/bin/bash

# journalctl, view and log management
usermod -a -G adm username              # member of adm to journalctl permission

journalctl                              # display journal log with pager
journalctl -n 50                        # display last 50 entries
journalctl -n 50 -p err                 # display last 50 entries with err priority
journalctl -f                           # follow the journal log


/run/log/journal                        # in memory

# persist journal log
mkdir /var/log/journal
systemctl restart systemd-journald
