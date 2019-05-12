### function stack
When we call a function, Firstly, its return address pushes to stack, then function’s parameters pushes to stack from right to left.

After end of function execution, address copied in (RIP) and application continue to executes from next place after function

### stack register
* RBP is the base pointer register. It points to the base of the current stack frame.
* RSP is the stack pointer, which points to the top of current stack frame.

two commands for work with stack:
* push argument - increments stack pointer (RSP) and stores argument in location pointed by stack pointer
* pop argument - copied data to argument from location pointed by stack pointer

```nasm
_start:
    mov rax, 1          ; now assume rbp = rsp
    mov rdx, 2
    push rax            ; [rsp] = 1; [rbp] = 1
    push rdx            ; [rsp] = 2; [rbp - 8] = 2
    mov rax, [rsp + 8]  ; [rsp + 8] = [rbp] = 1
```

### function call
x86_64 linux calling conventions, according to System V AMD64 ABI:
* rdi - first argument
* rsi - second argument
* rdx - third argument
* rcx - fourth argument
* r8 - fifth argument
* r9 - sixth
Next arguments will be passed in stack

int foo(int a1, int a2, int a3, int a4, int a5, int a6, int a7);

* a1 -> rdi
* a2 -> rsi
* a3 -> rdx
* a4 -> rcx
* a5 -> r8
* a6 -> r9
* a7

#### x86_64 calling convention. The way we pass float parameters through registers.
There is special registers: xmm0 - xmm15 provided by sse.
First of all we need to put number of xmmN register to rax register, and put result to xmmN register.
```nasm
mov rax, 0
movq xmm0, [result]
call printResult        ; printResult(double x)
```


### data section
```nasm
section .data   ; initialized data or constants
    num1:   equ 100
    num2:   equ 50
    msg:    db "Sum is correct", 10
section .bss    ; non initialized variables
```
