#include "syscall_handler.h"
#include "terminal/terminal.h"

// Placeholder functions for console I/O
void console_write(const char *buffer);
int console_read(char *buffer, int length);
void exit_process(int status); // Function to handle process exit


// Example syscall handler
int syscall_handler(int syscall, void *args) {
    switch (syscall) {
        case SYS_READ: {
            char *buffer = ((char **)args)[0]; // buffer
            int length = *((int *)(((char **)args)[1])); // input length
            return console_read(buffer, length); // call read
        }

        case SYS_WRITE: {
            const char *buffer = ((const char **)args)[0]; // output buffer
            int length = *((int *)(((const char **)args)[1])); // Length of output
            console_write(buffer); // Call to write function
            return length; // Return number of bytes written
            terminal_input(buffer);
        }

        case SYS_OPEN: {
            const char *path = ((const char **)args)[0];
            int flags = *((int *)(((const char **)args)[1]));
            return file_open(path, flags); // Call to open function
        }

        case SYS_CLOSE:
            // Your implementation for close
            return -1;

        case SYS_STAT:
            // Your implementation for stat
            return -1;

        case SYS_FSTAT:
            // Your implementation for fstat
            return -1;

        case SYS_LSTAT:
            // Your implementation for lstat
            return -1;

        case SYS_POLL:
            // Your implementation for poll
            return -1;

        case SYS_LSEEK:
            // Your implementation for lseek
            return -1;

        case SYS_MMAP:
            // Your implementation for mmap
            return -1;

        case SYS_MUNMAP:
            // Your implementation for munmap
            return -1;

        case SYS_BRK:
            // Your implementation for brk
            return -1;

        case SYS_EXIT: {
            int status = *((int *)args);
            exit_process(status); // Handle process exit
            return -1; // Indicate the process has exited
        }

        case SYS_FORK:
            // Your implementation for fork
            return -1;

        case SYS_EXECVE:
            // Your implementation for execve
            return -1;

        case SYS_WAIT:
            // Your implementation for wait
            return -1;

        case SYS_KILL:
            // Your implementation for kill
            return -1;

        case SYS_GETPID:
            return getpid();

        case SYS_MALLOC: {
            size_t size = *((size_t *)args); // Size to allocate
            return (int)my_malloc(size); // Return pointer to allocated memory
        }

        case SYS_FREE: {
            void *ptr = *(void **)args; // Pointer to free
            my_free(ptr); // Free the allocated memory
            return 0; // Success
        }

        case SYS_RENAME:
            // Your implementation for rename
            return -1;

        case SYS_UNLINK:
            // Your implementation for unlink
            return -1;

        case SYS_CHDIR:
            // Your implementation for chdir
            return -1;

        case SYS_GETCWD:
            // Your implementation for getcwd
            return -1;

        case SYS_SOCKET:
            // Your implementation for socket
            return -1;

        case SYS_CONNECT:
            // Your implementation for connect
            return -1;

        case SYS_BIND:
            // Your implementation for bind
            return -1;

        case SYS_LISTEN:
            // Your implementation for listen
            return -1;

        case SYS_ACCEPT:
            // Your implementation for accept
            return -1;

        case SYS_SEND:
            // Your implementation for send
            return -1;

        case SYS_RECEIVE:
            // Your implementation for receive
            return -1;

        case SYS_TIME:
            // Your implementation for time
            return -1;

        case SYS_SYSINFO:
            // Your implementation for sysinfo
            return -1;

        default:
            return -1; // invalid syscall
    }
}
