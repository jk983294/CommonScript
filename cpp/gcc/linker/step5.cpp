#include <cstdlib>
#include <cstdio>

int ret = std::puts("teacup");

int main() {
    return ret;
}

/*
 * this demo global initialization when switch to main
$ g++ -c step5.cpp -o step5.o -O1
$ ld step5.o -lc -static --entry main

$ objdump -s step5.o
Contents of section .init_array:
 0000 00000000 00000000

$ objdump -r step5.o
RELOCATION RECORDS FOR [.init_array]:
OFFSET           TYPE              VALUE
0000000000000000 R_X86_64_64       .text+0x0000000000000007
*/