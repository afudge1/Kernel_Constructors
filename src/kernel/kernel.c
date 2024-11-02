#include "kernel.h"
#include "../fat16/fat16.h"  // Include the FAT16 header
#include <stdint.h>

int kmain() {
    // Initialize the video memory
    uint16_t* buffer = (uint16_t*)0xb8000;
    *buffer = (uint16_t)0x020F;  // Set character and attribute (e.g., ' ' and bright white)

    // Initialize the FAT16 filesystem
    init_fat16();

    // Example: Read a file from the FAT16 filesystem
    char filename[] = "FILE.TXT"; // Example filename (must match your FAT16 file)
    char buffer[512];  // Buffer to hold the file data
    int bytes_read = read_file(filename, buffer, sizeof(buffer)); // Read the file

    if (bytes_read > 0) {
        // Optionally, you can print the contents to the screen
        for (int i = 0; i < bytes_read; i++) {
            // Output each byte as a character
            *(buffer + i) = (buffer[i] == '\0') ? ' ' : buffer[i]; // Replace null with space for display
            // Print to video memory (for simplicity, print in a straight line)
            *(buffer + i) = buffer[i]; // Adjust according to how you want to display it
        }
    }

    return 0; // Return from kmain
}
