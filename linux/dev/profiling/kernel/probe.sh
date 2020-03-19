# Kprobes, attached to any instruction in the Linux kernel
# Jprobes, inserted on a function's entry point
# Kretprobes, only call return handler

less /sys/kernel/debug/kprobes/list                 # list of all currently registered probes

# turn on or off all the registered kernel probes
echo "0" > /sys/kernel/debug/kprobes/enabled
echo "1" > /sys/kernel/debug/kprobes/enabled
cat /sys/kernel/debug/kprobes/enabled