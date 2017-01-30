#!/usr/bin/env bash

# pseudo file system maintains information about the currently running system
# /dev about devices, contains not only physical devices bu also pesudo devices
# /sys about physical devices' metadata information
# /dev/tty & /dev/pts/2 pesudo terminal, tty1 - tty6 is physical terminal, tty7 after is pesudo-terminal
# /proc current control set, information about the system
# /proc/number represents resource usage of a running process on the system, PID 1 the init process and the first process started by kernel

cd /sys/block/sda                                                               # contain the metadata of sda partition
cat size                                                                        # display sda partition size

cd /dev
ls sda*                                                                         # list all physical partitions

cd /proc
cat version
cat /proc/sys/net/ipv4/ip_forward
cat meminfo                                                                     # display memory usage information
cat mounts                                                                      # show mounted devices
cat interrupts                                                                  # show the currently connected devices and amount of interrupts the CPU deals with
head -n 10 interrupts                                                           # only show first 10 interrupts information
watch -n1 head -n 10 interrupts                                                 # monitor first 10 interrupts information every 1s
ps                                                                              # show process information
cd /proc/2640                                                                   # go to process 2640 resources folder


