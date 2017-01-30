#!/usr/bin/env bash

# display amount of free and used physical and swap memory in the system, as well as the buffers used by the kernel.
# The shared  memory column represents Shmem value taken from the /proc/meminfo file.
free                                                # display in kilobytes
free -m                                             # display in megabytes

