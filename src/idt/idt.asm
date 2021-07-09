section .asm
extern int21h_handler 
extern no_interrupt_handler
extern isr80h_handler
extern interrupt_handler

global idt_load
global no_interrupt
global enable_interrupts
global disable_interrupts
global isr80h_wrapper
global interrupt_pointer_table

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

no_interrupt: ;keyboard interrupt is usually 1 but since the remapping to 0x20 happned it is now 21
  pushad
  call no_interrupt_handler 
  popad
  iret

%macro interrupt 1
  global int%1
  int%1:
    pushad
    push esp
    push dword %1
    call interrupt_handler
    add esp, 8 
    popad
    iret
%endmacro

%assign i 0
%rep 512
  interrupt i
%assign i i+1 
%endrep

isr80h_wrapper:
  ; Interrupt frame start
  ; Peocessor will already have pushed some registers to the stack(ip,cs,flags,sp,ss)
  pushad ; push general purpose registers
  ;Interrupt frame end

  push esp ; push stack pointer so that we are pointing to interrrupt frame
  push eax ; holds command number and must be accessed by handler
  call isr80h_handler
  mov dword[tmp_res], eax ; hold return value
  add esp, 8 ; moves stack pointer back to previous position
  popad ; restore general purpose registers for user land
  mov eax, [tmp_res]
  iretd

section .data
; stores return value of isr80h_handler
tmp_res: dd 0

%macro interrupt_array_entry 1
  dd int%1
%endmacro

interrupt_pointer_table:
%assign i 0 
  %rep 512
    interrupt_array_entry i
  %assign i i+1
%endrep



