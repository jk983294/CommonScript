catchpoints: cause the debugger to stop for certain kinds of program events
throw                   C++抛出异常
catch                   C++捕捉到异常
exec                    exec被调用
fork                    fork被调用
vfork                   vfork被调用
load                    加载动态库
load libname            加载名为libname的动态库
unload                  卸载动态库
unload libname          卸载名为libname的动态库
syscall [args]          调用系统调用，args可以指定系统调用号，或者系统名称

(gdb) catch syscall mmap
(gdb) catch syscall 9

$ grep mmap /usr/share/gdb/syscalls/amd64-linux.xml
  <syscall name="mmap" number="9"/>

# catchpoint只触发一次
(gdb) tcatch fork                   # only break for first fork call

# 破解anti-debugging的程序
(gdb) catch syscall ptrace
(gdb) c
(gdb) set $rax = 0
(gdb) c
