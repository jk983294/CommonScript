int foo(void);

int function(void) {
    return foo();
}

/*
$ g++ -fPIC -shared -o libplt_shared_lib.so plt_shared_lib.cpp
$ objdump -d libplt_shared_lib.so
00000000000005ca <_Z8functionv>:
 5ca:   55                      push   %rbp
 5cb:   48 89 e5                mov    %rsp,%rbp
 5ce:   e8 fd fe ff ff          callq  4d0 <_Z3foov@plt>        # call at address 4d0 which is plt entry
 5d3:   5d                      pop    %rbp
 5d4:   c3                      retq

$ objdump -D libplt_shared_lib.so
00000000000004d0 <_Z3foov@plt>:
 4d0:   ff 25 42 0b 20 00       jmpq   *0x200b42(%rip)          # 201018 <_Z3foov>, (0x200b42 + 0x4d6)  = 0x201018
 4d6:   68 00 00 00 00          pushq  $0x0
 4db:   e9 e0 ff ff ff          jmpq   4c0 <.plt>

Disassembly of section .got.plt:

0000000000201000 <_GLOBAL_OFFSET_TABLE_>:
  201000:       60                      (bad)
  201001:       0e                      (bad)
  201002:       20 00                   and    %al,(%rax)
        ...
  201018:       d6                      (bad)                   # origin 0x201018 address store 0x04d6 which is the next instruction of 4d0, push 0 and jump 4c0
  201019:       04 00                   add    $0x0,%al

00000000000004c0 <.plt>:
 4c0:   ff 35 42 0b 20 00       pushq  0x200b42(%rip)        # 201008 <_GLOBAL_OFFSET_TABLE_+0x8>
 4c6:   ff 25 44 0b 20 00       jmpq   *0x200b44(%rip)        # 201010 <_GLOBAL_OFFSET_TABLE_+0x10>
 4cc:   0f 1f 40 00             nopl   0x0(%rax)

$ readelf --relocs libplt_shared_lib.so

Relocation section '.rela.plt' at offset 0x488 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000201018  000100000007 R_X86_64_JUMP_SLO 0000000000000000 _Z3foov + 0   # find the value of symbol foo and put it into address 0x201018

$ readelf --sections libplt_shared_lib.so
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 8] .plt              PROGBITS         00000000000004c0  000004c0
       0000000000000020  0000000000000010  AX       0     0     16

lazy binding — by convention when the dynamic linker loads a library,
it will put an identifier and resolution function into known places in the GOT.
Therefore, what happens is roughly this: on the first call of a function, it falls through to call the default stub,
which loads the identifier and calls into the dynamic linker,
which at that point has enough information to figure out "hey, this lib.so is trying to find the symbol xyz".
It will go ahead and find it, and then patch the address into the GOT such that
the next time the original PLT entry is called, it will load the actual address of the function, rather than the lookup stub.
*/