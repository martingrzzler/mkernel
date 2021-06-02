section .asm
extern int21h_handler 
extern no_interrupt_handler

global idt_load
global int21h
global no_interrupt
global enable_interrupts
global disable_interrupts

enable_interrupts:
  sti
  ret

disable_interrupts:
  cli
  ret

idt_load:
  push ebp
  mov ebp, esp

  mov ebx, [ebp+8] ; the first argument passed into the function
  lidt [ebx] ; instruction to load the IDT

  pop ebp
  ret

int21h: ;keyboard interrupt is usually 1 but since the remapping to 0x20 happned it is now 21
  cli
  pushad
  call int21h_handler 
  popad
  sti
  iret

no_interrupt: ;keyboard interrupt is usually 1 but since the remapping to 0x20 happned it is now 21
  cli
  pushad
  call no_interrupt_handler 
  popad
  sti
  iret
