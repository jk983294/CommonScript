#include <cstdlib>
#include <cstdio>

int ret = std::puts("teacup");

extern "C" void _start() {
    std::_Exit(ret);
}

/*
 * this demo global initialization
$ g++ -c step4.cpp -o step4.o -O1
$ ld step4.o -lc -static
$ readelf -Sr step4.o
There are 15 section headers, starting at offset 0x418:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       000000000000002a  0000000000000000  AX       0     0     1
  [ 2] .rela.text        RELA             0000000000000000  000002d8
       0000000000000078  0000000000000018   I      12     1     8
  [ 3] .data             PROGBITS         0000000000000000  0000006a
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .bss              NOBITS           0000000000000000  0000006c
       0000000000000004  0000000000000000  WA       0     0     4
  [ 5] .rodata.str1.1    PROGBITS         0000000000000000  0000006c
       0000000000000007  0000000000000001 AMS       0     0     1
  [ 6] .init_array       INIT_ARRAY       0000000000000000  00000078
       0000000000000008  0000000000000008  WA       0     0     8
  [ 7] .rela.init_array  RELA             0000000000000000  00000350
       0000000000000018  0000000000000018   I      12     6     8
  [ 8] .comment          PROGBITS         0000000000000000  00000080
       0000000000000025  0000000000000001  MS       0     0     1
  [ 9] .note.GNU-stack   PROGBITS         0000000000000000  000000a5
       0000000000000000  0000000000000000           0     0     1
  [10] .eh_frame         PROGBITS         0000000000000000  000000a8
       0000000000000048  0000000000000000   A       0     0     8
  [11] .rela.eh_frame    RELA             0000000000000000  00000368
       0000000000000030  0000000000000018   I      12    10     8
  [12] .symtab           SYMTAB           0000000000000000  000000f0
       0000000000000198  0000000000000018          13    12     8
  [13] .strtab           STRTAB           0000000000000000  00000288
       000000000000004b  0000000000000000           0     0     1
  [14] .shstrtab         STRTAB           0000000000000000  00000398
       0000000000000079  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)

Relocation section '.rela.text' at offset 0x2d8 contains 5 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000006  000d00000002 R_X86_64_PC32     0000000000000000 ret - 4
00000000000b  000f00000004 R_X86_64_PLT32    0000000000000000 _Exit - 4
000000000016  000a00000002 R_X86_64_PC32     0000000000000000 .LC0 - 4
00000000001b  001000000004 R_X86_64_PLT32    0000000000000000 puts - 4
000000000021  000d00000002 R_X86_64_PC32     0000000000000000 ret - 4

Relocation section '.rela.init_array' at offset 0x350 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000000  000200000001 R_X86_64_64       0000000000000000 .text + f

Relocation section '.rela.eh_frame' at offset 0x368 contains 2 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0
000000000034  000200000002 R_X86_64_PC32     0000000000000000 .text + f

$ objdump -s step4.o
Contents of section .init_array:
 0000 00000000 00000000

$ objdump -r step4.o
RELOCATION RECORDS FOR [.init_array]:
OFFSET           TYPE              VALUE
0000000000000000 R_X86_64_64       .text+0x000000000000000f
*/