BITS 64

section .data

section .bss

section .text
        global asm_strncmp

; string compare with a specif number compare funciton
asm_strncmp:
        push rbp                ; prologue
        mov rbp, rsp
        push rbx                ; save rbx value in stack
        push rcx                ; save rcx value in stack
	push r11		; save r11x value in stack
	push r12		; save r12x value in stack
	push r13		; save r12x value in stack

        mov rbx, rdi            ; save the 1st arg in rbx register
        mov rcx, rsi		; save the 2nd arg in rcx register
	mov r11, rdx		; save the 3rd arg in rdx register
	mov r12, 0		; start the iterator in 0
count_c:                        ; for statement
	inc r12			; increment the iterator by 1
	cmp r12, r11		; check if the iterator is greather than the 3rd arg
	jg next_a		; if it end the loop and decrease the iterator by 1
	mov r13b, byte [rcx + r12 - 1]	;
	cmp r13b, byte 0x00		; is not a null char
	je next_c			; if it is go out of for loop
	mov r13b, byte [rbx + r12 - 1]	; check if the char in arg2
	cmp r13b, byte 0x00		; is not a null char
	je next_c			; if it is go out of for loop
        cmp r13b, byte [rcx + r12 - 1]	; check if char in arg1 is eql to char in arg2
        je count_c			; if it is, continue in the for loop

next_c:					; end lopp
	mov rax, 0			; set the return value in 0
	push qword [rbx + r12 - 1]	; push the last char arg1 compared before on stack
	push qword [rcx + r12 - 1]	; push the last char arg2 compared before on stack
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

	pop r13			; set back the previous value of r13
	pop r12			; set back the previous value of r12
	pop r11			; set back the previous value of r11
        pop rcx                 ; set the rcx register with its old value
        pop rbx                 ; set the rbx register with its old value
        mov rsp, rbp            ; epilogue
        pop rbp			; set back the previous value of rbp
        ret                     ; return the len value

next_a:				; set the iter in the last position of str
	dec r12
	jmp next_c		; compare the last 2 char args
