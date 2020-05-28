## Memory
```sh
dmidecode | grep -P -A16 "Memory"
# Speed: 1067MHz
# Data Width: 64 bits
# core frequency: 133MHz - 200MHz, other frequency driven by it, amplify it
```


# 内存条参数
* CL(CAS Latency) 发送一个列地址到内存与数据开始响应之间的周期数
* tRCD(RAS-to-CAS Delay) 打开一行内存并访问其中的列所需的最小时钟周期数
* tRP(RAS Precharge Time) 发出预充电命令与打开下一行之间所需的最小时钟周期数
* tRAS(RAS Active Time) 行活动命令与发出预充电命令之间所需的最小时钟周期数。也就是对下一次预充电时间进行限制

CPU向内存控制器发出请求，内存控制器进行行地址的预充电，需要等待 tRP 个时钟周期。再发出打开一行内存的命令，又需要等待 tRCD 个时钟周期。接着发送列地址，再等待 CL 个周期

现代的内存都是一个时钟周期上下沿分别各传输一次数据，所以用Speed/2就可以得出，例如机器的Speed是1066MHz，则时钟周期为533MHz

# 内存随机访问
内存存在随机访问比顺序访问慢的多，大概是4:1的关系

随机IO比顺序IO要慢。如果行地址同上一次访问的不一致，则需要重新拷贝row buffer，延迟周期需要tRP+tRCD+CL。而如果是顺序IO的话（行地址不变），只需要CL个周期既可完成
* 随机IO：这种状况下需要tRP+tRCD+CL个时钟周期，7+7+7=21个周期。但是还有个tRAS的限制，两次行地址预充电不得小于24。所以我们得按24来计算，24*(1s/533Mhz) = 45ns, number does not consider cache
* 顺序IO：这种状况下只需要CL个时钟周期 7*(1s/533Mhz)=13ns

### add cache effect
* 数组足够小的时候，L1 cache全部都能装的下。内存IO发生较少，大部分都是高效的缓存IO，内存延时 1ns左右
* 访问地址连续，所以即使发生内存IO也绝大部分都是行地址不变的顺序IO情况。耗时在 9ns 左右
* 随机实验场景, 在64M的数据集中，内存的延时下降到了38.4ns

# 内存带宽
理论内存带宽的计算公式是：Band Width = Speed * Data Width, 厂家这个数据的基础是内存严格以顺序IO的方式工作，而且把传输的内存地址也当数据来看，进而计算出的结果

带宽就是一秒内访问过的字节总数
* 数组为2k，足够小到L1 cache全部都能装的下。这时候最高值也才6G而已，没有达到厂家宣称的8GB
* 步长增加后，穿透到内存的次数进一步增加，带宽进一步下降。这个时候，应用程序视角看到的数据带宽已经下降到1GB以下
* 随机IO情况，内存带宽竟然下降到了474M, 现在SSD固态硬盘顺序IO情况下也差不多能达到这个数量级

# NUMA

### NUMA架构下的内存访问延迟区别
历史上, CPU通过FSB总线(Front Side Bus，前端总线)连接到北桥芯片，然后再连接到内存。内存控制器是集成在北桥里的，Cpu和内存之间的通信全部都要通过这一条FSB总线来进行

CPU制造商们把内存控制器从北桥搬到了CPU内部，这样CPU便可以直接和自己的内存进行通信了。那么，如果CPU想要访问不和自己直连的内存条, via新的总线(QPI总线)

CPU的设计者们引入了QPI总线，相应的CPU的结构就叫NMUA架构

```sh
dmidecode|grep -P -A5 "Memory\s+Device"| grep Size
numactl --hardware
# node distance是一个二维矩阵，描述node访问所有内存条的延时情况
```

在NUMA架构下，CPU访问自己同一个node里的内存要比其它内存要快, 拿8M数组，循环步长为64的case来说，同node耗时3.15纳秒，跨node为3.96纳秒

```sh
numactl --cpubind=0 --membind=0 ./main          # 让内存和CPU处于同一个node
numactl --cpubind=0 --membind=1 ./main          # 让内存和CPU处于不同node
```

### numa陷阱
单实例内存最大申请到多大比较合适？

单进程分配的内存最好不要超过一个node里的内存总量，否则linux当该node里的内存分配光了的时候，会在自己node里动用硬盘swap，而不是其它node里申请

NUMA为了高效，会仅仅只从你的当前node里分配内存，只要当前node里用光了（即使其它node还有），也仍然会启用硬盘swap

zone_reclaim_mode用来管理当一个内存区域(zone)内部的内存耗尽时，是从其内部进行内存回收还是可以从其他zone进行回收的选项：
* 0 关闭zone_reclaim模式，可以从其他zone或NUMA节点回收内存
* 1 打开zone_reclaim模式，这样内存回收只会发生在本地节点内
* 2 在本地回收内存时，可以将cache中的脏数据写回硬盘，以回收内存
* 4 在本地回收内存时，表示可以用Swap 方式回收内存
```sh
cat /proc/sys/vm/zone_reclaim_mode
cat /proc/zoneinfo
```

如果不绑定亲和性的话，分配内存是当进程在哪个node上的CPU发起内存申请，就优先在哪个node里分配内存。之所以是平均分配在两个node里，是因为进程经常会进入主动睡眠状态，醒来后可能CPU就换了
```sh
numactl --cpunodebind=0 --membind=0 ./test_program   # 绑定亲和性 trap into naum trap
```


# 优化思路精髓
从72字节优化到了56字节，这内存节约的也不是特别多嘛，才20%多而已, 以Cache Line为单位, 在计算机里，56字节相对72字节实际上是翻倍的性能提升！！

Cache容量不变的条件下，能Cache住的memory将会翻倍，缓存命中率提升一大截

