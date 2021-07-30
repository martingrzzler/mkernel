[BITS 32]

section .asm

global print:function ; function ensures that elf symbol type is of function
global os_getKey:function
global os_malloc:function
global os_free:function
global os_putchar:function
global os_process_load_start:function
global os_process_get_arguments:function
global os_system:function
global os_exit:function

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

os_process_load_start:
	push ebp
	mov ebp, esp
	mov eax, 6 ; command start a process by filename
	push dword[ebp+8] ; filename
	int 0x80
	add esp, 4
	pop ebp
	ret

; int os_system(struct command_arguments* arguments)
os_system:
	push ebp
	mov ebp, esp
	mov eax, 7 ; command for invoking system command
	push dword[ebp+8]
	int 0x80
	add esp, 4
	pop ebp
	ret


;  void os_process_get_arguments(struct process_arguments* arguments)
os_process_get_arguments:
	push ebp
	mov ebp, esp
	mov eax, 8 ; get args command
	push dword[ebp+8]
	int 0x80
	add esp, 4
	pop ebp
	ret

; void os_exit()
os_exit:
	push ebp
	mov ebp, esp
	mov eax, 9 ; exit command
	int 0x80
	pop ebp
	ret




