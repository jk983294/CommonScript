# 调试子进程，gdb默认追踪父进程，设置下面后会去追踪fork出来的子进程
(gdb) set follow-fork-mode child
(gdb) start

# 同时调试父进程和子进程，这样gdb就能同时调试父子进程
(gdb) set detach-on-fork off
(gdb) set schedule-multiple on              # 父子进程都同时运行，不设置的话父进程先执行，此时子进程挂起直到父进程结束
(gdb) start
(gdb) i inferiors
(gdb) inferior 2                            # switch to child process

# 一个gdb会话中同时调试多个程序
$ gdb a.out
(gdb) start
(gdb) add-inferior -exec b.out              # 加载可执行文件b
(gdb) inferior 2
(gdb) start

# 调试已经运行的进程
$ gdb a.out processID
$ gdb a.out 10210
or
(gdb) attach 10210
(gdb) detach

# 程序正常退出的返回值
(gdb) p $_exitcode
