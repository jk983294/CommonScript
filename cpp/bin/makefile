# compile each cpp file into separate executable

SHELL = /bin/sh

CXXFLAGS = -std=c++11 -Wall -g -pthread
CXX = g++
INCLUDES =

# all: library.cpp main.cpp
# $@ evaluates to all
# $< evaluates to library.cpp
# $^ evaluates to library.cpp main.cpp

all: $(patsubst %.cpp, %, $(wildcard *.cpp))
%: %.o
	${CXX} ${CXXFLAGS} ${INCLUDES} $^ -o $@

%.o: %.cpp Makefile
	${CXX} -c ${CXXFLAGS} ${INCLUDES} $< -o $@

clean:
	-rm -f *.o
