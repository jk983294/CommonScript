section .data
    msg	db "hello, world!",`\n`

section .text
    global _start
_start:
    mov     rax, 1      ; syscall number
    mov     rdi, 1      ; fd
    mov     rsi, msg    ; buf
    mov     rdx, 14     ; count
    syscall             ; size_t sys_write(unsigned int fd, const char * buf, size_t count);
    mov    rax, 60      ; syscall number
    mov    rdi, 0       ; exit value
    syscall             ; exit(code);