#!/bin/bash

gcc -g -O0 thread.c -l pthread
gdb ./a.out
gdb --args executable arg1 arg2
gdb badprog core                            # postmortem analysis, check core dump
gdb badprog pid                             # attach to process which binary code is badprog and id is pid

# 程序运行控制
file ./a.out                                # 加载被调试的可执行程序文件
run/r
run argument1 argument2                     # run program with arguments
attach pid
detach
continue/c
step/s                                      # 进入的单步执行, Step Into
next/n                                      # 不进入的单步执行, Step Over
si                                          # assembly level step
ni                                          # assembly level next
until/u                                     # 在一个循环体内单步跟踪时，这个命令可以运行程序直到退出循环体
finish                                      # 退出该函数返回到它的调用函数中,显示其返回值(if has return value)
return
return expression                           # 强制函数忽略还没有执行的语句并返回
quit/q

# 断点
break/b filename:line-number                # for multiply source files
break/b filename:function-name
b class::function
b namespace::class::function
b class::function(type,type)
b namespace::class::function(type,type)
break/b 13                                  # add breakpoint at line 13
break/b function_name                       # add breakpoint at function function_name
break/b line-or-function if condition       # 如果condition（条件）是真，程序到达指定行或函数时停止。
break/b 46 if size==100
b test.c:8 if intValue == 5
break/b *function1                          # 断点设置在由编译器生成的prolog代码处
condition bnum expression                   # 修改断点号为bnum的停止条件为expression
condition bnum                              # clear断点号为bnum的停止条件
ignore bnum count                           # 忽略断点号为bnum的停止条件count次
watch fd                                    # break when the value of variable changes
rwatch                                      # expr/variable被读时，停住程序
awatch                                      # expr/variable的值被读或被写时，停住程序
clear                                       # 清除所有的已定义的停止点
clear function                              # 清除所有设置在函数上的停止点
clear linenum                               # 清除所有设置在指定行上的停止点
clear filename:linenum                      # 清除所有设置在指定文件：指定行上的停止点
delete/d breakpoint 1                       # 删除编号为1的断点
delete/d breakpoint                         # 删除所有的断点
disable breakpoint 1                        # 禁止断点1
enable breakpoint 1                         # 允许断点1

# 查看
x /s ptr                                    # show char* ptr content
p /s ptr                                    # show char* ptr content
print/p fd                                  # show variable data
print/p *array@10                           # show array's 10 data
print/p strlen(data)                        # evaluation expression
print/p f1(arg1 ...)                        # evaluation expression
print/p file::variable
print/p function::variable
call expr
list                                        # show next 10 lines
list 1,5                                    # show line 1 to 5
list +                                      # 列出当前行的后面代码行
list -                                      # 列出当前行的前面代码行
list function
show listsize                               # 显示打印代码的行数
show args
whatis fd                                   # check variable type at breakpoint
ptype class                                 # 比whatis的功能更强，提供一个结构的定义
display fd                                  # show variable data, it will automatically show display list
display /i $pc                              # 即将被执行的下一条汇编指令, $pc 代表当前汇编指令，/i 表示以十六进行显示
undisplay 编号
where                                       # get stack trace
backtrace/bt                                # 列表包含着从最近的过程开始的所有有效过程和调用这些过程的参数
bt n/-n
frame n
frame addr
up n                                        # 向栈的上面移动n层，可以不打n，表示向上移动一层
down n                                      # 向栈的下面移动n层，可以不打n，表示向下移动一层
info/i f/frame
info/i locals                               # check local variables
info/i args                                 # check arguments
info/i r                                    # check registers
info/i b/break/breakpoints                  # check breakpoints
info/i watchpoints
info program                                # 来查看程序的是否在运行，进程号，被暂停的原因。
info/i threads

# 设置数据
set fd=1                                    # change data
set var width=47                            # width是内置变量，用var来告诉gdb去修改width的值
print x=4
set args –b –x
set listsize count                          # 设置显示代码的行数
signal signal

# debug multithreading
info/i threads
thread 5                                    # switch to thread 5
break line thread threadno
break frik.c:13 thread 28 if a > 3
thread apply all bt

# debug multiple programs in a single session
# the state of each program execution is called an inferior
info inferiors
inferior infno                              # switch to inferior infno
add-inferior [ -copies n ] [ -exec executable ]
clone-inferior [ -copies n ] [ infno ]
remove-inferiors infno
detach inferior infno
kill inferiors infno
set print inferior-events
set print inferior-events on
set print inferior-events off
show print inferior-events
maint info program-spaces
example:
    sleep 1d &
    sleep 2d &
    gdb -q
    attach 2917
    add-inferior
    inferior 2
    attach 2918
    i inferiors
