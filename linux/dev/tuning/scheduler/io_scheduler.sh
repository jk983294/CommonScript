# change I/O scheduler (cfq, noop, deadline)
echo cfq > /sys/block/sda/queue/scheduler

# CFQ (Completely Fair Queuing) param:
cat /sys/block/sda/queue/iosched/slice_idle_us      # scheduler waits for a while before scheduling the next thread
cat /sys/block/sda/queue/iosched/quantum            # maximum number of requests that are being processed at once
cat /sys/block/sda/queue/iosched/low_latency        # dynamically adjust the length of the time slice by aiming to meet target_latency
cat /sys/block/sda/queue/iosched/target_latency
cat /sys/block/sda/queue/iosched/group_idle_us      # for cgroup

# NOOP (do nothing, just passes down the I/O that comes to it)
# recommended for setups with devices that do I/O scheduling themselves
# useful for devices that do not depend on mechanical movement, like SSDs

# DEADLINE
# it is latency-oriented I/O scheduler. Each I/O request is assigned a deadline
# in general, the algorithm prefers reads over writes
# params:
cat /sys/block/sda/queue/iosched/writes_starved     # controls how many reads can be sent to disk before it is possible to send writes
cat /sys/block/sda/queue/iosched/read_expire        # deadline for read operations in ms. The default is 500.
cat /sys/block/sda/queue/iosched/write_expire       # deadline for read operations in ms. The default is 500

# SSD
# consider switching to blk-mq for SCSI. This is done using the kernel command line option:
scsi_mod.use_blk_mq=1
