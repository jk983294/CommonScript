# 只允许一个线程运行
# gdb调试多线程程序时,一旦程序断住,所有的线程都处于暂停状态.当调试其中一个线程时(step/next),所有的线程都会同时执行
(gdb) set scheduler-locking on

# 查看线程信息
(gdb) i threads
(gdb) i threads 1 2                         # 只打印线程1,2的信息，适用于线程太多看不过来的情况

# 打印所有线程的堆栈信息
(gdb) thread apply all bt
(gdb) thread apply 1-2 bt
