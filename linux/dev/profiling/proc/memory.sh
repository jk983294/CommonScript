# print process memory map
pmap pid

# print memory stats for pid, it is expensive to read. so not recommended to monitor it regularly
cat /proc/pid/smaps

cat /proc/self/maps             # address assignment of executables and libraries