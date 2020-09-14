BITS 64

section .data

iter1 dd 0		; iterator 1
arg_a dq 0		; argument 1
arg_b dq 0		; argument 2
arg_c dd 0		; argument 3

section .bss

section .text
        global asm_memcpy

; copies memory area funciton
asm_memcpy:
        push rbp                ; prologue
        mov rbp, rsp
	push rbx		; save current rbx value
	push rcx		; save current rcx value

        mov [arg_a], rdi	; save the 1st arg in arg_a memory
        mov [arg_b], rsi	; start the 2nd arg in arg_b memory
	mov [arg_c], rdx	; start the 3th arg in arg_b memory
	mov [iter1], dword 0 	; start the iterator 1 in 0
	mov r11, 0		; set to 0 the r11 register
	mov rcx, 0		; set to 0 the rcx register
	mov rbx, 0              ; set to 0 the rbx register

count_c:			; start loop
	cmp r11, rdx		; if i >= n
	jge next_c		; break

	mov bl, [rsi + r11]	; set a single byte to rbx register
	cmp bl, 0x00            ; compare the previous byte with null char
	je next_c               ; if they are the same go out because any haystack was found

	mov byte [rdi + r11], bl; copy a byte in a specfic pointer

	inc dword [iter1]	; increment by 1 the iterator 1
	mov r11d, [iter1]	; copy the iter value to r11

	jmp count_c		; continue in loop

next_c:				; else go out of loop
	cmp r11, rdx		; if i < n
	jl fill_z		; fill zeros
next_f:
	mov rax, rdi		; set return value to 0

end_c:				; end
	mov rdi, [arg_a]	; set back the previous value of rdi
	mov rsi, [arg_b]	; set back the previous value of rsi
	pop rcx			; set back the previous value of rcx
	pop rbx			; set back the previous value of rbx
        mov rsp, rbp            ; epilogue
        pop rbp			; set back the previous value of rbp
        ret                     ; return the len value

fill_z:				; fill zeros
	cmp r11, rdx		; if i >= n
	jge next_f		; break

	mov byte [rdi + r11], cl; copy a byte in a specfic pointer

	inc dword [iter1]       ; increment by 1 the iterator 1
	mov r11d, [iter1]       ; copy the iter value to r11

	jmp fill_z		; end program
