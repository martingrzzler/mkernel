section .asm

global gdt_load

gdt_load:
	mov eax, [esp+4] ; struct gdt starting address
	mov [gdt_descriptor+2], eax ; set starting address
	mov ax, [esp+8] ; size
	mov [gdt_descriptor], ax ; set the size
	lgdt [gdt_descriptor] ; load GDT
	ret

section .data
gdt_descriptor:
	dw 0x00 ; Size
	dd 0x00 ; gdt start address