#include "kernel.h"
//#include "fat16/fat16.h"  // Include the FAT16 header
#include <stdint.h>
#include "idt/idt.h"

void display_char(uint16_t character, int position);

int kmain() {
    // Initialize the video memory
    uint16_t* video_memory = (uint16_t*)0xb8000;
    *video_memory = (uint16_t)0x020F;  // Set character and attribute (e.g., ' ' and bright white)

    // Initialize the FAT16 filesystem
    //init_fat16();

    idt_init();

    return 0; // Return from kmain
}

// Function to display a character at a specific position in video memory
void display_char(uint16_t character, int position) {
    uint16_t* video_memory = (uint16_t*)0xb8000; // Video memory base address
    video_memory[position] = character; // Write character and attribute
}
