SHELL = /bin/sh

OBJECTS =  my_utils.o test_main.o
CFLAGS = -Wall -g -std=c++11
CXX = g++
INCLUDE =
LIBS = -lm

# If you indicate just the .h files in the dependency line, make will know that the corresponding .c file is already required
main:${OBJECTS}
	${CXX} ${CFLAGS} ${INCLUDES} -o $@ ${OBJECTS} ${LIBS}

clean:
	-rm -f *.o main

.cpp.o:
	${CXX} ${CFLAGS} ${INCLUDES} -c $<

install:
	@echo You must be root to install
