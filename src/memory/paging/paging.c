#include "paging.h"
#include "../heap/kheap.h"

// Load the given page directory into CR3 register
void paging_load_directory(uint32_t directory);
static uint32_t* current_directory = 0; // Pointer to the current paging directory

// Create a new 4GB paging chunk with specified flags
struct paging_4gb_chunk* paging_new_4gb(uint8_t flags) {
    // Allocate directory
    uint32_t* directory = kzalloc(sizeof(uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE); 

    int offset = 0;
    for (int i = 0; i < PAGING_TOTAL_ENTRIES_PER_TABLE; ++i) {
        // Allocate page table entry
        uint32_t* entry = kzalloc(sizeof(uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE); 
        for (int j = 0; j < PAGING_TOTAL_ENTRIES_PER_TABLE; ++j) {
            // Set up page table entries
            entry[j] = (offset + (j * PAGING_PAGE_SIZE)) | flags; 
        }
        // Update offset for next table
        offset += (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE); 
        // Link page table to directory
        directory[i] = (uint32_t)entry | flags | PAGING_IS_WRITEABLE; 
    }
    // Create 4GB chunk
    struct paging_4gb_chunk* chunk_4gb = kzalloc(sizeof(struct paging_4gb_chunk)); 
    // Assign the directory entry
    chunk_4gb->directory_entry = directory; 
    // Return the new chunk
    return chunk_4gb; 
}

// Switch the current paging directory
void paging_switch(uint32_t* directory) {
    // Load the new directory
    paging_load_directory(directory); 
    // Update the current directory pointer
    current_directory = directory; 
}

// Get the directory of the 4GB chunk
uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk) {
    // Return the directory entry of the chunk
    return chunk->directory_entry; 
}
