#!/usr/bin/env bash

# run level: target states for init daemon to enter
# 0 Halt
# 1 single user (root only)
# 2 multi-user (no network services / GUI)
# 3 multi-user (no GUI)
# 5 full multi-user with GUI
# 6 reboot

# boot with boot options, give run level number
# when system boots, the init daemon reads /etc/inittab to establish the default run level
# Ubuntu default run level set in /etc/init/rc-sysinit.conf

runlevel                                                # N 5 display current run level
who -r                                                  # run-level 5  2017-01-09 20:26
init 3                                                  # go to no GUI mode
