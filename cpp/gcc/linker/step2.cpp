#include <cstdlib>

extern "C" void _start() {
    std::_Exit(42);
}

/*
 * this demo relocation
$ g++ -c step2.cpp -o step2.o -O1
$ ld step2.o -lc -static
$ readelf -r -s step2.o

Relocation section '.rela.text' at offset 0x1e0 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
00000000000a  000a00000004 R_X86_64_PLT32    0000000000000000 _Exit - 4

Relocation section '.rela.eh_frame' at offset 0x1f8 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0

Symbol table '.symtab' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS step2.cpp
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    6
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    5
     8: 0000000000000000    14 FUNC    GLOBAL DEFAULT    1 _start
     9: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _Exit                    # UND means undefined in this object file, it should be looked up elsewhere
*/