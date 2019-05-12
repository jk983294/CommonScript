all:
	nasm -f elf64 -o hello.o hello.asm
	ld -o hello hello.o
	nasm -f elf64 -o sum.o sum.asm
	ld -o sum sum.o
	nasm -f elf64 -o stack.o stack.asm
	ld -o stack stack.o
	nasm -f elf64 -o reverse.o reverse.asm
	ld -o reverse reverse.o

clean:
	rm -f hello.o hello
	rm -f sum sum.o
	rm -f stack stack.o
	rm -f reverse reverse.o
