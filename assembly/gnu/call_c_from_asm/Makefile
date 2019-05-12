all:
	gcc  -c print.c -o print.o
	nasm -f elf64 -o main.o main.asm
	ld   -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc main.o print.o -o main

clean:
	rm -f print.o main.o main
