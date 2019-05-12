all:
	nasm -f elf64 -o print.o print.asm
	gcc print.o main.c -o main

clean:
	rm -f print.o main
