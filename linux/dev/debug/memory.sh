#!/bin/bash

getconf PAGE_SIZE

# display amount of free and used physical and swap memory in the system, as well as the buffers used by the kernel.
# The shared  memory column represents Shmem value taken from the /proc/meminfo file.
free                                                # display in KB
free -m                                             # display in MB
free -g                                             # display in GB
free -s 2                                           # show every 2s

cat /proc/meminfo
# MemTotal:        4030196 kB           total RAM
# MemFree:          442268 kB           unused RAM
# MemAvailable:    1677740 kB           available for starting new app without swapping
# Buffers:           73428 kB           file buffer cache in RAM contain file system metadata
# Cached:          1419148 kB           page cache in RAM, exclude buffer cache and swap cache
# SwapCached:          252 kB           Page cache for swapped-out memory
# Active:          2277136 kB           Recently used memory, = Active(anon) + Active(file)
# Inactive:        1033552 kB           Less recently used memory that will usually be reclaimed first
# Active(anon):    1681748 kB           swap backed memory. This includes private and shared anonymous mappings and private file pages after copy-on-write
# Inactive(anon):   231488 kB           swap backed memory. This includes private and shared anonymous mappings and private file pages after copy-on-write
# Active(file):     595388 kB           other file system backed memory
# Inactive(file):   802064 kB           other file system backed memory
# Unevictable:          32 kB           memory that cannot be reclaimed (for example, because it is Mlocked or used as a RAM disk)
# Mlocked:              32 kB           backed by the mlock system call
# SwapTotal:       2097148 kB           swap space
# SwapFree:        2096112 kB           unused swap space
# Dirty:                28 kB           memory waiting to be written to disk, controlled with the sysctl parameters vm.dirty_ratio or vm.dirty_bytes
# Writeback:             0 kB           memory that is currently being written to disk
# AnonPages:       1818004 kB
# Mapped:           661536 kB           Memory claimed with the mmap system call
# Shmem:            130080 kB           Memory shared between groups of processes, such as IPC data, tmpfs data, and shared anonymous memory
# KReclaimable:      86264 kB
# Slab:             170656 kB           Memory allocation for internal data structures of the kernel
# SReclaimable:      86264 kB           Slab section that can be reclaimed, such as caches (inode, dentry, etc.)
# SUnreclaim:        84392 kB           Slab section that cannot be reclaimed
# KernelStack:       12528 kB           kernel space memory used by applications (through system calls)
# PageTables:        26300 kB           memory dedicated to page tables of all processes
# NFS_Unstable:          0 kB           NFS pages that have already been sent to the server, but are not yet committed there
# Bounce:                0 kB           Memory used for bounce buers of block devices
# WritebackTmp:          0 kB           Memory used by FUSE for temporary writeback buers
# CommitLimit:     4112244 kB           memory available to the system based on the overcommit ratio setting
# Committed_AS:    6728680 kB           memory (RAM and swap) that the current work-load would need in the worst case
# VmallocTotal:   34359738367 kB        allocated kernel virtual address space
# VmallocUsed:       38276 kB           used kernel virtual address space
# VmallocChunk:          0 kB           The largest contiguous block of available kernel virtual address space
# Percpu:             2784 kB
# HardwareCorrupted:     0 kB           failed memory (can only be detected when using ECC RAM)
# AnonHugePages:         0 kB           Anonymous hugepages that are mapped into user space page tables
# ShmemHugePages:        0 kB           
# ShmemPmdMapped:        0 kB
# CmaTotal:              0 kB
# CmaFree:               0 kB
# HugePages_Total:       0              Number of preallocated hugepages for use by SHM_HUGETLB and MAP_HUGETLB or through the hugetlbfs file system, as defined in /proc/sys/vm/nr_hugepages
# HugePages_Free:        0              Number of hugepages available
# HugePages_Rsvd:        0              Number of hugepages that are committed
# HugePages_Surp:        0              Number of hugepages available beyond HugePages_Total (“surplus”)
# Hugepagesize:       2048 kB           Size of a hugepage
# Hugetlb:               0 kB
# DirectMap4k:      221120 kB           Amount of kernel memory that is mapped to pages with a given size
# DirectMap2M:     3973120 kB

# print process memory map
pmap pid
