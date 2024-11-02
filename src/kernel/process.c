#include "process.h"
#include <stdlib.h> // For malloc/free or custom allocators
#include <string.h> // For memset

static Process *processes[MAX_PROCESSES];
static int process_count = 0;

// initialize process management
void process_init(void) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i] = NULL; // Set all to NULL initially
    }
}

// set up initial stack for a process
void setup_initial_stack(uint64_t stack_pointer, void (*func)()) {
    // Allocate space for return address and arguments
    uint64_t *stack = (uint64_t *)stack_pointer;

    // clear stack memory
    memset(stack, 0, STACK_SIZE_HEX);

    // Set the return address to the process function
    *stack = (uint64_t)func;

    // set stack pointer to top of stack (adjust for stack growth direction)
    uint64_t *new_stack_pointer = stack + (STACK_SIZE_HEX / sizeof(uint64_t));
    // Note: The actual stack setup may vary based on calling conventions
}

// new process creation
Process* create_process(void (*func)()) {
    if (process_count >= MAX_PROCESSES) {
        return NULL; // no space for more processes
    }

    Process *new_process = (Process *)malloc(sizeof(Process));
    if (!new_process) {
        return NULL; // allocation failed
    }

    new_process->pid = process_count; // assign PID
    new_process->state = PROCESS_READY; // initial state
    new_process->stack_pointer = (uint64_t)malloc(STACK_SIZE_HEX); // allocate stack space
    new_process->priority = 1; // default priority

    // Set up the initial stack for the process
    setup_initial_stack(new_process->stack_pointer, func);

    processes[process_count++] = new_process; // Add to process list
    return new_process;
}

// kill a process
void kill_process(uint64_t pid) {
    if (pid >= process_count || processes[pid] == NULL) {
        return; // invalid PID
    }

    // free stack/process structure
    free((void *)processes[pid]->stack_pointer);
    free(processes[pid]);
    processes[pid] = NULL; // ark as NULL
}

// Schedule a specific process (placeholder for context switching)
void schedule_process(Process *process) {
    // Implementation for scheduling the specific process
    // could involve saving current context and loading the new process context
}
