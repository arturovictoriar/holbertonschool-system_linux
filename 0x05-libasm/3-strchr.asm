BITS 64

section .data

iter dd 0		; iterator
arg_a dq 0		; argument 1
arg_b dd 0		; argument 2

section .bss

section .text
        global asm_strchr

; string compare funciton
asm_strchr:
        push rbp                ; prologue
        mov rbp, rsp
	push rbx		; save current rbx value
	push rcx		; save current rcx value
	push r11		; save current r11 value

        mov [arg_a], rdi	; save the 1st arg in arg_a memory
        mov [arg_b], esi	; start the 2nd arg in arg_b memory
	mov [iter], dword 0 	; start the iterator in 0
	mov rcx, [arg_a]	; dereferencing the double pointer to rcx
count_c:			; start loop
	inc dword [iter]	; increment by 1 the iterator
	mov r11, 0		; set to 0 the r11 register
	mov r11d, [iter]	; copy the iter value to r11
	mov rbx, 0		; set to 0 the rbx register
	mov bl, [rcx + r11 - 1]	; set a single byte to rbx register
	cmp bl, 0x00		; compaere the previous byte with null char
	je next_c		; if they are the same go out the loop
	cmp bl, [arg_b]		; if not, compare the byte with the second arg value
	jne count_c		; if they are not equal continue the loop
next_c:				; else go out of loop
	mov rax, 0		; set return value to 0
	cmp ebx, [arg_b]	; compare the byte with second arg value
	je equ_c		; if they are equal set the pointer to that byte
end_c:				; end
	pop r11			; set back the previous value of r11
	pop rcx			; set back the previous value of rcx
	pop rbx			; set back the previous value of rbx
        mov rsp, rbp            ; epilogue
        pop rbp			; set back the previous value of rbp
        ret                     ; return the len value

equ_c:				; if they are equal set the pointer to that byte
	dec r11			; set the right index
	add rcx, r11		; add the index in memory from the first byte
	mov rax, rcx		; set the pointer in return value
	jmp end_c		; end program
