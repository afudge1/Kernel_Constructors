#ifndef HEAP_H
#define HEAP_H

#include "config.h"
#include <stdint.h>
#include <stddef.h>

// Indicates a block is occupied
#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01

// Indicates a block is free
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

// Additional blocks in a multi-block allocation
#define HEAP_BLOCK_HAS_NEXT 0x80

// Mark block as free (inverted with TAKEN to indicate the state)
#define HEAP_BLOCK_IS_FREE  0x40

// Type definition for each entry in the heap's block table
typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

// Keeps track of memory block usage
struct heap_table
{
    HEAP_BLOCK_TABLE_ENTRY* entries; // Array of entries marking block statuses (taken/free)
    size_t total;                    // Total number of blocks in the heap
};

// Start address and its table
struct heap
{
    struct heap_table* table;   // Pointer to the associated block table for this heap
    void* start_address;        // Starting address of the heap's memory region
};

// Initializes a new heap with the given start and end addresses, and associates it with a block table
int heap_create(struct heap* heap, void* ptr, void* end, struct heap_table* table);
// Allocates memory of the specified size on the heap
void* heap_malloc(struct heap* heap, size_t size);
// Frees previously allocated memory at the specified pointer on the heap
void heap_free(struct heap* heap, void* ptr);

#endif
