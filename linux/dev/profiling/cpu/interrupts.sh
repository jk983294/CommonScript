cat /proc/interrupts
# column meaning: 1、逻辑中断号，2、中断在各CPU发生的次数，3、中断所属设备类名称，4、硬件中断号，5、中断处理函数

# top hi/si, hardware interupt / soft interupt
# soft interupt happen, then switch to ksoftirqd
cat /proc/softirqs
cat /proc/interrupts                    # check interupt number
cat /proc/irq/19/smp_affinity
psg irqbalance                          # affinity managed by /usr/sbin/irqbalance