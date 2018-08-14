# Double-Colon Rules
# each double-colon rule is processed individually, just as rules with different targets are processed.
# the double-colon rules for a target are executed in the order they appear in the makefile.
all::  $(ALL_OBJECTS) $(ALL_LIBS) $(ALL_BINARIES)

#*************************  DOC ***********************
doc:
	doxygen doxygen.ini

tags:
	find . -regex '.*\.\(c\|cpp\|h\)$\' -print0 | xargs -0  ctags --sort=yes --c++-kinds=+p --fields=+l  --fields=+iaS --extra=+q --language-force=c++
