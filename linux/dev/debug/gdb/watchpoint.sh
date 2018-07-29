# 观察点, 当一个变量值发生变化时，程序会停下来
# int a = 0;    // watch this variable
(gdb) watch a
or
(gdb) p &a                              # get address say $1 = (int *) 0x6009c8 <a>
(gdb) watch *(int*)0x6009c8
(gdb) info watchpoints

# 观察点只针对特定线程生效
(gdb) i threads
(gdb) watch a thread 2                  # only watch thread #2 caused variable a change

# 读观察点, 当发生读取变量行为时，程序就会暂停住
(gdb) rw a
(gdb) c

# 读写观察点, 当发生读取变量或改变变量值的行为时，程序就会暂停住
(gdb) aw a
(gdb) c
