# rps-Receive Package Steering, 根据报文的hash值从分发处理报文的cpu列表中选取一个目标cpu
# xps-Transmit Packet Steering
# rfs-Receive Flow Steering, 指派处理报文的应用程序所在的cpu来在内核态处理报文，以此来增加cpu的缓存命中率
# 在软件层面实现报文在多个cpu之间的负载均衡以及提高报文处理的缓存命中率

echo f > /sys/class/net/em1/queues/rx-0/rps_cpus # 0-3 core 参与到网卡的分发处理
echo f > /sys/class/net/em1/queues/tx-0/xps_cpus # 0-3 core 参与到网卡的分发处理
