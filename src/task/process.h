#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "task.h"
#include "config.h"

struct process
{
	// Process id
	uint16_t id;
	char filename[MAX_PATH];
	// main process task
	struct task *task;
	// memory (malloc) alocations of the process
	void *allocations[MAX_PROGRAM_ALLOCATIONS];
	// physical pointer to the process memory
	void *ptr;

	// physical pointer to thr stack memory
	void *stack;
	// size of data pointed to by "ptr"
	uint32_t size;
};
int process_load_for_slot(const char *filename, struct process **process, int process_slot);
int process_load(const char *filename, struct process **process);

#endif