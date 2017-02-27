SHELL = /bin/sh

OBJECTS =  main.o factorial.o hello.o
CFLAG = -Wall -g
CXX = g++
INCLUDE =
LIBS = -lm

# If you indicate just the .h files in the dependency line, make will know that the corresponding .c file is already required
hello:${OBJECTS}
	${CXX} ${CFLAGS} ${INCLUDES} -o $@ ${OBJECTS} ${LIBS}

clean:
	-rm -f *.o hello

.cpp.o:
	${CXX} ${CFLAGS} ${INCLUDES} -c $<

install:
	@echo You must be root to install
