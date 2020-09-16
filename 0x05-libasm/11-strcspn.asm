BITS 64

section .data

section .bss

section .text
	global asm_strcspn

; string length funciton
asm_strcspn:
	push rbp		; prologue
	mov rbp, rsp

	push rbx		; save rbx value in stack
	push rcx		; save rcx value in stack
	push r11		; save r11 value in stack

	mov rcx, 0		; start in 0 the rcx register
	mov r11, 0		; start in 0 the r11 register

count_c1:				; for statement
	cmp byte [rdi + rcx], 0x00	; compare each character of arg with caracter null
	je end_c			; if the char in arg is not = to caracter null continue in for

	mov rbx, 0			; set the iterator in 0
count_c2:				; second for
	mov r11b, [rsi + rbx]		; if accept byte is null
	cmp r11b, 0x00			; continue the first loop
	je count_c3			; continue the first loop

	inc rbx				; else increase the iterator
	cmp r11b, [rdi + rcx]		; if accept byte != to the byte in arg1
	je end_c			; break both loop and end program
	jmp count_c2			; continue the 2nd loop

count_c3:
	inc rcx				; else increment the length of arg1
	jmp count_c1			; continue the for

end_c:
	mov rax, rcx		; set the len in the return value

	pop r11			; set the r11 register with its old value
	pop rcx			; set the rcx register with its old value
	pop rbx			; set the rbx register with its old value

	mov rsp, rbp		; epilogue
	pop rbp
	ret			; return the len value
