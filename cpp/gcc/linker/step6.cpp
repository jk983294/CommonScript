#include <cstdlib>
#include <cstdio>

inline int init() {
    return std::puts("teacup");
}

int ret = init();

int main() {
    return ret;
}

/*
 * this demo inline function
$ g++ -c step6.cpp -o step6.o
$ ld step6.o -lc -static --entry main

$ readelf -sSg step6.o
There are 18 section headers, starting at offset 0x540:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 7] .text._Z4initv    PROGBITS         0000000000000000  0000009f
       0000000000000012  0000000000000000 AXG       0     0     1
  [ 8] .rela.text._Z4ini RELA             0000000000000000  00000408
       0000000000000030  0000000000000018  IG      15     7     8
COMDAT group section [    1] `.group' [_Z4initv] contains 2 sections:
   [Index]    Name
   [    7]   .text._Z4initv
   [    8]   .rela.text._Z4initv
Symbol table '.symtab' contains 19 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
    14: 0000000000000000    18 FUNC    WEAK   DEFAULT    7 _Z4initv     # weak symbol means you can have a bunch of this symbol, linker choose one of them
*/