BITS 64

section .data

iter1 dd 0		; iterator 1
iter2 dd 0		; iterator 2
arg_a dq 0		; argument 1
arg_b dq 0		; argument 2

section .bss

section .text
        global asm_strpbrk

; string compare funciton
asm_strpbrk:
        push rbp                ; prologue
        mov rbp, rsp
	push rbx		; save current rbx value
	push rcx		; save current rcx value
	push r12		; save current r12 value
	push r11		; save current r11 value

        mov [arg_a], rdi	; save the 1st arg in arg_a memory
        mov [arg_b], rsi	; start the 2nd arg in arg_b memory
	mov [iter1], dword 0 	; start the iterator 1 in 0
	mov [iter2], dword 0	; start the iterator 2 in 0
	mov r11, 0		; set to 0 the r11 register

count_c1:			; start loop
	mov rbx, 0		; set to 0 the rbx register
	mov bl, [rdi + r11]	; set a single byte to rbx register
	cmp bl, 0x00		; compare the previous byte with null char
	je next_c1		; if they are the same go out because any haystack was found

	mov r12, 0              ; set to 0 the r12 register
	mov dword [iter2], r12d	; set to 0 the iter2 variable
count_c2:
	mov rcx, 0              ; set to 0 the rbx register
	mov cl, [rsi + r12]     ; set a single byte to rcx register
	cmp cl, 0x00            ; compare the previous byte with null char
	je count_c3             ; if they are the same go out because a haystack

	inc dword [iter2]       ; increment by 1 the iterator 2
	mov r12d, [iter2]       ; copy the iter value to r12
	cmp bl, cl		; if not, compare the first arg byte with the second arg byte
	je next_c2		; if they are equal set the pointer
	jmp count_c2		; else continue the second loop

count_c3:
	inc dword [iter1]       ; increment by 1 the iterator 1
	mov r11d, [iter1]       ; copy the iter value to r11
	jmp count_c1		; and continue the loop

end_c:				; end
	mov rdi, [arg_a]	; set back the previous value of rdi
	mov rsi, [arg_b]	; set back the previous value of rsi

	pop r11			; set back the previous value of r11
	pop r12			; set back the previous value of r12
	pop rcx			; set back the previous value of rcx
	pop rbx			; set back the previous value of rbx
        mov rsp, rbp            ; epilogue
        pop rbp			; set back the previous value of rbp
        ret                     ; return the len value

next_c1:                        ; null value
        mov rax, 0              ; set return value to 0
	jmp end_c		; return value

next_c2:			; pointer value
	add rdi, r11		; from the begining of the string
	mov rax, rdi		; get the index wiht the right value
	jmp end_c		; return value
