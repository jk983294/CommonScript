# compile each cpp file into separate executable

SHELL = /bin/sh

CCFLAGS =
CC = gcc
INCLUDES =

TARGETS:= first second wrap main1 main2 my_malloc malloc_main normal_malloc_main mynet
OBJ    := first.o second.o wrap.o main.o
DEPS   :=

all: $(TARGETS)

first.o:
	$(CC) -fPIC -c first.c

second.o:
	$(CC) -fPIC -c second.c

wrap.o:
	$(CC) -fPIC -c wrap.c

main.o:
	$(CC) -c main.c

my_malloc.o:
	$(CC) -fPIC -c my_malloc.c

mynet.o:
	$(CC) -fPIC -c mynet.c

first: first.o
	$(CC) --share first.o -o libfirst.so

second: second.o
	$(CC) --share second.o -o libsecond.so

wrap: wrap.o
	$(CC) --share wrap.o -o libwrap.so

main1: main.o first second wrap
	$(CC) -o main1 main.o -L. -Wl,-rpath=. -lwrap -lfirst -lsecond -ldl

main2: main.o first second wrap
	$(CC) -o main2 main.o -L. -Wl,-rpath=. -lwrap -lsecond -lfirst -ldl

my_malloc: my_malloc.o
	$(CC) --share my_malloc.o -o libmy_malloc.so

mynet: mynet.o
	$(CC) --share mynet.o -o libmynet.so -ldl

malloc_main: my_malloc
	$(CC) -o malloc_main malloc_main.c -L. -Wl,-rpath=. -lmy_malloc -ldl

normal_malloc_main:
	$(CC) -o normal_malloc_main malloc_main.c -ldl

clean:
	-rm -f *.o *.so first second wrap main1 main2 malloc_main normal_malloc_main
