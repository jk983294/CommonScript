extern printResult

section .data
	radius		dq  1.7
	result		dq  0

	SYS_EXIT	equ 60
	EXIT_CODE	equ 0

section .text
	global	_start

_start:
	fld	qword [radius]          ; st0 = radius
	fld	qword [radius]          ; st1 = radius
	fmul                        ; st0 = st0 * st1

	fldpi                       ; st1 = pi
	fmul                        ; st0 = st0 * st1
	fstp	qword [result]      ; result = st0

	mov	rax, 0
	movq	xmm0, [result]
	call	printResult

	mov	rax, SYS_EXIT
	mov	rdi, EXIT_CODE
	syscall