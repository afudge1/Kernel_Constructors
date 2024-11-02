#include "syscall.h"
#include "kernel/syscall_handler.h"

// Function to invoke a syscall
int user_syscall(int number, void *args) {
    return syscall_handler(number, args); // Directly call the handler
}
