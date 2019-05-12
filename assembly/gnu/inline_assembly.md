### general
```
asm [volatile] ("assembly code" : output operand : input operand : clobbers);

__asm__(
        "movq $1, %%rax \n\t"
        "movq $1, %%rdi \n\t"
        "movq %1, %%rsi \n\t"   // %1 refer str
        "movl %2, %%edx \n\t"   // %2 refer len
        "syscall"
        : "=g"(ret)
        : "g"(str), "g" (len));
```

Each operand is described by constraint string followed by C expression in parentheses. There are a number of constraints:
* r - Kept variable value in general purpose register
* g - Any register, memory or immediate integer operand is allowed, except for registers that are not general registers.
* f - Floating point register
* m - A memory operand is allowed, with any kind of address that the machine supports in general.
* and etc…

### variable
* $1 -> immediate number
* %1 -> first argument
* %%rax -> register

