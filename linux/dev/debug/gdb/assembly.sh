si                                                  # assembly level step
ni                                                  # assembly level next
x/20i 0x00007ffe4ccd5f96                            # show next 20 instructions from address 0x00007ffe4ccd5f96

# 把断点设置在汇编指令层次函数的开头
(gdb) b *main
(gdb) b *func

# 自动反汇编后面要执行的代码
(gdb) set disassemble-next-line on                  # 在任意情况下反汇编后面要执行的代码
(gdb) set disassemble-next-line auto                # 在后面的代码没有源码的情况下才反汇编后面要执行的代码
(gdb) set disassemble-next-line off                 # 关闭反汇编功能

# 将源程序和汇编指令映射起来
(gdb) disas /m main                                 # main每一条语句对应的汇编代码
(gdb) i line 13                                     # 某一行所对应的地址范围
(gdb) disassemble 0x4004e9, 0x40050c                # 查看这一条语句对应的汇编代码

# 显示将要执行的汇编指令
(gdb) display /5i $pc
(gdb) undisplay

# 打印寄存器的值
(gdb) i registers
(gdb) i all-registers
(gdb) i registers eax
(gdb) p $eax

# 设置汇编指令格式
# x86处理器上，gdb默认显示汇编指令格式是AT&T格式
(gdb) disassemble main
(gdb) set disassembly-flavor intel          # 格式改为intel格式
(gdb) disassemble main

# 显示程序机器码
(gdb) disassemble /r main
