#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "memory/memory.h"
#include "disk/disk.h"
#include "disk/streamer.h"
#include "fs/pparser.h"
#include "string/string.h"
#include "task/tss.h"
#include "fs/file.h"
#include "task/task.h"
#include "isr80h/isr80h.h"
#include "task/process.h"
#include "gdt/gdt.h"
#include "status.h"
#include "config.h"
uint16_t *video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

// color must be put before char ascii code because of endiness
uint16_t terminal_make_char(char c, char color)
{
  return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, int color)
{
  video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, color);
}

void terminal_writechar(char c, char color)
{
  if (c == '\n')
  {
    terminal_row += 1;
    terminal_col = 0;
    return;
  }

  terminal_putchar(terminal_col, terminal_row, c, color);
  terminal_col += 1;
  if (terminal_col >= VGA_WIDTH)
  {
    terminal_col = 0;
    terminal_row += 1;
  }
}

void terminal_initialize()
{
  video_mem = (uint16_t *)(0xB8000);
  terminal_row = 0;
  terminal_col = 0;
  for (int y = 0; y < VGA_HEIGHT; y++)
  {
    for (int x = 0; x < VGA_WIDTH; x++)
    {
      terminal_putchar(x, y, ' ', 0);
    }
  }
}

void print(const char *str)
{
  size_t len = strlen(str);
  for (int i = 0; i < len; i++)
  {
    terminal_writechar(str[i], TERMINAL_WHITE);
  }
}
static struct paging_4gb_chunk *kernel_chunk = 0;

void panic(const char *msg)
{
  print(msg);
  while (1)
  {
  };
}
void kernel_page()
{
  kernel_registers();
  paging_switch(kernel_chunk);
}
struct tss tss;
struct gdt gdt_real[TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[TOTAL_GDT_SEGMENTS] =
    {
        {.base = 0x00, .limit = 0x00, .type = 0x00},                 // NULL Segment
        {.base = 0x00, .limit = 0xffffffff, .type = 0x9A},           // Kernel Code Segment,
        {.base = 0x00, .limit = 0xffffffff, .type = 0x92},           // Kernel Data Segment
        {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},           // User Code Segment
        {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},           // User Data Segment
        {.base = (uint32_t)&tss, .limit = sizeof(tss), .type = 0xE9} // TSS Segment
};

void kernel_main()
{
  terminal_initialize();
  print("Hello World!\n\nMr. XX\n");

  memset(gdt_real, 0x00, sizeof(gdt_real));
  gdt_structured_to_gdt(gdt_real, gdt_structured, TOTAL_GDT_SEGMENTS);

  // Load the GDT
  gdt_load(gdt_real, sizeof(gdt_real));

  // initialize heap
  kheap_init();

  // Intitalize filesystems
  fs_init();

  // search and intialize disks
  disk_search_and_init();

  // initialize global Interrupt descriptor table
  idt_init();

  // Setup TSS
  memset(&tss, 0x00, sizeof(tss));
  tss.esp0 = 0x600000; // location of kernel stack
  tss.ss0 = KERNEL_DATA_SELECTOR;

  // Load TSS
  tss_load(0x28); // offset in gdt-> 5 * 8 bytes

  // Set up paging
  kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

  // switch to kernel chunk
  paging_switch(kernel_chunk);

  // enable paging
  enable_paging();

  // register the kernel commands
  isr80h_register_commands();

  struct process *process = 0;
  int res = process_load("0:/blank.bin", &process);
  if (res != ALL_OK)
  {
    panic("Failed to load blank.bin\n");
  }
  task_run_first_ever_task();

  while (1)
  {
  }
}