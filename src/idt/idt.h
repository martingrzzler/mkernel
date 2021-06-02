#ifndef IDT_H
#define IDT_H
#include <stdint.h>

struct idt_desc
{
  uint16_t offset_1; // Offset bits 0 - 15
  uint16_t selector; // a code segment selector in GDT or LDT
  uint8_t zero;      // unused, set to 0
  uint8_t type_attr; // type and attributes
  uint16_t offset_2; // offset bits 16 - 31
} __attribute__((packed));

struct idtr_desc
{
  uint16_t limit; // size of idt - 1
  uint32_t base;  // Base address of the start of the table
} __attribute__((packed));

void idt_init();
void enable_interrupts();
void disable_interrupts();
#endif