# cgroups allows assigning and limiting hardware and system resources for processes
# Every process is assigned exactly one administrative cgroup
# Limitations for CPU, memory, disk I/O, or network bandwidth usage can be set
systemd-cgls            # displays the hierarchy tree

# set param
systemctl set-property user.slice CPUAccounting=yes             # CPU usage accounting
systemctl set-property user.slice CPUQuota=50%                  # Assigns a CPU time to processes
systemctl set-property user.slice MemoryAccounting=yes          # memory usage accounting
systemctl set-property nginx.service MemoryLow=512M             # Unused memory from processes below this limit will not be reclaimed for other use
systemctl set-property nginx.service MemoryHigh=2G              # If more memory above this limit is used, memory is aggressively taken away from the processes
systemctl set-property nginx.service MemoryMax=4G               # Processes will be killed if they use more memory than allowed
systemctl set-property system.slice DeviceAllow="/dev/sdb1 r"   # Allows read, write and mknod access
