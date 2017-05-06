# compile each cpp file into separate executable

SHELL = /bin/sh

CXXFLAGS = -std=c++11 -Wall -g -pthread
CXX = g++
INCLUDES =

all: $(patsubst %.cpp, %, $(wildcard *.cpp))
%: %.o
	${CXX} ${CXXFLAGS} ${INCLUDES} $< -o $@

%.o: %.cpp Makefile
	${CXX} -c ${CXXFLAGS} ${INCLUDES} $< -o $@

clean:
	-rm -f *.o
