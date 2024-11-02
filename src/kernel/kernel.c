#include "kernel.h"
#include "fat16/fat16.h"  // Include the FAT16 header
#include <stdint.h>

void display_char(uint16_t character, int position);

int kmain() {
    // Initialize the video memory
    uint16_t* video_memory = (uint16_t*)0xb8000;
    *video_memory = (uint16_t)0x020F;  // Set character and attribute (e.g., ' ' and bright white)

    // Initialize the FAT16 filesystem
    init_fat16();

    // Example: Read a file from the FAT16 filesystem
    const char *filename = "FILE.TXT"; // Example filename (must match your FAT16 file)
    char file_buffer[512];  // Buffer to hold the file data
    int bytes_read = read_file(filename, file_buffer, sizeof(file_buffer)); // Read the file

    if (bytes_read > 0) {
        // Optionally, display the contents to the screen
        for (int i = 0; i < bytes_read; i++) {
            // Replace null characters with spaces for display
            char display_char_value = (file_buffer[i] == '\0') ? ' ' : file_buffer[i];

            // Display character at corresponding video memory position
            display_char(display_char_value | 0x0F00, i); // Set attribute to white
        }
    }

    return 0; // Return from kmain
}

// Function to display a character at a specific position in video memory
void display_char(uint16_t character, int position) {
    uint16_t* video_memory = (uint16_t*)0xb8000; // Video memory base address
    video_memory[position] = character; // Write character and attribute
}
