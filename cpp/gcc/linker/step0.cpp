extern "C" void _start() {
    asm("mov $60, %eax\n"
        "mov $42, %edi\n"
        "syscall\n");
}

/*
$ g++ -c step0.cpp -o step0.o -O1
$ ld -static step0.o
$ ./a.out
$ echo $?
42
$ objdump -dr a.out
Disassembly of section .text:

00000000004000b0 <_start>:
  4000b0:       b8 3c 00 00 00          mov    $0x3c,%eax
  4000b5:       bf 2a 00 00 00          mov    $0x2a,%edi
  4000ba:       0f 05                   syscall
  4000bc:       c3                      retq

$ readelf -S a.out
There are 7 section headers, starting at offset 0x288:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         00000000004000b0  000000b0
       000000000000000d  0000000000000000  AX       0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)

$ readelf -s a.out

Symbol table '.symtab' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 00000000004000b0     0 SECTION LOCAL  DEFAULT    1
     2: 00000000004000c0     0 SECTION LOCAL  DEFAULT    2
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3
     4: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS step0.cpp
     5: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS
     6: 0000000000601000     0 OBJECT  LOCAL  DEFAULT    2 _GLOBAL_OFFSET_TABLE_
     7: 00000000004000b0    13 FUNC    GLOBAL DEFAULT    1 _start
     8: 0000000000601000     0 NOTYPE  GLOBAL DEFAULT    2 __bss_start
     9: 0000000000601000     0 NOTYPE  GLOBAL DEFAULT    2 _edata
    10: 0000000000601000     0 NOTYPE  GLOBAL DEFAULT    2 _end
*/