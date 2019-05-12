### Macros
single line
```nasm
; %define macro_name(parameter) value
%define argc rsp + 8
%define cliArg1 rsp + 24

mov rax, [argc]     ; argc expand to 'rsp + 8'
cmp rax, 3
jne .mustBe3args
```

multi-line
```nasm
%macro bootstrap 1
    push ebp
    mov ebp,esp
%endmacro

_start:
    bootstrap
```

PRINT macro
```nasm
%macro PRINT 1
    pusha                                   ; push all general registers
    pushf                                   ; push all float registers
    jmp %%astr                              ; jump to %%astr label
%%str db %1, 0
%%strln equ $-%%str
%%astr: _syscall_write %%str, %%strln
    popf
    popa
%endmacro

%macro _syscall_write 2
	mov rax, 1
    mov rdi, 1
    mov rsi, %%str
    mov rdx, %%strln
    syscall
%endmacro

;; usage
PRINT "Hello World!"
```

### Useful standard macros
STRUC and ENDSTRUC for data structure defintion
```nasm
struc person
   name: resb 10
   age:  resb 1
endstruc

;; usage
section .data
    p: istruc person
      at name db "name"
      at age  db 25
    iend

section .text
_start:
    mov rax, [p + person.name]
```

%include

We can include other assembly files and jump to there labels or call functions with %include directive.

