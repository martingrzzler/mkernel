#ifndef TASK_H
#define TASK_H

#include "config.h"
#include "memory/paging/paging.h"
#include "process.h"

struct registers
{
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;

	uint32_t ip;
	uint32_t cs;
	uint32_t flags;
	uint32_t esp;
	uint32_t ss;
};

struct process;

struct task
{
	struct paging_4gb_chunk *page_directory;

	// to be able to reenable state when task was halted
	struct registers registers;

	struct process *process;

	struct task *next;
	struct task *prev;
};

struct task *task_new(struct process *process);
struct task *task_current();
struct task *task_get_next();
int task_free(struct task *task);
void restore_general_purpose_registers(struct registers *regs);

void task_run_first_ever_task();

void task_return(struct registers *regs);
void user_registers();
int task_switch(struct task *task);
int task_page();

#endif