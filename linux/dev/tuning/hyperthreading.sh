echo 0 > /sys/devices/system/cpu/cpu0/online     # turn off hyperthreading
vim /boot/grub/menu.lst                             # turn off hyperthreading, noht
