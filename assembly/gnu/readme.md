### data section
```gas
.section .data
    var1: .byte 10      // 1 byte
    var2: .word 10      // 2 byte
    var3: .int 10       // 4 byte
    var4: .quad 10      // 8 byte
    var5: .octa 10      // 16 byte

    // assembles each string (with no automatic trailing zero byte) into consecutive addresses
    str1: .asci "Hello world"
    // just like .ascii, but each string is followed by a zero byte
    str2: .asciz "Hello world"
    // Copy the characters in str to the object file
    str3: .string "Hello world"
```

### text section
```gas
	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"Hello World\n"
	.text
	.globl	main
	.type	main, @function

main:
.LFB0:
	// code
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.9.1-16ubuntu6) 4.9.1"
	.section	.note.GNU-stack,"",@progbits
```

### code
```gas
mov source, destination
mov %rcx, %rax
```

### post fix for instruction
```gas
movw (%rsi), %ax
```
* b - 1 byte operands
* w - 2 bytes operands
* l - 4 bytes operands
* q - 8 bytes operands
* t - 10 bytes operands
* o - 16 bytes operands

### Memory access
```gas
movq -8(%rbp), %rdi
movq 8(%rbp), %rdi
```

### jumps
```gas
lcall $section, $offset
```

### Comments
```gas
# - single line comments
// - single line comments
/* */ - for multiline comments
```
