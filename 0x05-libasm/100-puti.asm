BITS 64

section .data

arg1 dd 0
neg_num dd 0

section .bss

section .text
        global asm_puti
	extern asm_putc

; string length funciton
asm_puti:
       	push rbp
	mov rbp, rsp
	push r11
	push rdx
	push rcx
	push rdi

	mov rcx, 0
	mov [arg1], rdi
	cmp dword [arg1], 0
	jl set_neg
	je print_1

get_dig:
	cmp dword [arg1], 0
	je ret_val

	mov rdi, 10
	mov rdx, 0
	mov rax, 0
	mov eax, [arg1]
	div rdi
	mov [arg1], eax

	mov rdi, 0
	mov rdi, rdx
	add rdi, 48
	call asm_putc

	inc rcx
	inc dword [neg_num]
	jmp get_dig

ret_val:
	mov rax, 0
	mov rax, qword [neg_num]

end_c:
	pop rdi
	pop rcx
	pop rdx
	pop r11
	mov rsp, rbp
	pop rbp
        ret

set_neg:
	mov rdi, 45
	call asm_putc
	inc dword [neg_num]
	mov rdi, -1
	mov rax, 0
	mov rax, [arg1]
	imul rdi
	mov [arg1], eax
	jmp get_dig

print_1:
	mov rdi, 48
	call asm_putc
	jmp end_c
