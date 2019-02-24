#include <cstdlib>
#include <cstdio>

template <typename T>
inline T init() {
    return std::puts("teacup");
}

int ret = init<int>();

int main() {
    return ret;
}

/*
 * this demo template function
$ g++ -c step7.cpp -o step7.o
$ ld step7.o -lc -static --entry main

$ readelf -sSg step7.o
There are 18 section headers, starting at offset 0x540:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 7] .text._Z4initIiET PROGBITS         0000000000000000  0000009f    # compare to inline version, only signature changes
       0000000000000012  0000000000000000 AXG       0     0     1
  [ 8] .rela.text._Z4ini RELA             0000000000000000  00000410
       0000000000000030  0000000000000018  IG      15     7     8
COMDAT group section [    1] `.group' [_Z4initIiET_v] contains 2 sections:
   [Index]    Name
   [    7]   .text._Z4initIiET_v
   [    8]   .rela.text._Z4initIiET_v
Symbol table '.symtab' contains 19 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
    16: 0000000000000000    18 FUNC    WEAK   DEFAULT    7 _Z4initIiET_v
*/