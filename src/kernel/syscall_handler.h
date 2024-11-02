// syscall_numbers.h
#ifndef SYSCALL_HANDLER_H
#define SYSCALL_HANDLER_H

// Process control syscalls
#define SYS_READ     0
#define SYS_WRITE    1
#define SYS_OPEN     2
#define SYS_CLOSE    3
#define SYS_STAT     4
#define SYS_FSTAT    5
#define SYS_LSTAT    6
#define SYS_POLL     7
#define SYS_LSEEK    8
#define SYS_MMAP     9
#define SYS_MUNMAP   10
#define SYS_BRK      11
#define SYS_EXIT     12
#define SYS_FORK     13
#define SYS_EXECVE   14
#define SYS_WAIT     15
#define SYS_KILL     16
#define SYS_GETPID   17

// mem management
#define SYS_MALLOC   18
#define SYS_FREE     19

// file management
#define SYS_RENAME   20
#define SYS_UNLINK   21
#define SYS_CHDIR    22
#define SYS_GETCWD   23

// network (probably won't be implemented)
#define SYS_SOCKET    24
#define SYS_CONNECT   25
#define SYS_BIND      26
#define SYS_LISTEN    27
#define SYS_ACCEPT    28
#define SYS_SEND      29
#define SYS_RECEIVE   30

// OS info
#define SYS_TIME      31
#define SYS_SYSINFO   32

int syscall_handler(int syscall, void *args);

#endif // SYSCALL_HANDLER_H
