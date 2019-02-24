extern int foo;

int function(void) {
    return foo;
}

/*
$ g++ -fPIC -shared -o libgot_shared_lib.so got_shared_lib.cpp
$ objdump -d libgot_shared_lib.so
00000000000005ba <_Z8functionv>:
 5ba:   55                      push   %rbp
 5bb:   48 89 e5                mov    %rsp,%rbp
 5be:   48 8b 05 2b 0a 20 00    mov    0x200a2b(%rip),%rax        # 200ff0 <foo>    # 0x200a2b + 5c5(%rip) = 200ff0
 5c5:   8b 00                   mov    (%rax),%eax
 5c7:   5d                      pop    %rbp
 5c8:   c3                      retq

$ readelf --relocs libgot_shared_lib.so

Relocation section '.rela.dyn' at offset 0x3e0 contains 8 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000200ff0  000400000006 R_X86_64_GLOB_DAT 0000000000000000 foo + 0               # find the value of symbol foo and put it into address 0x200ff0

$ readelf --sections libgot_shared_lib.so
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [16] .got              PROGBITS         0000000000200fd8  00000fd8
       0000000000000028  0000000000000008  WA       0     0     8                   # got range [200fd8, 201000(200fd8+28)], and 200ff0 is in its range

when this library is loaded, the dynamic loader will examine the relocation,
go and find the value of foo and patch the .got entry as required.
When it comes time for the code loads to load that value, it will point to the right place and everything just works;
without having to modify any code values
*/