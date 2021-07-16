#ifndef OS_H
#define OS_H

#include <stddef.h>
#include <stdbool.h>

void print(const char *filename);
int os_getKey();
void *os_malloc(size_t size);
void os_free(void *ptr);
void os_putchar(char c);
int os_getkeyblock();
void os_terminal_readline(char *out, int max, bool output_while_typing);

#endif