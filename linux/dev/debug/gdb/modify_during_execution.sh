# 改变字符串的值
// char p1[] = "Sam";
// char *p2 = "Bob";
(gdb) set main::p1="Kun"
(gdb) set main::p2="Jiang"
or
(gdb) p &p1                                             # get address of p1 0x80477a4
(gdb) set {char [4]} 0x80477a4 = "Kun"

# 设置变量的值
// int i = 2;
(gdb) set var i = 8
or
(gdb) p &i
(gdb) set {int}0x8047a54 = 8

# 修改寄存器的值
(gdb) set var $eax = 8

# 修改PC寄存器的值，可以达到改变程序执行流程的目的
(gdb) info line 6
(gdb) p $pc
(gdb) set var $pc=0x08050949

# 当程序运行到断点处，会自动把变量n的值修改为0，然后继续执行
# 用这种方式在gdb中先实验性的修改下试试，而不需要修改源码，重新编译
(gdb) b func1               # suppose the breakpoint number is 1
(gdb) command 1             # add command for breakpoint 1
>silent
>set variable n = 0
>continue
>end
(gdb) r
