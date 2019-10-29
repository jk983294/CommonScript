echo 0 > /sys/devices/system/cpu/cpu0/online     # turn off hyperthreading
vim /boot/grub/menu.lst                             # turn off hyperthreading, noht

# speedstep
cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors # read the current available settings
echo performance > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor # turn off speedstep
cat /proc/cpuinfo
cpufreq-info

cpus="2 3"
for cpu in $cpus
do
    echo "performance" > /sys/devices/system/cpu/cpu$cpu/cpufreq/scaling_governor
    echo 0 > /sys/devices/system/machinecheck/machinecheck$cpu/check_interval
done

# cpu idle
grep CONFIG_CPU_IDLE /boot/config-4.15.0-29-generic
