#!/usr/bin/env bash

lsmod                                       # list currently loaded kernel modules
lsmod | grep psmouse                        # show module info
grep psmouse /proc/modules
modprobe -r psmouse                         # unload kernel module psmouse
modprobe psmouse                            # load kernel module psmouse
modprobe -v psmouse                         # load module with verbose info

modinfo -d psmouse                          # description psmouse module
modinfo -p psmouse                          # parameter could pass into

cd /etc/modprobe.d/
less alsa-base.conf
less blacklist.conf                         # never get loaded modules, usually one driver replaced by another