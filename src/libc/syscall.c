#include "syscall.h"

// Function to invoke a syscall
int user_syscall(int number, void *args) {
    int result;

    // Assembly code to invoke the syscall
    asm volatile (
        "movl %[number], %%eax;"  // Move syscall number into eax
        "movl %[args], %%ebx;"    // Move args pointer into ebx (first argument)
        "int $0x80;"              // Trigger interrupt for syscall
        "movl %%eax, %[result];"  // Move the result from eax to result variable
        : [result] "=r" (result)   // Output operand
        : [number] "r" (number), [args] "r" (args) // Input operands
        : "%eax", "%ebx"          // Clobbered registers
    );

    return result; // Return the result from the syscall
}
