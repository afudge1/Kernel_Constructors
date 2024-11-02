// syscall.h
#ifndef SYSCALL_H
#define SYSCALL_H

#include "../kernel/syscall_numbers.h"

// Function prototype for user_syscall
int user_syscall(int number, void *args);

// Syscall wrapper function
static inline int syscall(int number, void *args) {
    return user_syscall(number, args);
}

#endif // SYSCALL_H
