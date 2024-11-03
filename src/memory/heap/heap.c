#include "heap.h"
#include "kernel.h"
#include <stdbool.h>

// Validates that the heap table matches the expected number of blocks
static int heap_validate_table(void* ptr, void* end, struct heap_table* table) {
    // Calculate the total size of the heap and the number of pages
    size_t table_size = (size_t)((unsigned int)end - (unsigned int)ptr);
    size_t total_pages = table_size / PAINOS_HEAP_BLOCK_SIZE;

    // Check if the table's total pages match the calculated total pages
    if(table->total != total_pages) {
        return -1; // Error if the totals do not match
    }

    return 0; // Valid if totals match
}

// Validates if a pointer is aligned to the block size
static int heap_validate_alignment(void* ptr) {
    // Returns 0 if the address is not aligned, or 1 if it is
    return ((unsigned int)ptr % PAINOS_HEAP_BLOCK_SIZE) == 0;
}

// Initializes an uninitialized heap with start, end, and table information
int heap_create(struct heap* heap, void* ptr, void* end, struct heap_table* table) {
    int res = 0;

    // Validate alignment of the start and end pointers
    if(!heap_validate_alignment(ptr) || !heap_validate_alignment(end)) {
        return -1; // Error if alignment is invalid
    }

    // Initialize the heap struct and assign start address and table
    memset(heap, 0, sizeof(struct heap));
    heap->start_address = ptr;
    heap->table = table;

    // Validate the table based on start and end addresses
    res = heap_validate_table(ptr, end, table);
    if(res < 0) {
        return -1; // Error if table is invalid
    }

    // Initialize all entries in the table to free
    size_t table_size = sizeof(HEAP_BLOCK_TABLE_ENTRY) * table->total;
    memset(table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);
    return res;
}

// Aligns a value to the nearest upper multiple of PAINOS_HEAP_BLOCK_SIZE
static uint32_t heap_align_value_to_upper(uint32_t val) {
    // Check if already aligned
    if(val % PAINOS_HEAP_BLOCK_SIZE == 0) {
        return val;
    }

    // Adjust value upwards to the next block boundary
    val = (val - (val % PAINOS_HEAP_BLOCK_SIZE)) + PAINOS_HEAP_BLOCK_SIZE;
    return val;
}

// Retrieves the type of a heap block entry using bitwise operations
static int heap_get_entry_type(HEAP_BLOCK_TABLE_ENTRY entry) {
    return entry & 0x0f; // Mask to get entry type from entry bits
}

// Finds the starting block index for a contiguous sequence of free blocks of a specified length
int heap_get_start_block(struct heap* heap, int total_blocks) {
    struct heap_table* table = heap->table;
    int bc = 0; // Block count
    int bs = -1; // Starting block index for the sequence

    // Loop through each block in the table to find a free sequence
    for(size_t i = 0; i < table->total; ++i) {
        if(heap_get_entry_type(table->entries[i]) == HEAP_BLOCK_TABLE_ENTRY_FREE) {
            // Found a free block, increment counter
            if(bs == -1) {
                bs = i; // Set start of free sequence
            }
            bc++;

            // If enough blocks are found, return starting index
            if(bc == total_blocks) {
                return bs;
            }
        } else {
            // Reset counters if block is not free
            bc = 0;
            bs = -1;
        }
    }

    // Return -1 if no suitable block sequence is found
    return -1;
}

// Function to mark a range of blocks as taken in the heap's block table.
void heap_mark_blocks_taken(struct heap* heap, int start_block, int total_blocks) {
    int end_block = (start_block + total_blocks) - 1;

    // Set base entry status for a "taken" block
    HEAP_BLOCK_TABLE_ENTRY entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN | HEAP_BLOCK_IS_FREE;

    // Mark as having a next block if this allocation spans multiple blocks
    if(total_blocks > 1) {
        entry |= HEAP_BLOCK_HAS_NEXT;
    }

    // Mark each block in the range as taken
    for(int i = start_block; i <= end_block; ++i) {
        heap->table->entries[i] = entry;
        
        // Add HAS_NEXT flag for all but the last block
        if(i != end_block) {
            entry |= HEAP_BLOCK_HAS_NEXT;
        }
    }
}

// Converts a block index to its corresponding memory address
void* heap_block_to_address(struct heap* heap, int block) {
    return (void*)((unsigned int)heap->start_address + (block * PAINOS_HEAP_BLOCK_SIZE));
}

// Allocates a specified number of contiguous blocks in the heap and returns their address
void* heap_malloc_blocks(struct heap* heap, uint32_t total_blocks) {
    void* address = 0;

    // Find the starting block of the free sequence
    int start_block = heap_get_start_block(heap, total_blocks);
    if(start_block < 0) {
        return 0; // Return null if allocation failed
    }
    
    // Convert start block to memory address
    address = heap_block_to_address(heap, start_block);

    // Mark blocks as taken in the table
    heap_mark_blocks_taken(heap, start_block, total_blocks);

    return address;
}

// Allocates memory on the heap of a specified size.
void* heap_malloc(struct heap* heap, size_t size) {
    // Align the requested size to meet block size requirements
    size_t aligned_size = heap_align_value_to_upper(size);
    
    // Calculate total blocks required for the aligned size
    uint32_t total_blocks = aligned_size / PAINOS_HEAP_BLOCK_SIZE;
    
    // Allocate blocks and return their address
    return heap_malloc_blocks(heap, total_blocks);
}

// Converts an address within the heap to its corresponding block index
int heap_address_to_block(struct heap* heap, void* address) {
    return (int)((unsigned int)address - (unsigned int)heap->start_address) / PAINOS_HEAP_BLOCK_SIZE;
}

// Marks a series of blocks as free, starting from a specified block
void heap_mark_blocks_free(struct heap* heap, int starting_block) {
    struct heap_table* table = heap->table;
    
    // Loop through blocks from starting block and mark them as free
    for(int i = starting_block; i < (int)table->total; ++i) {
        HEAP_BLOCK_TABLE_ENTRY entry = table->entries[i];
        
        // Mark the block as free
        table->entries[i] = HEAP_BLOCK_TABLE_ENTRY_FREE;
        
        // Stop if this is the last block in the sequence
        if(!(entry & HEAP_BLOCK_HAS_NEXT)) {
            break;
        }
    }
}

// Frees memory allocated at a specified pointer on the heap
void heap_free(struct heap* heap, void* ptr) {
    // Convert the pointer to the corresponding block index and free blocks
    heap_mark_blocks_free(heap, heap_address_to_block(heap, ptr));
}