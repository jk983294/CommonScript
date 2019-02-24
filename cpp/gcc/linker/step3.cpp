#include <cstdlib>

int ret = 42;

extern "C" void _start() {
    std::_Exit(ret);
}

/*
 * this demo global variable
$ g++ -c step3.cpp -o step3.o -O1
$ ld step3.o -lc -static
$ readelf -r -s step3.o

Relocation section '.rela.text' at offset 0x208 contains 2 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000006  000900000002 R_X86_64_PC32     0000000000000000 ret - 4
00000000000b  000b00000004 R_X86_64_PLT32    0000000000000000 _Exit - 4

Relocation section '.rela.eh_frame' at offset 0x238 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0

Symbol table '.symtab' contains 12 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS step3.cpp
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    6
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    5
     8: 0000000000000000    15 FUNC    GLOBAL DEFAULT    1 _start
     9: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    3 ret              # in section 3 which is .data
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
    11: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _Exit

$ objdump -s step3.o

step3.o:     file format elf64-x86-64

Contents of section .text:
 0000 4883ec08 8b3d0000 0000e800 000000    H....=.........
Contents of section .data:
 0000 2a000000                             *...                             # this is ret 0x2a is 42
*/