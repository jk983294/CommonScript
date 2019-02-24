# object file

## object file content contains:
* ranges of unsplittable data (sections)
* names that define or reference data (symbols)
* lists of modifications of data (relocations)

```
# dump sections, symbols and relocations
$ readelf b.o -sSr
```

## section

* can be moved around relative to other sections
* linker combines all compatible sections based on name, type and flags
* allow grouping to have a contiguous ranges with the same flags to mmap

```
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
```

## symbol
* defines or reference a location
* value(virtual address), type, scope(bind), location(which section), name
* weak symbol means you can have a bunch of this symbol, linker choose one of them (inline function)

```
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
```

## relocation
* locations in section data that refer to symbols
* update with the final location of the symbol when known
* each section have a relocation table
* location(offset in section), type(function pointer etc.), value
* relocations are entries in binaries that are left to be filled later by the dynamic linker
* relocation is a descriptor which essentially says "determine the value of X, and put that value into the binary at offset Y"

```
$ readelf -r step1.o

Relocation section '.rela.text._start' at offset 0x200 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000001  000a00000002 R_X86_64_PC32     0000000000000000 _Z4exitv - 4

Relocation section '.rela.eh_frame' at offset 0x218 contains 2 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000500000002 R_X86_64_PC32     0000000000000000 .text._Z4exitv + 0
000000000034  000600000002 R_X86_64_PC32     0000000000000000 .text._start + 0
```

## init_array
* .init_array section is a function array
* linker concatenate all sections init_array function to a function pointer
* an array of function addresses that must be called, in-order, to perform initialization. Some of the entries in the array can be 0 or -1, and should be ignored.

## comdat group:
* each section can belong to a group
* if a group has already been loaded by linker, ignore all group members in other object files
* linker will insert the group name into a table, if new name then it get insert, if it is duplicate one, linker will ignore it
* this is for how weak symbol works

```
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
    14: 0000000000000000    18 FUNC    WEAK   DEFAULT    7 _Z4initv
```

## debug info
* collection of sections mapping source to object code
* linker responsible for deduplication and indexing

.gcc_exception_table

## static linking
* read input, record all metadata (sections/symbols/relocations)
* resolve symbol
    1. replace weak symbol with strong definition
    2. error on duplicate strong definition)
* layout sections
    1. group section by type and flags
    2. combine input sections with the same name prefix
    3. assign virtual address while respecting alignment
* write output
* apply relocation
    1. lookup any symbols it reference
    2. compute the result according to the reloc type
    3. write the result to the output

## link optimization
* identical code folding
* relocation relaxation
* TLS relaxation
* merge sections
* garbage collection
* link time optimization

## dynamic linking
* loading
    1. executable image contains instructions for the loader (ELF headers)
    2. instruct which byte to put where in memory and also which access flags
* dynamic relocation
    1. relocation applied after the bytes are in memory
    2. used for address which are not known until load time (reference to other shared lib/address space layout randomization)
    3. generally not allowed to relocate executable bytes
* PLT/GOT
    1. table of address
    2. eagerly relocated for data reference
    3. lazily relocated in for code reference
    4. every executable and so has its own got

## PLT (procedure linkage table) used to patch function call in GOT
* lazy binding, plt call linker to patch GOT
* The compiler forces indirection through the PLT for any calls to functions it can't see the definition for
* lazy binding — by convention when the dynamic linker loads a library,
it will put an identifier and resolution function into known places in the GOT.
Therefore, what happens is roughly this: on the first call of a function, it falls through to call the default stub,
which loads the identifier and calls into the dynamic linker, 
which at that point has enough information to figure out "hey, this lib.so is trying to find the symbol xyz".
It will go ahead and find it, and then patch the address into the GOT such that
the next time the original PLT entry is called, it will load the actual address of the function, rather than the lookup stub.

## GOT (global offset table) used to patch data offset
when this library is loaded, the dynamic loader will examine the relocation,
go and find the value of foo and patch the .got entry as required.
When it comes time for the code loads to load that value, it will point to the right place and everything just works;
without having to modify any code values
