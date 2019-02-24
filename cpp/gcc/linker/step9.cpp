#include <cstdlib>
#include <cstdio>

// !!! don't use static in header, it will copy to all translation unit
static int init() {
    return std::puts("teacup");
}

int ret = init();

int main() {
    return ret;
}

/*
 * this demo static function
$ g++ -c step9.cpp -o step9.o

$ readelf -sSg step9.o
There are no section groups in this file.

Symbol table '.symtab' contains 17 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     6: 0000000000000000    18 FUNC    LOCAL  DEFAULT    1 _ZL4initv    # LOCAL will duplicate in every object
*/