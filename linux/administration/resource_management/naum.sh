# Automatic NUMA Balancing migrates data on demand to memory nodes that are local to the CPU accessing that data
# Automatic NUMA balancing happens in three basic steps:
#   1. A task scanner periodically scans tasks' address space and marks the memory to force a page fault when the data is next accessed
#   2. The next access to the data will result in a NUMA Hinting Fault. Based on this fault, the data can be migrated to a memory node associated with the task accessing the memory.
#   3. To keep a task, the CPU it is using and the memory it is accessing together, the scheduler groups tasks that share data.

numactl --hardware                              # show the memory configuration of the machine
cat /proc/sys/kernel/numa_balancing
echo "1" > /proc/sys/kernel/numa_balancing      # enable numa_balancing
cat /proc/vmstat | grep numa                    # monitor