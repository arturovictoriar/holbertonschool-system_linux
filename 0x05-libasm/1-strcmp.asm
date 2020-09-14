BITS 64

section .data

section .bss

section .text
        global asm_strcmp

; string compare funciton
asm_strcmp:
        push rbp                ; prologue
        mov rbp, rsp
        push rbx                ; save rbx value in stack
        push rcx                ; save rcx value in stack
	push rdx		; save rdx value in stack
	push r8

        mov rbx, rdi            ; save the 1st arg in rbx register
        mov rcx, rsi		; start the 2nd arg in rcx register
	mov rdx, 0		; start the iterator in 0
count_c:                        ; for statement
	inc rdx			; increment the iterator
	mov r8b, byte [rcx + rdx - 1]	; check if the char in arg1
	cmp r8b, byte 0x00		; is not a null char
	je next_c			; if it is go out of for loop
	mov r8b, byte [rbx + rdx - 1]	; check if the char in arg2
	cmp r8b, byte 0x00		; is not a null char
	je next_c			; if it is go out of for loop
        cmp r8b, byte [rcx + rdx - 1]	; check if char in arg1 is eql to char in arg2
        je count_c			; if it is, continue in the for loop
next_c:					; end lopp
	mov rax, 0			; set the return value in 0
	push qword [rbx + rdx - 1]	; push the last char arg1 compared before on stack
	push qword [rcx + rdx - 1]	; push the last char arg2 compared before on stack
	mov rbx, 0			; set the reg in 0
	mov rcx, 0			; set the reg in 0
	mov bl, byte [rsp + 8]		; set the last char value arg1 in a variable
	mov cl, byte [rsp]		; set the last char value arg2 in a variable
	cmp rbx, rcx			; compare the previous variables
	je eq_c				; if are the same set return value in 0
	jg pos_c			; if rbx is greater than rcx set the return value in 1
	jl neg_c			; if rbx is less than rcx set the return value in -1

eq_c:				; set the return value in 0
	mov rax, 0
	jmp end_c		; go to the end program

neg_c:				; set the return value in -1
	mov rax, -1
	jmp end_c		; go to the end program

pos_c:				; set the return value in 1
	mov rax, 1
	jmp end_c		; go to the end program
end_c:
	pop rdx
	pop rcx

	pop r8			; set back the previous value of r8
	pop rdx			; set back the previous value of rdx
        pop rcx                 ; set the rcx register with its old value
        pop rbx                 ; set the rbx register with its old value
        mov rsp, rbp            ; epilogue
        pop rbp			; set back the previous value of rbp
        ret                     ; return the len value
