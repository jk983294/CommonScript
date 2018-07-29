# 在匿名空间设置断点
# 对namespace Foo中的foo函数设置断点
(gdb) b Foo::foo
# 对匿名空间中的bar函数设置断点
(gdb) b (anonymous namespace)::bar

# 在程序地址上打断点, 当调试汇编程序，或者没有调试信息的程序时，经常有此需求
(gdb) b *0x400522

# 在程序入口处打断点
# 方法一
$ readelf -h a.out | grep Entry
(gdb) b *entry
(gdb) r
# 方法二
(gdb) info files             # get Entry point
(gdb) b *entry
(gdb) r

# 在文件行号上打断点
# gdb会对所有匹配的文件设置断点
(gdb) b file.cpp:6

# 保存已经设置的断点
(gdb) save breakpoints breakpoint.file
(gdb) source breakpoint.file
(gdb) info breakpoints

# 临时断点, 让断点只生效一次
(gdb) tb main.cpp:15

# 条件断点
# 比如循环中，只想check第101次循环
(gdb) b 10 if i==101

# 忽略断点
# 比如循环中，只想check第101次循环
# ignore bnum count 意思是忽略接下来count次编号为bnum的断点，只在第count + 1次断点触发
(gdb) b 10
(gdb) ignore 1 100
