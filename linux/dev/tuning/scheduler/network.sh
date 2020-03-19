# modify the size and behavior of kernel socket buffers
ls /proc/sys/net/core
ls /proc/sys/net/ipv4
cat /proc/sys/net/ipv4/tcp_moderate_rcvbuf      # autotuning is active and buffer size is adjusted dynamically
cat /proc/sys/net/ipv4/tcp_rmem                 # minimum, initial, and maximum size of the Memory Receive buffer per connection
cat /proc/sys/net/ipv4/tcp_wmem                 # same as tcp_rmem but Memory Send buffer per connection
cat /proc/sys/net/core/rmem_max                 # limit the maximum receive buffer size that applications can request
cat /proc/sys/net/core/wmem_max                 # limit the maximum send buffer size that applications can request
cat /proc/sys/net/ipv4/tcp_timestamps           # disable TCP features that you do not need
cat /proc/sys/net/ipv4/tcp_window_scaling       # disable TCP features that you do not need
cat /proc/sys/net/ipv4/tcp_sack                 # disable TCP features that you do not need

sysctl -a | grep tcp                            # relevant parameters