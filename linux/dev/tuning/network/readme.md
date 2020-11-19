### 中断处理
Linux中断处理函数是分上半部和下半部的。上半部是只进行最简单的工作，快速处理然后释放CPU。剩下将绝大部分的工作都放到下半部中，可以慢慢从容处理。内核采用的下半部实现方式是软中断，由ksoftirqd内核线程全权处理。硬中断是通过给CPU物理引脚施加电压变化，而软中断是通过给内存中的一个变量的二进制值以通知软中断处理程序。

只要硬中断在哪个CPU上被响应，那么软中断也是在这个CPU上处理的。所以说，如果你发现你的Linux软中断CPU消耗都集中在一个核上的话，做法是要把调整硬中断的CPU亲和性，来将硬中断打散到不通的CPU核上去。

### 处理
当网卡上收到数据以后，Linux中第一个工作的模块是网络驱动。 网络驱动会以DMA的方式把网卡上收到的帧写到内存里。再向CPU发起一个中断，以通知CPU有数据到达。第二，当CPU收到中断请求后，会去调用网络驱动注册的中断处理函数。 网卡的中断处理函数并不做过多工作，发出软中断请求，然后尽快释放CPU。ksoftirqd检测到有软中断请求到达，调用poll开始轮询收包，收到后交由各级协议栈处理。对于UDP包来说，会被放到用户socket的接收队列中。

### ksoftirqd内核线程
该进程数量不是1个，而是N个，其中N等于你的机器的核数。
当ksoftirqd被创建出来以后，它就会进入自己的线程循环函数ksoftirqd_should_run和run_ksoftirqd了。不停地判断有没有软中断需要被处理。

### 协议栈注册
fs_initcall调用inet_init后开始网络协议栈注册。 通过inet_init，将这些函数注册到了inet_protos和ptype_base数据结构中了。
inet_add_protocol函数将tcp和udp对应的处理函数都注册到了inet_protos数组中了。
ip_rcv中会处理netfilter和iptable过滤，如果你有很多或者很复杂的 netfilter 或 iptables 规则，这些规则都是在软中断的上下文中执行的，会加大网络延迟

### 网卡驱动初始化
每一个驱动程序会使用 module_init 向内核注册一个初始化函数，当驱动被加载时，内核会调用这个函数。
驱动的pci_register_driver调用完成后，Linux内核就知道了该驱动的相关信息。
当网卡设备被识别以后，内核会调用其驱动的probe方法。驱动probe方法执行的目的就是让设备ready。
网卡驱动实现了ethtool所需要的接口，也在这里注册完成函数地址的注册。ethtool这个命令之所以能查看网卡收发包统计、能修改网卡自适应模式、能调整RX 队列的数量和大小，是因为ethtool命令最终调用到了网卡驱动的相应方法，而不是ethtool本身有这个超能力。

### 启动网卡
当启用一个网卡时（例如，通过 ifconfig eth0 up），net_device_ops 中的 igb_open方法会被调用。
__igb_open函数在igb_setup_all_rx_resources这一步操作中，分配了RingBuffer，并建立内存和Rx队列的映射关系。
中断函数注册igb_request_irq
对于多队列的网卡，为每一个队列都注册了中断，其对应的中断处理函数是igb_msix_ring

### 硬中断处理
当数据帧从网线到达网卡上的时候，第一站是网卡的接收队列。网卡在分配给自己的RingBuffer中寻找可用的内存位置，找到后DMA引擎会把数据DMA到网卡之前关联的内存里，这个时候CPU都是无感的。当DMA操作完成以后，网卡会像CPU发起一个硬中断，通知CPU有数据到达。

### 网络协议栈处理
在netif_receive_skb中，数据包将被送到协议栈中。
netif_receive_skb函数会根据包的协议，假如是udp包，会将包依次送到ip_rcv(),udp_rcv()协议处理函数中进行处理。
在__netif_receive_skb_core中，经常使用的tcpdump的抓包点。

### 软中断budget调整
```sh
# sysctl -a | grep netdev_budget
# sysctl -w net.core.netdev_budget=600
```

