INCLUDES = -I "/home/tutorialspoint/header"
CXX = g++
LIBS =  -lm
CFLAGS = -g -Wall

# dependent on main.o, factorial.o, and hello.o files.
# Hence, whenever there is a change in any of these object files, make will take action.
hello: main.o factorial.o hello.o
	$(CXX) main.o factorial.o hello.o -o hello

main.o: main.cpp functions.h
	$(CXX) $(CFLAGS) -c main.cpp

factorial.o: factorial.cpp functions.h
	$(CXX) $(CFLAGS) -c factorial.cpp

hello.o: hello.cpp functions.h
	$(CXX) $(CFLAGS) -c hello.cpp

install:
	@echo You must be root to install

clean :
	rm main.o factorial.o hello.o hello
