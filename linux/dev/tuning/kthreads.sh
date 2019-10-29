# refer: https://www.kernel.org/doc/Documentation/kernel-per-CPU-kthreads.txt

# ehca_comp/%u kthread

# irq/%d-%s kthread
echo f > /proc/irq/44/smp_affinity

# kcmtpd_ctr_%d Handle Bluetooth work

# ksoftirqd/%u
## TIMER_SOFTIRQ, cpu isolate, Build with CONFIG_HOTPLUG_CPU=y, After boot completes, force the CPU offline, then bring it back online to recurring timers to migrate elsewhere
## NET_TX_SOFTIRQ and NET_RX_SOFTIRQ, Force networking interrupts onto other CPU, Initiate any network I/O on other CPU
## BLOCK_SOFTIRQ, Force block-device interrupts onto other CPU, Initiate any block I/O on other CPU
## IRQ_POLL_SOFTIRQ, Force block-device interrupts onto other CPU, Initiate any block I/O and block-I/O polling on other CPU
## TASKLET_SOFTIRQ, Avoid use of drivers that use tasklets, Convert all drivers from tasklets to workqueues, Force interrupts for drivers using tasklets onto other CPU
## SCHED_SOFTIRQ, Avoid sending scheduler IPIs to the CPU, use nohz_full, cpu isolate
## HRTIMER_SOFTIRQ, cpu isolate, CONFIG_HOTPLUG_CPU=y, Once boot completes, force the CPU offline, then bring it back online
## RCU_SOFTIRQ, use nohz_full to offload callbacks

# kworker/%u:%d%s (cpu, id, priority)
## Run your workload at a real-time priority

# rcuc/%u
## Build the kernel with CONFIG_PREEMPT=n
## Build the kernel with CONFIG_RCU_BOOST=n
## Build with CONFIG_RCU_NOCB_CPU=y, use rcu_nocbs

# rcuop/%d and rcuos/%d
## Use affinity, cgroups to force these kthreads to execute on some other CPU
## Build with CONFIG_RCU_NOCB_CPU=n, shift it to RCU_SOFTIRQ

# watchdog/%u
## Build with CONFIG_LOCKUP_DETECTOR=n
## Boot with "nosoftlockup=0"
echo 0 > /proc/sys/kernel/watchdog
echo 10 > /proc/sys/kernel/watchdog_thresh
