# precompile
gcc -E a.cpp

# assembly
gcc -S a.cpp

# 打印gcc预定义的宏信息
gcc -dM -E - < /dev/null

# 所有优化选项以及缺省情况下它们是否打开
g++ -Q --help=optimizers -O1

# 打印彩色诊断信息
export GCC_COLORS=error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01

# 打印头文件搜索路径
gcc -v foo.cpp

# 打印连接库的具体路径
g++ -print-file-name=libgpr.so
g++ -print-file-name=libbsd.a

# 在命令行中预定义宏
gcc -D DEBUG main.cpp
gcc -DDEBUG main.cpp

# 在命令行中取消宏定义
gcc -U DEBUG main.cpp
gcc -UDEBUG main.cpp

# 只做语法检查
g++ -fsyntax-only main.cpp

# 保存临时文件 obj file
g++ -save-temps main.cpp

# 打开警告信息
g++ -Wall main.cpp
