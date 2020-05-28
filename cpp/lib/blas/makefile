# compile each cpp file into separate executable

SHELL = /bin/sh

CXX = g++
INC = -I./ -I$(HOME)/include
LDFLAGS = -L./
LDLIBS = -lblas -llapack
CXXFLAGS = -std=c++11 -Wall -O3 -Werror ${INC}

all: $(patsubst %.cpp, %, $(wildcard *.cpp))
%: %.o
	${CXX} ${CXXFLAGS} $< -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp Makefile
	${CXX} -c ${CXXFLAGS} $< -o $@

clean:
	-rm -f *.o blas1 cblas1 cblas2 cblas3 lapack_demo
