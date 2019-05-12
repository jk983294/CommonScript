section .data
	SYS_WRITE	equ 1
	STD_OUT		equ 1
	SYS_EXIT	equ 60
	EXIT_CODE	equ 0

	NEW_LINE	db 0xa
	WRONG_ARGC	db "Must be two command line argument", 0xa

section .text
	global	_start

_start:
    ;; [rsp] - top of stack will contain arguments count.
    ;; [rsp + 8] - will contain argv[0]
    ;; [rsp + 16] - will contain argv[1]
    ;; and so on
	pop	rcx             ; rcx = argc
	cmp	rcx, 3          ; Check argc
	jne	argcError

	;;
	;; start to sum arguments
	;;

	add	rsp, 8          ; skip argv[0] - program name
	pop	rsi             ; rsi = argv[1]
	call	str_to_int  ; convert argv[1] str to int
	mov	r10, rax        ; put first num to r10
	pop	rsi             ; rsi = argv[2]
	call	str_to_int  ; convert argv[2] str to int
	mov	r11, rax        ; put second num to r10
	add	r10, r11        ; r10 = argv[1] + argv[2]

	;;
	;; Convert to string
	;;
	mov	rax, r10
	xor	r12, r12        ; len = 0
	jmp	int_to_str      ; convert to string

;;
;; Print argc error
;;
argcError:
	mov	rax, 1          ; sys_write syscall
	mov	rdi, 1          ; file descritor, standard output
	mov	rsi, WRONG_ARGC ; message address
	mov	rdx, 34         ; length of message
	syscall             ; call write syscall
	jmp	exit            ; exit from program


;;
;; Convert int to string, input is rax,
;; output:
;;     r12 which is string length
;;     stack keeps char array
;;
int_to_str:
	mov	rdx, 0          ; rdx = 0; reminder from division
	mov	rbx, 10         ; rbx = 10; base
	div	rbx             ; rax = rax / 10
	add	rdx, 48         ; rax = rdx + '0'
	push	rdx         ; push reminder to stack
	inc	r12             ; len++;
	cmp	rax, 0x0        ; if(rax != 0)
	jne	int_to_str      ;    loop again
	jmp	print           ; else { print result }

;;
;; Convert string to int, input is in rsi, output is in rax
;;
str_to_int:
	xor	rax, rax            ; rax = 0; it is accumulator
	mov	rcx,  10            ; base for multiplication
next:
	cmp	[rsi], byte 0       ; if(*pStr == NULL)
	je	return_str
	; else
	mov	bl, [rsi]           ; mov current char to bl
	sub	bl, 48              ; bl -= '0'
	mul	rcx                 ; rax = rax * 10
	add	rax, rbx            ; rax = rax + bl
	inc	rsi                 ; ++pStr
	jmp	next

return_str:
	ret


;;
;; Print number
;; input is char array in stack and r12 keeps string length
;;
print:
	;;;; calculate number length
	mov	rax, 1
	mul	r12                 ; rax = 1 * r12
	mov	r12, 8
	mul	r12                 ; rax *= 8 ??? We must multiple it to 8 (because we pushed every symbol to stack)
	mov	rdx, rax            ; rdx = rax, which is length
	;;;;

	;;;; print sum
	mov	rax, SYS_WRITE
	mov	rdi, STD_OUT
	mov	rsi, rsp
	syscall                 ; call sys_write

	jmp	printNewline

;;
;; Print number
;;
printNewline:
	mov	rax, SYS_WRITE
	mov	rdi, STD_OUT
	mov	rsi, NEW_LINE
	mov	rdx, 1
	syscall
	jmp	exit

;;
;; Exit from program
;;
exit:
	mov	rax, SYS_EXIT       ; syscall number
	mov	rdi, EXIT_CODE      ; exit code
	syscall                 ; call sys_exit
