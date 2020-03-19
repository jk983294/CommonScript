# system control parameters are used to modify the Linux kernel parameters at runtime
sysctl -a                   # list all parameters
sysctl dev                  # (/proc/sys/dev/) Device-specific information
sysctl fs                   # (/proc/sys/fs/) Used file handles, quotas, and other file system-oriented parameters. 
sysctl kernel               # (/proc/sys/kernel/) Information about the task scheduler, system shared memory, and other kernel-related parameters
sysctl net                  # (/proc/sys/net/) Information about network bridges, and general network parameters 
sysctl vm                   # (/proc/sys/vm/) Entries in this path relate to information about the virtual memory, swapping, and caching

sysctl -w PARAMETER=VALUE   # set a parameter for the current session, use the command 
# to permanently change a setting, add a line PARAMETER=VALUE to /etc/sysctl.conf
