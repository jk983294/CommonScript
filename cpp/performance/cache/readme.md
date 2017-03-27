### Latency

| location    | cycle  |
| --------    | :----: |
| L1          |   4    |
| L2          |   11   |
| L3          |   39   |
| main memory |   107  |

### false sharing

if data lay out in the same cache line, and different threads operate
on some portion of that cache line, then thread will mark dirty for that cache line
across all cache system, namely from L1 to L3 cache.

but actually those data can be paralleled since they only use their own piece of data.

so use local data in thread, then set global data once.

compiler can cause false sharing issue too, suppose compiler compact all static global data into the same place,
it is very likely those data can fit into one cache line which hamper the concurrency.

### best practice for Data

where practical, employ linear array traversals

use as much of a cache line as possible

### best practice for Instruction

fit working set in cache

make "fast paths" branch-free sequence

inline cautiously: code duplication reduces effective cache size

### cache associativity
cache line can go to any one of N places in the cache(N-way set associative)
so when traversal data, don't choose pow(2, n) as step

### data oriented programming

don't over generalize, Node represent too many things, too many fields sit inside Node. so less Node objects can fit into one cache line

class bool fields give very low information density, compact it / padding it

### Optimization

Profile Guided Optimization(PGO)

Whole Program Optimization(WPO)

### further information
what every programmer should know about memory

CPU cache, wikipedia
