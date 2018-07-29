# 启动时不显示提示信息
gdb -q
alias gdb="gdb -q"

# gdb退出时不显示提示信息, add below to .gdbinit
(gdb) set confirm off

# 输出信息多时不会暂停输出
(gdb) set pagination off
(gdb) set height 0

# 列出函数的名字
(gdb) info functions
(gdb) info functions thread_*
