# $(dir <names...>)
# get directory name, if no '/' found, return './', other wise return part before '/'
$(dir src/foo.c hacks)                                  # 'src/ ./'

# $(notdir <names...>)
# get file name, it does not include directory part
$(dir src/foo.c hacks)                                  # 'foo.c hacks'

# $(suffix <names...>) get file suffix, if no suffix, then '' returned
$(suffix src/foo.c src-1.0/bar.c hacks)                 # '.c .c'

# $(basename <names...>) get file prefix
$(basename src/foo.c src-1.0/bar.c hacks)               # 'src/foo src-1.0/bar hacks'

# $(addsuffix <suffix>,<names...>) add suffix for file list
$(addsuffix .c,foo bar)                                 # 'foo.c bar.c'

# $(addprefix <prefix>,<names...>)
$(addprefix src/,foo bar)                               # 'src/foo src/bar'

# $(join <list1>,<list2>) element by element join
$(join aaa bbb , 111 222 333)                           # 'aaa111 bbb222 333'
