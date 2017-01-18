#!/usr/bin/env bash

# boot sequence:
# 1. power on self-test, beeps and flashes, BIOS check the hardware
# 2. locate MBR, BIOS indicates the bootable disk, system reads the MBR(Master Boot Record) of that disk, the first 512 bytes
# 3. boot loader, like GRUB, it will point to the location of the bootable linux partition and kernel and RAM, multiple entries can appear in the menu allowing user to choose the OS
# 4. kernel and RAM disk, kernel is the Linux OS, the RAM disk contains the drivers required by the kernel to access the oot file system, boot loader entry points to the desired kernel and ram disk
# 5. init daemon starts, kernel access the root file system and will start init daemon, init daemon PID 1, it will start the required services we have configured

# Boot Loaders:
# 1. GRUB (GRand Unified Bootloader) CentOS 6.5 / SUSE Enterprise 11
# 2. GRUB2 Ubuntu 13.10
# 3. EXTLINUX
# 4. LILO

# GRUB stanzas (root / kernel / initrd)
cd /
cd boot
ls -l vmlinuz                                       # symbolic link to kernel

# GRUB cmd, choose the three tuple (root / kernel / initrd) then boot
root (hd0,5)
kernel /boot/vmlinuz
initrd /boot/initrd
boot

# edit GRUB
cd /boot/grub/
vim meun.lst
# stanza entry example:
#    title SUSE Linux Enterprise Server 11 SP3
#        root (hd0,5)
#        kernel /boot/vmlinuz-3.0.76-ape
#        initrd /boot/initrd-3.0.76.0.11-ape


shutdown -r now                                                 # reboot now
shutdown -h +5 "system maintenance in 5 minutes"                # power off machine, send message to all user on this box
shutdown -h +5 "system maintenance in 5 minutes" &              # power off machine running in background
shutdown -h 18:42 "system maintenance at 18:42"                 # power off machine
shutdown -c                                                     # cancel a pending shutdown event
reboot                                                          # reboot machine
poweroff                                                        # power off machine
halt                                                            # power off machine
init 0                                                          # power off machine
telinit 0                                                       # power off machine