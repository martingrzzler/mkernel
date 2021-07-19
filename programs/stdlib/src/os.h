#ifndef OS_H
#define OS_H

#include <stddef.h>
#include <stdbool.h>

struct command_argument
{
	char argument[512];
	struct command_argument *next;
};

struct process_arguments
{
	int argc;
	char **argv;
};

void print(const char *filename);
struct command_argument *os_parse_command(const char *command, int max);
int os_getKey();
void *os_malloc(size_t size);
void os_free(void *ptr);
void os_putchar(char c);
int os_getkeyblock();
void os_terminal_readline(char *out, int max, bool output_while_typing);
void os_process_load_start(const char *filename);
void os_process_get_arguments(struct process_arguments *arguments);

#endif