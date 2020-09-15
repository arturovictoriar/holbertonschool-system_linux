BITS 64

section .data

section .bss

section .text
        global asm_strncasecmp

; string compare funciton
asm_strncasecmp:
        push rbp                	; prologue
        mov rbp, rsp
	push rdx			; save rdx value in stack
	push r11			; save r11 value in stack
	push r12			; save r12 value in stack
	push r13

	mov r13, rdx			; save 3rd arg
	mov rdx, 0			; start the iterator in 0
	mov r11, 0			; start the registeer compator 0
	mov r12, 0			; start the registeer compator 0
count_c:                        	; for statement
	inc rdx				; increment the iterator
	cmp r13, rdx			; if iterator == n
	je next_c			; break

	mov r12b, byte [rsi + rdx - 1]	; check if the char in arg1
	mov r11b, byte [rdi + rdx - 1]  ; check if the char in arg2

	cmp r12b, 65			; convert from uppercase to lowercase
	jl next_count1			; if the byte is in uppercase
	cmp r12b, 91
	jl conv_lower_arg1

next_count1:
	cmp r11b, 65			; convert from uppercase to lowercase
	jl next_count2			; if the byte is in uppercase
	cmp r11b, 91
	jl conv_lower_arg2

next_count2:
        cmp r12b, 0x00                  ; is not a null char
        je next_c                       ; if it is go out of for loop
        cmp r11b, 0x00                  ; is not a null char
        je next_c                       ; if it is go out of for loop

        cmp r11b, r12b			; check if char in arg1 is eql to char in arg2
        je count_c			; if it is, continue in the for loop
next_c:					; end lopp
	mov rax, 0			; set the return value in 0
	mov rax, r11			; compare the previous variables
	sub rax, r12

	pop r13
	pop r12
	pop r11				; set back the previous value of r8
	pop rdx				; set back the previous value of rdx
        mov rsp, rbp            	; epilogue
        pop rbp				; set back the previous value of rbp
        ret                     	; return the len value

conv_lower_arg1:			; convert from uppercase to lowercase
	add r12b, 32
	jmp next_count1

conv_lower_arg2:			; convert from uppercase to lowercase
	add r11b, 32
        jmp next_count2
