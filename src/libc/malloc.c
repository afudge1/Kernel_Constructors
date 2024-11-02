#include "stdlib.h"
#include <stddef.h> // size_t

#define HEAP_SIZE 1024 * 1024 * 100 // 100MB heap
static char heap[HEAP_SIZE]; // static buffer for heap

typedef struct Block {
    size_t size;          // block size
    struct Block *next;   // next free block
} Block;

static Block *free_list = NULL; // head

// initialize malloc
void init_malloc() {
    free_list = (Block *)heap; // Set the free list to the start of the heap
    free_list->size = HEAP_SIZE - sizeof(Block); // Set the size of the first block
    free_list->next = NULL; // No next block initially
}

// Allocate memory
void *malloc(size_t size) {
    if (size == 0) {
        return NULL; // No allocation for size 0
    }

    // Align size to the nearest multiple of 4
    size = (size + 3) & ~3;

    Block *current = free_list;
    Block *previous = NULL;

    // Find the first suitable block
    while (current != NULL) {
        if (current->size >= size) {
            // If the remaining block is large enough, split it
            if (current->size > size + sizeof(Block)) {
                Block *new_block = (Block *)((char *)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }

            // Remove current block from the free list
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                free_list = current->next; // Move head of the free list
            }

            return (void *)((char *)current + sizeof(Block)); // Return pointer to usable memory
        }

        previous = current;
        current = current->next;
    }

    return NULL; // No suitable block found
}

// Free allocated memory
void free(void *ptr) {
    if (ptr == NULL) {
        return; // Do nothing for NULL pointers
    }

    // Get the block pointer
    Block *block = (Block *)((char *)ptr - sizeof(Block));
    block->next = free_list; // Add the block back to the free list
    free_list = block; // Update head of the free list
}
