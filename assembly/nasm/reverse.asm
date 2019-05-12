;;
;; initialized data
;;
section .data
	SYS_WRITE	equ 1
	STD_OUT		equ 1
	SYS_EXIT	equ 60
	EXIT_CODE	equ 0

	NEW_LINE	db 0xa      ; '\n'
	INPUT		db "Hello world!"

;;
;; non initialized data
;;
section .bss
	OUTPUT	resb 1          ; buffer where put reversed string

;;
;; code
;;
section .text
	global	_start

;;
;; main routine
;;
_start:
	mov	rsi, INPUT          ; rsi = &INPUT
	xor	rcx, rcx            ; count = 0
	cld                     ; df = 0 si++
	mov	rdi, $ + 15         ; 15 = following two instruction's length, rdi = &(xor	rax, rax)
	call	calculateStrLength
	xor	rax, rax            ; rax = 0
	xor	rdi, rdi            ; count1 = 0
	jmp	reverseStr

;;
;; calculate length of string, output is rcx, we also push string into stack, prepare to pop it out into STDOUT
;;
calculateStrLength:
	cmp	byte [rsi], 0       ; if( *rsi == NULL )
	je	exitFromRoutine
	;                       ; else {
	lodsb                   ;     al = *rsi; ++rsi;   // this affacted by df = 0 i.e. cld instruction
	push	rax             ;     push symbol to stack
	inc	rcx                 ;     ++count
	jmp	calculateStrLength  ; }

;;
;; back to _start
;;
exitFromRoutine:
	push	rdi             ; push return addres to stack again
	ret                     ; return to _start

;;
;; reverse string
;;
reverseStr:
	;; check is it end of string
	cmp	rcx, 0              ; if ( count == 0 )
	je	printResult         ; { printResult }
	pop	rax                 ; else { ch = rax;
	mov	[OUTPUT + rdi], rax ;        *(OUTPUT + count1) = ch;
	dec	rcx                 ;        --count;
	inc	rdi                 ;        ++count1;  // increase additional length counter (for write syscall)
	jmp	reverseStr          ; }

;;
;; Print result string
;;
printResult:
	mov	rdx, rdi
	mov	rax, 1
	mov	rdi, 1
	mov	rsi, OUTPUT
	syscall
	jmp	printNewLine

;;
;; Print number
;;
printNewLine:
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