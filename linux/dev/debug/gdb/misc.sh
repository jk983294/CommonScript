# 设置被调试程序的参数
$ gdb -args ./a.out a b c
(gdb) set args a b c
(gdb) show args
(gdb) run a b c

# 设置被调试程序的环境变量
(gdb) set env LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0

# help
(gdb) help
(gdb) help data                             # 得到这个类别下所有命令的列表和命令功能
(gdb) help mem                              # 某一个具体命令的用法
(gdb) apropos regex                         # 查找所有符合正则表达式的命令信息

# 在gdb中执行shell命令和make
(gdb) shell ls
or
(gdb) !ls
(gdb) make CFLAGS="-g -O0"

# 支持预处理器宏信息
#define NAME "Joe"
# 使用gcc -g3进行编译
(gdb) p NAME

# 直接按回车键，会重复执行上一次的命令

# 记录执行gdb的过程
# 方便以后自己参考或是别人帮忙分析
(gdb) set logging file log.txt
(gdb) set logging on
$ cat log.txt

# 设置源文件查找路径
# gdb有时不能准确地定位到源文件的位置（比如文件被移走了）
(gdb) directory /new/source/path/
(gdb) set substitute-path /home/old /home/new
or
$ gdb a.out -d /new/source/path/

# 命令的缩写形式
b -> break
c -> continue
d -> delete
f -> frame
i -> info
j -> jump
l -> list
n -> next
p -> print
r -> run
s -> step
u -> until
aw -> awatch
bt -> backtrace
dir -> directory
disas -> disassemble
fin -> finish
ig -> ignore
ni -> nexti
rw -> rwatch
si -> stepi
tb -> tbreak
wa -> watch
win -> winheight
