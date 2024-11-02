#ifndef STDIO_H
#define STDIO_H

#include <stddef.h> // For size_t

// Function declarations

// Basic character output
int putchar(char c);
int puts(const char *str);

// Formatted output
int printf(const char *format, ...);

// String handling
char *gets(char *str); // Note: gets is unsafe; consider alternatives
int sprintf(char *str, const char *format, ...);

#endif // STDIO_H
