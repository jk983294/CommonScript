cat /etc/default/grub
cat /proc/cmdline


crashkernel=auto # switch to a 'crash kernel' upon panic
quiet		# disable most log messages

# 抢占被长时间关闭而导致进程无法调度 soft lockup
# 中断被长时间关闭而导致更严重的问题 hard lockup
nosoftlockup	# disable the soft-lockup detector, kernel线程 < 时钟中断 < NMI中断
nmi_watchdog=0 # turn hardlockup detector in nmi_watchdog off

intel_idle.max_cstate=0 # disables intel_idle and fall back on acpi_idle
processor.max_cstate=0 # limit processor to maximum C-state, C0 Operating State CPU fully turned on
mce=ignore_ce # disable features for corrected errors
idle=poll # slightly improve the performance of waking up a idle CPU

hugepagesz=2MB # Valid pages sizes on x86-64 are 2M and 1G ("pdpe1gb" cpuinfo flag)
hugepages=4096
hugepagesz=1GB # HugeTLB pages to allocate at boot
hugepages=6 # The size of the HugeTLB pages
default_hugepagesz=1G # used for SHM, and default size when mounting hugetlbfs filesystems
transparent_hugepage=never # kernel attempts to allocate hugepages whenever possible, disable this tendency

numa_balancing=disable # moves tasks closer to the memory they are accessing, do it manually since it has costs
cat /proc/sys/kernel/numa_balancing # check numa_balancing
pcie_aspm=performance # disable PCIe Active State Power Management
intel_pstate=disable # Do not enable intel_pstate as the default scaling driver for the supported processors
audit=0 # kernel audit is disabled
irqaffinity=0 # set the default irq affinity mask, the argument is a cpu list
spectre_v2=off # disable both the kernel and the user space protections, vulnerability that affects modern microprocessors that perform branch prediction
nopti # Control Page Table Isolation of user and kernel address spaces, Disabling this feature removes hardening, but improves performance of system calls and interrupts
tsc=reliable # mark tsc clocksource as reliable, this disables periodic synchronization

isolcpus=4,6,8,10 # isolate a given set of CPUs from disturbance
rcu_nocbs=4,6,8,10 # remove one or more CPUs from the candidates for running RCU callbacks
nohz_full=4,6,8,10 # the specified list of CPUs whose tick will be stopped whenever possible
