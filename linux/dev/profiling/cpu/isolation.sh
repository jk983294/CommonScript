# know the list of isolated cpu for the current running kernel
cat /sys/devices/system/cpu/isolated

## find cores being used
ps -aeF | awk '{print $4}' | sort | uniq
