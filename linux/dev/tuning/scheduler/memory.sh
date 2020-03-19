# VM (virtual memory manager)
# Tunable Parameter:
cat /proc/sys/vm/swappiness                 # how aggressively kernel swaps out anonymous memory relative to pagecache and other caches
cat /proc/sys/vm/vfs_cache_pressure         # tendency of kernel to reclaim the VFS cache memory
cat /proc/sys/vm/min_free_kbytes            # memory is kept free for use by special reserves including “atomic” allocations
cat /proc/sys/vm/watermark_scale_factor     # When the watermark reached then system reclaim memory in the background

# writeback behavior to file-backed mmap() memory
cat /proc/sys/vm/dirty_background_ratio     # dirty pagecache exceeds this percentage, writeback threads start working
cat /proc/sys/vm/dirty_background_bytes     # dirty pagecache exceeds this amount, writeback threads start working
cat /proc/sys/vm/dirty_ratio                # When exceeded, apps that want to write to the pagecache are blocked and wait for kernel flusher threads to reduce the amount of dirty memory
cat /proc/sys/vm/dirty_bytes                # same as dirty_ratio but from byte perspective
cat /proc/sys/vm/dirty_expire_centisecs     # dirty memory exceed this interval will be written out next time a flusher thread wakes up

# Readahead Parameters
cat /sys/block/sda/queue/read_ahead_kb      # maximum amount of data that the kernel reads ahead for a single file

# Transparent Huge Page (THP) Parameters
cat /sys/kernel/mm/transparent_hugepage/enabled     # If disabled, the value never is shown in square brackets
cat /sys/kernel/mm/transparent_hugepage/defrag      # how much effort an application commits when allocating a THP

# khugepaged Parameters
cat /sys/kernel/mm/transparent_hugepage/khugepaged/defrag                   # 0 will disable khugepaged even though THP may still be used at fault time
cat /sys/kernel/mm/transparent_hugepage/khugepaged/pages_to_scan            # how many pages are scanned by khugepaged in a single pass
cat /sys/kernel/mm/transparent_hugepage/khugepaged/scan_sleep_millisecs     # khugepaged sleeps for a short interval specified by this parameter after each pass
cat /sys/kernel/mm/transparent_hugepage/khugepaged/alloc_sleep_millisecs    # controls how long khugepaged will sleep in the event it fails to allocate a THP in the background
