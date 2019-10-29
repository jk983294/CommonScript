sched_rt_runtime_us # 表示所有实时进程一次能占有CPU的最长时间，缺省是1秒，当这个时间被用完，他们必须等待下面参数
sched_rt_period_us # 表示的时间(缺省是0.95s)才能被重新调度
sched_rt_period_us # 表示下一次调度实时进程的时间

# 禁止带宽限制
echo -1 > /proc/sys/kernel/sched_rt_period_us
echo -1 > /proc/sys/kernel/sched_rt_runtime_us
