#ifndef STRING_H
#define STRING_H

#include <stddef.h> // For size_t

// Function prototypes for string manipulation functions
size_t strlen(const char *str);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strcmp(char string1[], char string2[] );
void *memset(void *s, int c, size_t n);

#endif // STRING_H
