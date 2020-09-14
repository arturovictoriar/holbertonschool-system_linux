BITS 64

section .data

section .bss

section .text
	global asm_strlen

; string length funciton
asm_strlen:
	push rbp		; prologue
	mov rbp, rsp
	push rbx		; save rbx value in stack
	push rcx		; save rcx value in stack
	mov rbx, rdi		; save the 1st arg in rbx register
	mov rcx, 0		; start in 0 the lenth arg in rcx register
count_c:			; for statement
	inc rcx			; incremet len by one
	cmp byte [rbx + rcx - 1], 0x00	; compare each character of arg with caracter null
	jne count_c		; if the char in arg is not = to caracter null continue in for
	dec rcx			; else decrement 1 the length to sub the null character
	mov rax, rcx		; set the len in the return value
	pop rcx			; set the rcx register with its old value
	pop rbx			; set the rbx register with its old value
	mov rsp, rbp		; epilogue
	pop rbp
	ret			; return the len value
