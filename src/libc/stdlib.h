#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h> // size_t

// mem management functions
void *malloc(size_t size);
void free(void *ptr);
//void *realloc(void *ptr, size_t size);
//void *calloc(size_t nmemb, size_t size);

// random functions
//int rand(void);
//void srand(unsigned int seed);

// conversion functions
//int atoi(const char *str);
//long atol(const char *str);

#endif // STDLIB_H
