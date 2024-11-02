#include "process.h"
#include <stdlib.h> // For malloc/free or custom allocators
#include <string.h> // For memset

static Process *processes[MAX_PROCESSES];
static int process_count = 0;

// Initialize process management
void process_init(void) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i] = NULL; // Set all to NULL initially
    }
}

// Function to set up the initial stack for a process
void setup_initial_stack(uint64_t stack_pointer, void (*func)()) {
    // Allocate space for return address and arguments
    uint64_t *stack = (uint64_t *)stack_pointer;

    // Clear the stack memory
    memset(stack, 0, 1024); // Assuming stack size of 1024 bytes

    // Set the return address to the process function
    *stack = (uint64_t)func;

    // Setup the stack pointer to the top of the stack (adjust for stack growth direction)
    // Here, we assume the stack grows downwards, so we set the stack pointer to the end of the allocated space
    uint64_t *new_stack_pointer = stack + (1024 / sizeof(uint64_t));
    // Note: The actual stack setup may vary based on calling conventions
}

// Create a new process
Process* create_process(void (*func)()) {
    if (process_count >= MAX_PROCESSES) {
        return NULL; // No space for more processes
    }

    Process *new_process = (Process *)malloc(sizeof(Process));
    if (!new_process) {
        return NULL; // Allocation failed
    }

    new_process->pid = process_count; // Assign PID
    new_process->state = PROCESS_READY; // Initial state
    new_process->stack_pointer = (uint64_t)malloc(1024); // Allocate stack space (adjust size as needed)
    new_process->priority = 1; // Default priority

    // Set up the initial stack for the process
    setup_initial_stack(new_process->stack_pointer, func);

    processes[process_count++] = new_process; // Add to process list
    return new_process;
}

// Destroy a process
void destroy_process(uint64_t pid) {
    if (pid >= process_count || processes[pid] == NULL) {
        return; // Invalid PID
    }

    // Free the stack and process structure
    free((void *)processes[pid]->stack_pointer);
    free(processes[pid]);
    processes[pid] = NULL; // Mark as NULL
}

// Schedule a specific process (placeholder for context switching)
void schedule_process(Process *process) {
    // Implementation for scheduling the specific process
    // This could involve saving current context and loading the new process context
}
