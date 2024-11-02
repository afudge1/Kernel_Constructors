#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define TIME_SLICE 10  // Time slice for each process in milliseconds
#define MAX_PROCESSES 128  // Maximum number of processes

typedef struct Process {
    uint64_t pid;  // Process ID
    uint64_t stack_pointer; // Stack pointer for the process
    // Add more fields as needed (e.g., state, priority)
} Process;

void scheduler_init(void);
void schedule(void);

#endif // SCHEDULER_H
