#include <cstdlib>
#include <cstdio>

void external();

extern bool b;

struct A {
    ~A() {
        external();
    }
};

int blah() {
    A a;
    external();
    if(b)
        throw 2;
    external();
    return 4;
}

/*
 * this demo exception
$ g++ -c step10.cpp -o step10.o

$ readelf -sSg step10.o
Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 9] .gcc_except_table PROGBITS         0000000000000000  0000010c
       0000000000000004  0000000000000000  AG       0     0     1
  [10] .gcc_except_table PROGBITS         0000000000000000  00000110
       000000000000000d  0000000000000000   A       0     0     1
  [15] .eh_frame         PROGBITS         0000000000000000  00000150
       0000000000000070  0000000000000000   A       0     0     8

Symbol table '.symtab' contains 17 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
    11: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT    1 _ZN1AD5Ev
    17: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
    18: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _Z8externalv
    19: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND __gxx_personality_v0
    23: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND __cxa_allocate_exception
    24: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _ZTIi
    25: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND __cxa_throw
    26: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _Unwind_Resume
    27: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND __stack_chk_fail
*/