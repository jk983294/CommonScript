# GDB
gcc -g -O0 thread.c -l pthread
gdb ./a.out
gdb badprog core                            # postmortem analysis, check core dump
gdb badprog pid                             # attach to process which binary code is badprog and id is pid

# �������п���
file ./a.out                                # ���ر����ԵĿ�ִ�г����ļ�
run/r
run argument1 argument2                     # run program with arguments
attach pid
detach
continue/c
step/s                                      # ����ĵ���ִ��, Step Into
next/n                                      # ������ĵ���ִ��, Step Over
si                                          # assembly level step
ni                                          # assembly level next
until/u                                     # ��һ��ѭ�����ڵ�������ʱ���������������г���ֱ���˳�ѭ����
finish                                      # �˳��ú������ص����ĵ��ú�����,��ʾ�䷵��ֵ(if has return value)
return
return expression                           # ǿ�ƺ������Ի�û��ִ�е���䲢����
quit/q

# �ϵ�
break/b filename:line-number                # for multiply source files
break/b filename:function-name
b class::function
b namespace::class::function
b class::function(type,type)
b namespace::class::function(type,type)
break/b 13                                  # add breakpoint at line 13
break/b function_name                       # add breakpoint at function function_name
break/b line-or-function if condition       # ���condition�����������棬���򵽴�ָ���л���ʱֹͣ��
break/b 46 if size==100
b test.c:8 if intValue == 5
break/b *function1                          # �ϵ��������ɱ��������ɵ�prolog���봦
condition bnum expression                   # �޸Ķϵ��Ϊbnum��ֹͣ����Ϊexpression
condition bnum                              # clear�ϵ��Ϊbnum��ֹͣ����
ignore bnum count                           # ���Զϵ��Ϊbnum��ֹͣ����count��
watch fd                                    # break when the value of variable changes
rwatch                                      # expr/variable����ʱ��ͣס����
awatch                                      # expr/variable��ֵ������дʱ��ͣס����
clear                                       # ������е��Ѷ����ֹͣ��
clear function                              # ������������ں����ϵ�ֹͣ��
clear linenum                               # �������������ָ�����ϵ�ֹͣ��
clear filename:linenum                      # �������������ָ���ļ���ָ�����ϵ�ֹͣ��
delete/d breakpoint 1                       # ɾ�����Ϊ1�Ķϵ�
delete/d breakpoint                         # ɾ�����еĶϵ�
disable breakpoint 1                        # ��ֹ�ϵ�1
enable breakpoint 1                         # ����ϵ�1

# �鿴
print/p fd                                  # show variable data
print/p *array@10                           # show array's 10 data
print/p strlen(data)                        # evaluation expression
print/p f1(arg1 ...)                        # evaluation expression
print/p file::variable
print/p function::variable
call expr
list                                        # show next 10 lines
list 1,5                                    # show line 1 to 5
list +                                      # �г���ǰ�еĺ��������
list -                                      # �г���ǰ�е�ǰ�������
list function
show listsize                               # ��ʾ��ӡ���������
show args
whatis fd                                   # check variable type at breakpoint
ptype class                                 # ��whatis�Ĺ��ܸ�ǿ���ṩһ���ṹ�Ķ���
display fd                                  # show variable data, it will automatically show display list
display /i $pc                              # ������ִ�е���һ�����ָ��, $pc ����ǰ���ָ�/i ��ʾ��ʮ��������ʾ
undisplay ���
where                                       # get stack trace
backtrace/bt                                # �б�����Ŵ�����Ĺ��̿�ʼ��������Ч���̺͵�����Щ���̵Ĳ���
bt n/-n
frame n
frame addr
up n                                        # ��ջ�������ƶ�n�㣬���Բ���n����ʾ�����ƶ�һ��
down n                                      # ��ջ�������ƶ�n�㣬���Բ���n����ʾ�����ƶ�һ��
info/i f/frame
info/i locals                               # check local variables
info/i args                                 # check arguments
info/i r                                    # check registers
info/i b/break/breakpoints                  # check breakpoints
info/i watchpoints
info program                                # ���鿴������Ƿ������У����̺ţ�����ͣ��ԭ��
info/i threads

# ��������
set fd=1                                    # change data
set var width=47                            # width�����ñ�������var������gdbȥ�޸�width��ֵ
print x=4
set args �Cb �Cx
set listsize count                          # ������ʾ���������
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










# trace system call and signal
strace ./a.out
strace cat /dev/null
strace -p pid
# record relative timestamp on call entries
strace -r ./a.out
# record time spent in calls
strace -T ./a.out
# summary of times and errors for each call
strace -c ./a.out
# sorting the summary table on any column
strace -c -S calls ./a.out
# enable child process tracing
strace -f ./a.out
# filter
strace -e trace=file,open,process,network,ipc ./a.out
strace -e trace=!file ./a.out

# trace library call
ltrace ./a.out
ltrace cat /dev/null
ltrace -p pid
# record relative timestamp on call entries
ltrace -r ./a.out
# record time spent in calls
ltrace -T ./a.out
# summary of times and errors for each call
ltrace -c ./a.out
# sorting the summary table on any column
ltrace -c -S calls ./a.out
# enable child process tracing
ltrace -f ./a.out
# filter
ltrace -e trace=file,open,process,network,ipc ./a.out
ltrace -e trace=!file ./a.out