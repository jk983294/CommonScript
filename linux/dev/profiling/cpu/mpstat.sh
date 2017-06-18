#!/bin/bash

# report processors related statistics
# CPU               processor number
# %usr              the percentage of CPU utilization while executing at the user level
# %nice             the percentage of CPU utilization while executing at the user level with nice priority.
# %sys              the percentage of CPU utilization while executing at the system level
# %iowait           the percentage of idle time that system had an outstanding disk I/O request.
# %idle             the percentage of idle time that system did not have an outstanding disk I/O request.
# %irq              the percentage of time spent by hardware interrupts.
# %soft             the percentage of time spent by software interrupts.
# %steal            the percentage of time spent in involuntary wait by the virtual CPU while the hypervisor was servicing another virtual processor.
# %guest            the percentage of time spent by the CPU to run a virtual processor.
# %gnice            the percentage of time spent by the CPU to run a niced guest

mpstat 5                    # sampling every 5 second
