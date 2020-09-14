BITS 64

section .data

iter1 dd 0		; iterator 1
iter2 dd 0		; iterator 2
arg_a dq 0		; argument 1
arg_b dq 0		; argument 2
r_pointer dq 0		; substring pointer

section .bss

section .text
        global asm_strstr

; string compare funciton
asm_strstr:
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
	mov r12, 0		; set to 0 the r12 register

count_c:			; start loop
	inc dword [iter1]	; increment by 1 the iterator 1
	mov r11d, [iter1]	; copy the iter value to r11

	mov rcx, 0		; set to 0 the rbx register
	mov cl, [rsi + r12]	; set a single byte to rcx register
	cmp cl, 0x00		; compare the previous byte with null char
	je equ_c                ; if they are the same go out because a haystack

	mov rbx, 0		; set to 0 the rbx register
	mov bl, [rdi + r11 - 1]	; set a single byte to rbx register
	cmp bl, 0x00		; compare the previous byte with null char
	je next_c		; if they are the same go out because any haystack was found

	cmp bl, cl		; if not, compare the first arg byte with the second arg byte
	je inc_arg_2		; if they are equal continue the comparison
	mov r12, 0		; else set the comparison arg2 from begining
	jne count_c		; and continue the loop

next_c:				; else go out of loop
	mov rax, 0		; set return value to 0

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

equ_c:				; if they are equal set the pointer to that byte
	mov rax, [r_pointer]	; set the pointer in return value
	jmp end_c		; end program

inc_arg_2:			; increment the byte comparison
	cmp r12, 0x00		; if it is the first byte of the substring
	je save_p		; save the begining of substring

inc_next:			; increment the iterator of the 2nd substring
	inc dword [iter2]	; increment by 1
	mov r12d, [iter2]	; and paste in the register
	jmp count_c		; come back to the funtion was call

save_p:				; save the beginig of substring
	dec r11			; set the right index to the substring
	mov r12, rdi		; copy the arg1 pointer
	add r12, r11		; add the offset pointer
	mov [r_pointer], r12	; save in memory
	inc r11			; set back the iterator 1
	mov r12, 0		; set back the iterator 2
	jmp inc_next		; come back to the function was call
