# 进入不带调试信息的函数, 默认情况下, gdb不会进入不带调试信息的函数, 接下来可以使用调试汇编程序的办法去调试函数si/ni
(gdb) set step-mode on
(gdb) s

# 退出正在调试的函数
# finish命令，函数会继续执行完，并且打印返回值，然后等待输入接下来的命令
(gdb) finish

# return命令，函数不会继续执行下面的语句，而是直接返回
# return expression 命令指定函数的返回值
(gdb) return
(gdb) return 42

# 直接执行函数
# call func()
# print func()

# 打印函数堆栈帧信息
(gdb) i frame
(gdb) i registers
(gdb) disassemble func
(gdb) disassemble MyClass::func

# 选择函数堆栈帧
(gdb) bt
(gdb) frame 2
or
(gdb) bt
(gdb) i frame               # check caller frame at 0x7fffffffe160
(gdb) frame 0x7fffffffe160

# 向上或向下切换函数堆栈帧
(gdb) bt
(gdb) up 1
(gdb) down 2
