#include "string.h"

size_t strlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return s - str;
}

char *strcpy(char *dest, const char *src) { // copies from src to dest
    char *ptr = dest;
    while ((*ptr++ = *src++));
    return dest;
}

char *strcat(char *dest, const char *src) { // concatenates src to end of dest
    char *ptr = dest + strlen(dest);
    while ((*ptr++ = *src++));
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Set memory block to a specific value
void *memset(void *s, int c, size_t n) {
    unsigned char *ptr = s;
    while (n--) {
        *ptr++ = (unsigned char)c;
    }
    return s;
}
