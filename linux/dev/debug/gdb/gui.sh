# 进入和退出
$ gdb -tui program
(gdb) Crtl + X + A 组合键                              # access and quit

# 显示汇编代码窗口
(gdb) layout asm

# 既显示源代码，又显示汇编代码
(gdb) layout split

# 显示寄存器窗口
(gdb) layout regs
(gdb) tui reg general
(gdb) tui reg float
(gdb) tui reg system

# 调整窗口大小
# winheight <win_name> [+ | -] <#lines>
(gdb) winheight src -5
(gdb) winheight src +5
