echo f > /proc/irq/default_smp_affinity # 默认情况下未激活的IRQ的中断亲和掩码, 默认设置是0xffffffff
echo f > /proc/irq/44/smp_affinity # 把44号中断绑定到前4个CPU(CPU0-3)上面
echo 0-3 > /proc/irq/44/smp_affinity_list # 把44号中断绑定到前4个CPU(CPU0-3)上面

for irq in `ls /proc/irq/`; do echo 1 > /proc/irq/$irq/smp_affinity; done
for irq in `ls /proc/irq/`; do echo -n "$irq  ";  cat /proc/irq/$irq/smp_affinity_list; done
