### general purpose registers

| 64 bits | 32 bits |  16 bits  | 8 bits    |
| :----:  | :----:  | :----:    | :----:    |
| rax     | eax     |   ax      | al        |
| rbx     | ebx     |   bx      | bl        |
| rcx     | ecx     |   cx      | cl        |
| rdx     | edx     |   dx      | dl        |
| rsi     | esi     |   si      | sil       |
| rdi     | edi     |   di      | dil       |
| rbp     | ebp     |   bp      | bpl       |
| rsp     | esp     |   sp      | spl       |
| r8      | r8d     |   r8w     | r8b       |
| r9      | r9d     |   r9w     | r9b       |
| r10     | r10d    |   r10w    | r10b      |
| r11     | r11d    |   r11w    | r11b      |
| r12     | r12d    |   r12w    | r12b      |
| r13     | r13d    |   r13w    | r13b      |
| r14     | r14d    |   r14w    | r14b      |
| r15     | r15d    |   r15w    | r15b      |

### special variable
* $ - returns position in memory of string where $ defined
*$$ - returns position in memory of current section start

### syscall convention
* rax - temporary register; when we call a syscall, rax must contain syscall number
* rdi - used to pass 1st argument to functions
* rsi - pointer used to pass 2nd argument to functions
* rdx - used to pass 3rd argument to functions

size_t sys_write(unsigned int fd, const char * buf, size_t count);

* 1 -> rax
* fd -> rdi
* buf -> rdi
* count -> rdx

https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_64.tbl

### data section
```nasm
section .data   ; initialized data or constants
    num1:   equ 100
    num2:   equ 50
    msg:    db "Sum is correct", 10
section .bss    ; non initialized variables
```

type:

| name    | size    |  
| :----:  | :----:  |
| byte     | 8 bits     |
| word     | 2 bytes     |
| double word     | 4 bytes     |
| quad word     | 8 bytes     |
| double quad word     | 16 bytes     |

* DB, DW, DD, DQ, DT, DO, DY and DZ - are used for declaring initialized data
* RESB, RESW, RESD, RESQ, REST, RESO, RESY and RESZ - are used for declaring non initialized variables
* INCBIN - includes External Binary Files
* EQU - defines constant. For example:
* TIMES - Repeating Instructions or Data

### text section
```nasm
section .text
    global _start
_start:
```

### code
```nasm
[label:] instruction [operands] [; comment]
MOV COUNT, 48; Put value 48 in the COUNT variable
```

### Arithmetic operations
* ADD - integer add
* SUB - substract
* MUL - unsigned multiply
* IMUL - signed multiply
* DIV - unsigned divide
* IDIV - signed divide
* INC - increment
* DEC - decrement
* NEG - negate

### Control flow
conditional jump
```nasm
cmp rax, 50     ; if(rax != 50)
jne .exit       ;     exit();  
jmp .right      ; else right();
```
* JE - if equal
* JZ - if zero
* JNE - if not equal
* JNZ - if not zero
* JG - if first operand is greater than second
* JGE - if first operand is greater or equal to second
* JA - the same that JG, but performs unsigned comparison
* JAE - the same that JGE, but performs unsigned comparison

unconditional jump
* JMP label
