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

int strcmp(char string1[], char string2[] )
{
    for (int i = 0; ; i++)
    {
        if (string1[i] != string2[i])
        {
            return string1[i] < string2[i] ? -1 : 1;
        }

        if (string1[i] == '\0')
        {
            return 0;
        }
    }
}

// Set memory block to a specific value
void *memset(void *s, int c, size_t n) {
    unsigned char *ptr = s;
    while (n--) {
        *ptr++ = (unsigned char)c;
    }
    return s;
}
