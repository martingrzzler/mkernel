[BITS 32]

section .asm

global print:function ; function ensures that elf symbol type is of function
global os_getKey:function
global os_malloc:function
global os_free:function
global os_putchar:function

; void print(const char* filename)
print:
	push ebp
	mov ebp, esp
	push dword[ebp+8]
	mov eax, 1 ; command print
	int 0x80
	add esp, 4
	pop ebp
	ret

os_getKey:
	push ebp
	mov ebp, esp
	mov eax, 2 ; getKey command
	int 0x80
	pop ebp
	ret

os_putchar:
	push ebp
	mov ebp, esp
	mov eax, 3 ; putchar command
	push dword[ebp+8]
	int 0x80
	add esp, 4
	pop ebp
	ret

os_malloc:
	push ebp
	mov ebp, esp
	mov eax, 4 ; command malloc
	push dword[ebp+8]
	int 0x80
	add esp, 4
	pop ebp
	ret 

os_free:
	push ebp
	mov ebp, esp
	mov eax, 5 ; command free
	push dword[ebp+8] ; ptr
	int 0x80
	add esp, 4
	pop ebp
	ret