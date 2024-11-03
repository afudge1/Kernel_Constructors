// printf.c
#include "stdio.h"
#include "stdlib.h"  // For itoa or other utility functions
#include <stdarg.h>
#include "printf.h"
#include "terminal/terminal.h"
#include "terminal/terminal_config.h"

char printf_buffer[VGA_WIDTH+1];
uint32_t printf_buffer_i;

void putchar(char c) {
    printf_buffer[printf_buffer_i]=c;
    printf_buffer_i++;

    if (printf_buffer_i>=VGA_WIDTH || c == '\n' || c == 0)
    {
        printf_buffer[printf_buffer_i-1] = 0;
        terminal_input(printf_buffer);
        for (int i=0;i<VGA_WIDTH+1;i++)
        {
            printf_buffer[i] = 0;
        }        
        printf_buffer_i = 0;
    }
}

static void print_string(const char *str) {
    while (*str) {
        putchar(*str++);
    }
}

static void print_int(int num) {
    char buffer[12]; // Enough for a 32-bit int
    int i = 0;

    // handle negatives
    if (num < 0) {
        putchar('-');
        num = -num;
    }

    // convert integer -> string in reverse order
    if (num == 0) {
        putchar('0');
        return;
    }

    while (num > 0) {
        buffer[i++] = (num % 10) + '0'; // get last digit
        num /= 10;                       // remove last digit
    }

    // Print the number in the correct order
    for (int j = i - 1; j >= 0; j--) {
        putchar(buffer[j]);
    }
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++; // Move to the next character
            switch (*format) {
                case 's': {
                    // string
                    char *str = va_arg(args, char *);
                    print_string(str);
                    break;
                }
                case 'd': {
                    // integer
                    int num = va_arg(args, int);
                    print_int(num);
                    break;
                }
                case 'c': {
                    // char
                    char ch = (char)va_arg(args, int);
                    putchar(ch);
                    break;
                }
                default:
                    putchar('%'); // Print the '%' if unknown specifier
                    putchar(*format); // Print the character after '%'
                    break;
            }
        } else {
            putchar(*format); // Print regular characters
        }
        format++;
    }

    va_end(args);
    putchar('\n');
    return 0;
}
