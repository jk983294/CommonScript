# 查看信号处理信息
# Stop：表示被调试的程序有对应的信号发生时，gdb是否会暂停程序
# Print：表示被调试的程序有对应的信号发生时，gdb是否会打印相关信息
# Pass to program：gdb是否会把这个信号发给被调试的程序
(gdb) i signals

# 信号发生时是否暂停程序
(gdb) handle SIGHUP nostop                          # SIGHUP信号发生时，gdb不暂停程序
(gdb) handle SIGHUP stop                            # SIGHUP信号发生时，gdb暂停程序

# 信号发生时是否打印信号信息
(gdb) handle SIGHUP noprint
(gdb) handle SIGHUP print

# 信号发生时是否把信号丢给程序处理
(gdb) handle SIGHUP nopass                          # SIGHUP信号发生时，gdb不把信号丢给程序处理
(gdb) handle SIGHUP pass

# 给程序发送信号
# kill命令给程序发送信号，gdb会根据当前的设置决定是否把信号发送给进程，而使用signal命令则直接把信号发给进程
# signal signal_name 程序会先continue，然后立即给程序发送信号
(gdb) signal SIGHUP
(gdb) signal 0
