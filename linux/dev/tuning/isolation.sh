# grub boot config
isolcpus=4,6,8,10 # isolate a given set of CPUs from disturbance
rcu_nocbs=4,6,8,10 # remove one or more CPUs from the candidates for running RCU callbacks
nohz_full=4,6,8,10 # the specified list of CPUs whose tick will be stopped whenever possible
