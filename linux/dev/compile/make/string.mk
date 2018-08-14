# wildcard
$(wildcard *.cpp)
$(patsubst %.c,%.o,$(wildcard *.cpp))           # get all object files from cpp files

# $(subst <from>,<to>,<text>)
# substitute all <from> to <to> in <text>
$(subst ee,EE,feet on the street)               # result is 'fEEt on the strEEt'

# $(patsubst <pattern>, <replacement>, <text>)
# substitute all match with <pattern> (greedy mode) to <replacement> in <text>
# <pattern> can contains wildcard "%", it means any length string
# if <replacement> also contains "%", it is the string in <pattern>
$(patsubst %.c, %.o, x.c.c bar.c)               # result is 'x.c.o bar.o'
OBJ = $(SRC_FILES: .c=.o)                       # substitute .c => .o

# $(strip <string>)
# remove head and tailing space
$(strip a b c )                                 # 'a b c'

# $(findstring <find>, <in>)
# sub string of <find> in <in>
$(findstring a,a b c)                           # 'a'
$(findstring a,b c)                             # ''

# $(filter <pattern...>,<text>)
# keep <text> which match the <pattern...>
sources := foo.c bar.c baz.s ugh.h
$(filter %.c %.s, $(sources))                   # 'foo.c bar.c baz.s'

$(filter-out <pattern...>,<text>)
# keep <text> which does not match the <pattern...>
objects=main1.o foo.o main2.o bar.o
mains=main1.o main2.o
$(filter-out $(mains),$(objects))               # 'foo.o bar.o'

$(sort <list>)
$(sort foo bar lose)                            # 'bar foo lose'

$(word <n>,<text>)
# get nth word from <text>
$(word 2, foo bar baz)                          # 'bar'

$(wordlist <startIndex>,<endIndex>,<text>)
$(wordlist 2, 3, foo bar baz)                   # 'bar baz'

$(words <text>)
# get word count of <text>
$(words foo bar baz)                            # 3
$(word $(words <text>),<text>)                  # get last string

$(firstword <text>)
$(word 1,<text>)
