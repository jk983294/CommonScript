# $(foreach  var, list, cmd), extract list word to var, execute cmd with var
names := a b c d
files := $(foreach n,$(names),$(n).o)           # result is "a.o b.o c.o d.o"
