echo 1000 > /proc/sys/vm/stat_interval  # statistics updated at an interval specified as seconds
# BDI writeback affinity, block device
echo 0 > /sys/bus/workqueue/devices/writeback/numa # disable NUMA affinity for the writeback threads
echo 3 > /sys/bus/workqueue/devices/writeback/cpumask # set the affinity to only include the general purpose CPU[0-1]
echo -1 > /proc/sys/kernel/sched_rt_runtime_us # disable real-time throttling
echo -1 > /proc/sys/kernel/sched_rt_period_us # disable real-time throttling
echo 0 >/sys/devices/system/machinecheck/machinecheck<cpu>/check_interval # disable periodic check for corrected machine check errors
echo 0 > /proc/sys/kernel/watchdog # disable watchdog timer which detect and recover from software faults
echo 0 > /proc/sys/kernel/nmi_watchdog # disable the debugging feature for catching hardware hangings and cause a kernel panic
echo 1500 > /proc/sys/vm/dirty_writeback_centisecs # make write-backs of dirty memory pages occur less often than the default
echo -1 > /sys/kernel/debug/sched_tick_max_deferment # disable tick maximum deferment
echo 2 > /proc/sys/vm/overcommit_memory # disable memory overcommit
echo 0 > /proc/sys/kernel/timer_migration # disable timer migration
