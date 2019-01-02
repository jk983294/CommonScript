# GCC, uses AT&T/UNIX assembly syntax.
"Op-code src dst" in AT&T syntax
Register names are prefixed by %, ie, if eax is to be used, write %eax
AT&T immediate operands are preceded by ’$’. For static "C" variables also prefix a ’$’. for hexadecimals, we first see a ’$’, then ’0x’ and finally the constants.
In AT&T syntax the size of memory operands is determined from the last character of the op-code name. Op-code suffixes of ’b’, ’w’, and ’l’ specify byte(8-bit), word(16-bit), and long(32-bit) memory references.
Memory Operands, section:disp(base, index, scale) in AT&T.
+------------------------------+------------------------------------+
|       Intel Code             |      AT&T Code                     |
+------------------------------+------------------------------------+
| mov     eax,1                |  movl    $1,%eax                   |
| mov     ebx,0ffh             |  movl    $0xff,%ebx                |
| int     80h                  |  int     $0x80                     |
| mov     ebx, eax             |  movl    %eax, %ebx                |
| mov     eax,[ecx]            |  movl    (%ecx),%eax               |
| mov     eax,[ebx+3]          |  movl    3(%ebx),%eax              |
| mov     eax,[ebx+20h]        |  movl    0x20(%ebx),%eax           |
| add     eax,[ebx+ecx*2h]     |  addl    (%ebx,%ecx,0x2),%eax      |
| lea     eax,[ebx+ecx]        |  leal    (%ebx,%ecx),%eax          |
| sub     eax,[ebx+ecx*4h-20h] |  subl    -0x20(%ebx,%ecx,0x4),%eax |
+------------------------------+------------------------------------+

# format
asm("movl %ecx %eax");          // moves the contents of ecx to eax
__asm__("movb %bh (%eax)");     // moves the byte from bh to the memory pointed by eax
__asm__("movl %eax, %ebx\n\t"
        "movl $56, %esi\n\t"
        "movl %ecx, $label(%edx,%ebx,$4)\n\t"
        "movb %ah, (%ebx)");    // multi-line code, use \n\t to start new line

# extended asm
asm ( assembler template
    : output operands                  /* optional */
    : input operands                   /* optional */
    : list of clobbered registers      /* optional */
    );

# Assembler Template
Operands corresponding to the C expressions are represented by %0, %1 ... etc

# Operands
"constraint" (C expression) is the general form
## Operand referencing
Numbering is done as follows. If there are a total of n operands (both input and output inclusive),
then the first output operand is numbered 0, continuing in increasing order,
and the last input operand is numbered n-1.

# Clobber List
This is to inform gcc that we will use and modify them ourselves.
So gcc will not assume that the values it loads into these registers will be valid.
We shoudn’t list the input and output registers in this list.
If our instruction can alter the condition code register, we have to add "cc" to the list of clobbered registers.
If our instruction modifies memory in an unpredictable fashion, add "memory" to the list of clobbered registers.
We also have to add the volatile keyword if the memory affected is not listed in the inputs or outputs of the asm.

# Volatile
If our assembly statement must execute where we put it, So to keep it from moving, deleting and all, we declare it as
asm volatile ( ... : ... : ... : ...);

# constraints
## Register operand constraint(r)
asm ("movl %%eax, %0\n" :"=r"(myval));
+---+--------------------+
| r |    Register(s)     |
+---+--------------------+
| a |   %eax, %ax, %al   |
| b |   %ebx, %bx, %bl   |
| c |   %ecx, %cx, %cl   |
| d |   %edx, %dx, %dl   |
| S |   %esi, %si        |
| D |   %edi, %di        |
+---+--------------------+

## Memory operand constraint(m)
When the operands are in the memory, any operations performed on them will occur directly in the memory location, not through register
asm("sidt %0\n" : :"m"(loc));

## Matching(Digit) constraints
a single variable may serve as both the input and the output operand. Such cases may be specified in "asm" by using matching constraints.
asm ("incl %0" :"=a"(var):"0"(var));
"=a" means eax as output register
"0" here specifies the same constraint as the 0th output variable

## Some other constraints used are:
"m" : A memory operand is allowed, with any kind of address that the machine supports in general.
"o" : A memory operand is allowed, but only if the address is offsettable. ie, adding a small offset to the address gives a valid address.
"V" : A memory operand that is not offsettable. In other words, anything that would fit the `m’ constraint but not the `o’constraint.
"i" : An immediate integer operand (one with constant value) is allowed. This includes symbolic constants whose values will be known only at assembly time.
"n" : An immediate integer operand with a known numeric value is allowed. Many systems cannot support assembly-time constants for operands less than a word wide. Constraints for these operands should use ’n’ rather than ’i’.
"g" : Any register, memory or immediate integer operand is allowed, except for registers that are not general registers.

## x86 specific constraints
"r" : Register operand constraint, look table given above.
"q" : Registers a, b, c or d.
"I" : Constant in range 0 to 31 (for 32-bit shifts).
"J" : Constant in range 0 to 63 (for 64-bit shifts).
"K" : 0xff.
"L" : 0xffff.
"M" : 0, 1, 2, or 3 (shifts for lea instruction).
"N" : Constant in range 0 to 255 (for out instruction).
"f" : Floating point register
"t" : First (top of stack) floating point register
"u" : Second floating point register
"A" : Specifies the `a’ or `d’ registers. This is primarily useful for 64-bit integer values intended to be returned with the `d’ register holding the most significant bits and the `a’ register holding the least significant bits.

# Constraint Modifiers
"=" : Means that this operand is write-only for this instruction; the previous value is discarded and replaced by output data.
"&" : Means that this operand is an early clobber operand, which is modified before the instruction is finished using the input operands. Therefore, this operand may not lie in a register that is used as an input operand or as part of any memory address. An input operand can be tied to an earlyclobber operand if its only use as an input occurs before the early result is written.

