[BITS 32]

section .asm
global _start

_start:

_loop:
	call getKey
	push eax
	mov eax, 3
	int 0x80
	add esp, 4
	jmp _loop

getKey:
	mov eax, 2 ; Command getKey
	int 0x80
	cmp eax, 0x00
	je getKey
	ret

section .data
message: db 'Hello World from User Land', 0