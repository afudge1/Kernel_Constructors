#include "paging.h"
#include "../heap/kheap.h"

// Example usage in kernel (initialize and enable paging):
// #include "memory/paging/paging.h" in kernel
// call enable_paging() in kmain()
/*
Ex.
struct paging_4gb_chunk* kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));
enable_paging();
*/

// Load the given page directory into the CR3 register (assembly)
void paging_load_directory(uint32_t directory);
// Pointer to currently active page directory
static uint32_t* current_directory = 0; 

// Create a new 4GB paging chunk with specified flags
struct paging_4gb_chunk* paging_new_4gb(uint8_t flags) {
    // Allocate page directory
    uint32_t* directory = kzalloc(sizeof(uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE); 

    int offset = 0;
    for (int i = 0; i < PAGING_TOTAL_ENTRIES_PER_TABLE; ++i) {
        // Allocate a page table
        uint32_t* entry = kzalloc(sizeof(uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE); 
        for (int j = 0; j < PAGING_TOTAL_ENTRIES_PER_TABLE; ++j) {
            // Initialize each page entry with flags
            entry[j] = (offset + (j * PAGING_PAGE_SIZE)) | flags; 
        }
        // Move to the next page table
        offset += (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE); 
        // Link page table to directory with write flag
        directory[i] = (uint32_t)entry | flags | PAGING_IS_WRITEABLE; 
    }
    // Allocate 4GB chunk structure
    struct paging_4gb_chunk* chunk_4gb = kzalloc(sizeof(struct paging_4gb_chunk)); 
    // Assign directory entry to chunk
    chunk_4gb->directory_entry = directory; 
    // Return the initialized 4GB chunk
    return chunk_4gb;
}

// Switch to the given page directory
void paging_switch(uint32_t* directory) {
    // Load new directory into CR3
    paging_load_directory(*directory); 
    // Update current directory pointer
    current_directory = directory; 
}

// Get the directory entry of a 4GB paging chunk
uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk) {
    // Return directory entry from chunk
    return chunk->directory_entry; 
}

// Check if an address is page-aligned
bool paging_is_aligned(void* virtual_address) {
    // Check alignment with page size
    return ((uint32_t)virtual_address % PAGING_PAGE_SIZE) == 0; 
}

// Get the directory and table indexes for a given virtual address
int paging_get_indexes(void* virtual_address, uint32_t* directory_index_out, uint32_t* table_index_out) {
    if (!paging_is_aligned(virtual_address)) {
        // Error if address is not page-aligned
        return -1; 
    }

    // Calculate indexes based on address
    *directory_index_out = ((uint32_t)virtual_address / (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE));
    *table_index_out = ((uint32_t)virtual_address % (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE)) / PAGING_PAGE_SIZE;
    
    // Success
    return 0; 
}

// Set a page table entry for a given virtual address in a directory
int paging_set(uint32_t* directory, void* virtual_address, uint32_t value) {
    if (!paging_is_aligned(virtual_address)) {
        // Error if address is not page-aligned
        return -1; 
    }

    uint32_t directory_index = 0;
    uint32_t table_index = 0;
    int res = paging_get_indexes(virtual_address, &directory_index, &table_index);

    if (res < 0) {
        // Return error if indexes couldn't be calculated
        return res; 
    }

    // Locate the page table in the directory
    uint32_t entry = directory[directory_index];
    // Mask to get base address of table
    uint32_t* table = (uint32_t*)(entry & 0xFFFFF000); 
    // Set the entry in the table
    table[table_index] = value; 
    
    // Success
    return 0; 
}