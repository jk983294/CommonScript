# compile each cpp file into separate executable

SHELL = /bin/sh

CXX = g++
INC = -I./ -I$(HOME)/include
LDFLAGS = -L./
LDLIBS = -lbenchmark -pthread
# -fno-omit-frame-pointer  this is crucial to call graph perf generation
CXXFLAGS = -std=c++11 -Wall -O3 -fno-exceptions -fno-rtti -fno-omit-frame-pointer -pedantic -Werror ${INC}

all: $(patsubst %.cpp, %, $(wildcard *.cpp))
%: %.o
	${CXX} ${CXXFLAGS} $< -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp Makefile
	${CXX} -c ${CXXFLAGS} $< -o $@

clean:
	-rm -f *.o *_bench
