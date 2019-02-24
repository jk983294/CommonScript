void exit() {
    asm("mov $60, %eax\n"
        "mov $42, %edi\n"
        "syscall\n");
}

extern "C" void _start() {
    exit();
}

/*
 * this will show function sections
$ g++ -c step1.cpp -o step1.o -O1 -ffunction-sections
$ ld -static step1.o
$ objdump -dr step1.o

step1.o:     file format elf64-x86-64


Disassembly of section .text._Z4exitv:

0000000000000000 <_Z4exitv>:
   0:   b8 3c 00 00 00          mov    $0x3c,%eax
   5:   bf 2a 00 00 00          mov    $0x2a,%edi
   a:   0f 05                   syscall
   c:   c3                      retq

Disassembly of section .text._start:

0000000000000000 <_start>:
   0:   e8 00 00 00 00          callq  5 <_start+0x5>           # jump address is now 00 00 00 00, will patch later
                        1: R_X86_64_PC32        _Z4exitv-0x4    # tell linker that replace the offset with _Z4exitv - 4
   5:   f3 c3                   repz retq

$ readelf -r step1.o

Relocation section '.rela.text._start' at offset 0x200 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000001  000a00000002 R_X86_64_PC32     0000000000000000 _Z4exitv - 4

Relocation section '.rela.eh_frame' at offset 0x218 contains 2 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000500000002 R_X86_64_PC32     0000000000000000 .text._Z4exitv + 0
000000000034  000600000002 R_X86_64_PC32     0000000000000000 .text._start + 0
*/