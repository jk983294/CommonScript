#include <cstdlib>
#include <cstdio>

inline int ret = std::puts("teacup");

int main() {
    return ret;
}

/*
 * this demo inline global
$ g++ -std=c++17 -c step8.cpp -o step8.o

$ readelf -sSg step8.o
Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 7] .bss.ret          NOBITS           0000000000000000  000000bc
       0000000000000004  0000000000000000 WAG       0     0     4       # WAG means start with 0
  [ 8] .bss._ZGV3ret     NOBITS           0000000000000000  000000c0    # GV means guard value
       0000000000000008  0000000000000000 WAG       0     0     8

COMDAT group section [    1] `.group' [ret] contains 1 sections:
   [Index]    Name
   [    7]   .bss.ret

COMDAT group section [    2] `.group' [_ZGV3ret] contains 1 sections:
   [Index]    Name
   [    8]   .bss._ZGV3ret
Symbol table '.symtab' contains 19 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
    16: 0000000000000000     4 OBJECT  UNIQUE DEFAULT    7 ret          # UNIQUE is weak symbol
    18: 0000000000000000     8 OBJECT  UNIQUE DEFAULT    8 _ZGV3ret
*/