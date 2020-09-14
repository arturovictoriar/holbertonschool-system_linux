BITS 64

section .data

section .bss

section .text
        global asm_puts

; string length funciton
asm_puts:
        push rbp                ; Setup stack frame
	mov rbp, rsp            ; Those two lines are equivalent to 'enter'

	push rbx		; save rbx value
	push rdi                ; store the arg1 value

	mov rax, 0		; set 0 the return value
	call asm_strlen		; call the function asm_strlen
	mov rbx, rax		; save the return value

	mov rax, 1              ; Write syscall
	mov rdi, 1              ; write to stdout
	mov rsi, rsp            ; Address of the character to be printed (Address of the stack)
	mov rdx, rbx		; Write strlen bytes
	syscall                 ; call the syscall

	mov rax, rbx            ; return value printd

	pop rdi                 ; set back the previos value
	pop rbx			; set back the previos value
	mov rsp, rbp            ; Restore previous stack frame
	pop rbp                 ; Those two lines are equivalent to 'leave'
        ret			; return
