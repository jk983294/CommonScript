# 打印ASCII字符串
(gdb) x/s str1

# 打印wchar_t字符串
(gdb) p sizeof(wchar_t)                                 # if 4 use x/ws or if 2 use x/hs
(gdb) x/ws str2
(gdb) x/hs str2

# 打印STL容器中的内容 python script libstdc++-v3/python
# vector<int> vec{1, 2, 3};
(gdb) p vec                                             # $1 = std::vector of length 3, capacity 3 = {1, 2, 3}

# 打印大数组中的内容
# int array[201];
(gdb) set print elements number-of-elements             # default max number is 200, use this to bypass
or
(gdb) set print elements 0
or
(gdb) set print elements unlimited
then
(gdb) p array

# 打印数组中任意连续元素值
(gdb) p array[60]@10                                    # print 60 - 69 elements
(gdb) p *array@10                                       # print first 10

# 打印数组的索引下标
(gdb) set print array-indexes on
(gdb) p array

# 格式化打印数组
(gdb) call print(matrix, 10, 10)                        # 需要定义 void print(int** matrix, int m, int n)

# 打印函数局部变量的值
# trick 1
(gdb) bt full
(gdb) bt full 2                                         # print local variable of 2 frames
# trick 2
(gdb) info locals

# 打印调用栈帧中变量
# 先切换到该栈帧中，然后打印
(gdb) f 1
(gdb) p var
# 也可以不进行切换，直接打印
(gdb) p func2::var
# 对于C++的函数名，需要使用单引号括起来
(gdb) p '(anonymous namespace)::zerg::func'::n->pi->inst->dump()

# 静态变量的值, 同名静态变量需要文件名做区分
(gdb) p 'static1.cpp'::var
(gdb) p 'static2.cpp'::var

# 打印变量的类型和所在文件
(gdb) whatis vec                                        # type = std::vector<int, std::allocator<int> >
(gdb) ptype vec

# 打印内存的值
# x/nfu addr 以f格式打印从addr开始的n个长度单元为u的内存值
# f: t 2进制 x 16进制 o 8进制 u 无符号10进制
# u: b byte h 2byte w 4byte g 8byte
(gdb) x/16xw array                                      # 16进制格式打印数组array16个word

# 每行打印一个结构体成员
(gdb) set print pretty on
(gdb) p myStruct

# 通过基类打印派生类
(gdb) set print object on
(gdb) p myBase

# $_ and $__
# x命令会把最后检查的内存地址值存在$_中，并且会把这个地址中的内容放在$__
(gdb) x/16xb a
(gdb) p $_
(gdb) p $__

# 打印进程内存信息
(gdb) i proc mappings                                   # 进程的内存映射信息
(gdb) i files
(gdb) i target
