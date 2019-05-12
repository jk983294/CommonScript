section .data
    num1:   equ 100
    num2:   equ 50
    msg:	db "Sum is correct", 10

section .text
    global _start

;; entry point
_start:
    mov rax, num1       ; rax = num1
    mov rbx, num2       ; rbx = num2
    add rax, rbx        ; rax += rbx
    cmp rax, 150        ; if(rax != 150)
    jne .exit           ;     exit()
    jmp .rightSum       ; else rightSum()

; Print message that sum is correct
.rightSum:
    mov     rax, 1      ; write syscall
    mov     rdi, 1      ; file descritor, standard output
    mov     rsi, msg    ; message address
    mov     rdx, 15     ; length of message
    syscall ; size_t sys_write(unsigned int fd, const char * buf, size_t count);
    jmp .exit           ; exit()

; exit procedure
.exit:
    mov    rax, 60      ; syscall number
    mov    rdi, 0       ; return value
    syscall             ; exit(code);