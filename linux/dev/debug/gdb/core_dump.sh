# 为调试进程产生core dump文件, 记录现在进程的状态，以供以后分析
(gdb) generate-core-file my.core.file
or
(gdb) gcore my.core.file

# 加载可执行程序和core dump文件
$ gdb executable coredump.file
or
(gdb) file executable
(gdb) core coredump.file
