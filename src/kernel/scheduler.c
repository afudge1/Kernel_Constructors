#include "scheduler.h"

static Process *processes[MAX_PROCESSES];
static int current_process_index = 0;
static int process_count = 0;

// Initialize the scheduler
void scheduler_init(void) {
    // Initialize process array and any other needed structures
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i] = NULL; // Set all to NULL initially
    }
}

// Add a process to the scheduler
void add_process(Process *process) {
    if (process_count < MAX_PROCESSES) {
        processes[process_count++] = process;
    }
}

// Round Robin scheduling
void schedule(void) {
    if (process_count == 0) return; // No processes to schedule

    // Select the next process in a round-robin manner
    current_process_index = (current_process_index + 1) % process_count;
    Process *next_process = processes[current_process_index];

    // Switch to the next process (pseudo-code for context switch)
    // context_switch(next_process->stack_pointer);
}
