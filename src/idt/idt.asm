section .asm

global idt_load

idt_load:
  push ebp
  mov ebp, esp

  mov ebx, [ebp+8] ; the first argument passed into the function
  lidt [ebx] ; instruction to load the IDT

  pop ebp
  ret