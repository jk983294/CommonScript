# task scheduler decides which task to run next
# Completely Fair Scheduler (CFS), CFS tries to guarantee a fair approach to each runnable task
# the task with the minimum vruntime is always the first entry in the red-black tree

# Scheduling Policies
# SCHED_FIFO            for special time-critical applications
# SCHED_BATCH           for CPU-intensive tasks.
# SCHED_IDLE            for very low prioritized tasks.
# SCHED_OTHER           Default Linux time-sharing scheduling policy used by the majority of processes.
# SCHED_RR              Similar to SCHED_FIFO , but uses the Round Robin scheduling algorithm

# runtime change policy for pid
chrt -m                 # get valid priorities for each scheduling algorithm
chrt -p pid             # get the real-time attributes of an existing task
chrt -b -p 0 pid        # switch to SCHED_BATCH scheduling policy   

# runtime change kernel parameters
sysctl -A | grep "sched" | grep -v "domain"     # get a list of all scheduler related sysctl variables
# kernel.sched_autogroup_enabled = 1    
# kernel.sched_cfs_bandwidth_slice_us = 5000    # amount of run-time (bandwidth) transferred to a run queue from the task's control group bandwidth pool
# kernel.sched_child_runs_first = 0             # forked child runs before the parent continues execution
# kernel.sched_latency_ns = 18000000            # Targeted preemption latency for CPU bound tasks
# kernel.sched_migration_cost_ns = 500000       # increase this variable reduces task migrations to keep it hot
# kernel.sched_min_granularity_ns = 2250000     # Minimal preemption granularity for CPU bound tasks
# kernel.sched_nr_migrate = 32  
# kernel.sched_rr_timeslice_ms = 100            # time that SCHED_RR tasks are allowed to run before they are preempted
# kernel.sched_rt_period_us = 1000000   
# kernel.sched_rt_runtime_us = 950000   
# kernel.sched_schedstats = 0   
# kernel.sched_tunable_scaling = 1  
# kernel.sched_util_clamp_max = 1024    
# kernel.sched_util_clamp_min = 1024    
# kernel.sched_wakeup_granularity_ns = 3000000  # wake-up preemption granularity, Lowering it improves wake-up latency and throughput for latency critical tasks

# stats
cat /proc/sched_debug | less
# tree-key column                   the task's virtual runtime
# switches column                   total number of switches
# prio column                       the process priority
# wait-time column                  time the task waited to be scheduled
# sum-exec column                   time (in ns) the task was running on the processor
# sum-sleep column                  time (in ns) the task was asleep

cat /proc/schedstat                 # check /usr/src/linux/Documentation/scheduler/sched-stats.txt

cat /proc/pid/sched                 # stats for specified pid
