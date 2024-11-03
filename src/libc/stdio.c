// Function to output a single character
int putchar(int c) {
    // Replace this with actual I/O operations appropriate for your system
    // For example: syscall(SYS_WRITE, &c, 1);
    return c; // Assume the character is written successfully
}

// Function to output a string
int puts(const char *str) {
    while (*str) {
        putchar(*str++); // Output each character
    }
    putchar('\n'); // Print a newline character
    return 0; // Success
}

// Function to read a single character from input
int getchar(void) {
    int c;
    // Here, implement actual input reading from your system
    // For example: syscall(SYS_READ, &c, 1);
    // This is a placeholder:
    c = 'p'/* read character from input */;
    
    return c; // Return the character read
}

// Unsafe gets implementation
char *gets(char *str) {
    int c;
    int i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        str[i++] = (char)c; // Store character in the string
    }
    str[i] = '\0'; // Null-terminate the string

    if (c == EOF && i == 0) {
        return NULL; // No input read
    }
    return str; // Return the string
}
