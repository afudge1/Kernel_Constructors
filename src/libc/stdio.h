#ifndef STDIO_H
#define STDIO_H

#include <stddef.h> // For size_t

// Function prototypes for standard I/O functions
int printf(const char *format, ...);
void putchar(char c);
int puts(const char *str);
void getchar(void);
char *gets(char *str); // unsafe :>

#endif // STDIO_H