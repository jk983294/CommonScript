INCLUDES =
CXX = g++
LIBS =  -lm
CFLAGS = -Wall -g -std=c++11

main: main.o func1.o func2.o
	$(CXX) main.o func1.o func2.o -o main

tests: tests_main.o test_func1.o test_func2.o func1.o func2.o
	$(CXX) tests_main.o test_func1.o test_func2.o func1.o func2.o -o tests

test_func1.o: ./test/test_func1.cpp
	$(CXX) $(CFLAGS) -c ./test/test_func1.cpp

test_func2.o: ./test/test_func1.cpp
	$(CXX) $(CFLAGS) -c ./test/test_func2.cpp

tests_main.o: ./test/tests_main.cpp
	$(CXX) $(CFLAGS) -c ./test/tests_main.cpp

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

func1.o: func1.cpp
	$(CXX) $(CFLAGS) -c func1.cpp

func2.o: func2.cpp
	$(CXX) $(CFLAGS) -c func2.cpp

install:
	@echo You must be root to install

clean :
	-rm -f *.o main tests
