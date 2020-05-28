grep ctxt /proc/$PID/status
pidstat -w 1
sar -w 1

# one context switch roughly cost 3-5us
# co-routine switch cost 120ns
# system call cost 200ns-15us
# network connect normaly cost 22us, when ip_local_port_range used up, then it cost 2.5ms, because it randomly pick a port to try
# function call cost 0.4ns
# soft interupt cost 3.4us