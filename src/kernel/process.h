#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#define MAX_PROCESSES 128  // Maximum number of processes
#define STACK_SIZE_HEX 0x20000 // 128 KB stack size

// Process states
typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_BLOCKED,
    PROCESS_TERMINATED
} ProcessState;

// Process Control Block (PCB)
typedef struct Process {
    uint64_t pid;               // Process ID
    uint64_t stack_pointer;     // Stack pointer for the process
    ProcessState state;         // Current state of the process
    uint64_t priority;          // Process priority (optional)
    // Add more fields as needed (e.g., program counter, registers)
} Process;

void process_init(void);            // Initialize process management
Process* create_process(void (*func)()); // Create a new process
void kill_process(uint64_t pid);    // Kill a process
void schedule_process(Process *process); // Schedule a specific process

#endif // PROCESS_H
