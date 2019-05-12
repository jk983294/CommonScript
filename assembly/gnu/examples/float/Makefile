all:
	gcc  -c print.cpp -o print.o
	nasm -f elf64 -o float.o float.asm
	ld   -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc float.o print.o -o main

clean:
	rm -f print.o float.o main
