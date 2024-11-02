#include "heap.h"
#include "kernel.h"
#include <stdbool.h>

static int heap_validate_table(void* ptr, void* end, struct heap_table* table)
{
    
    size_t table_size = (size_t)(end - ptr);
    size_t total_pages = table_size / PAINOS_HEAP_BLOCK_SIZE;
    if(table->total != total_pages) {
        return -1;
    }

    return 0;
}
static int heap_validate_alignment(void* ptr) {
    return ((unsigned int)ptr % PAINOS_HEAP_BLOCK_SIZE) == 0;
}


// Expects uninitialized heap, start pointer, end pointer, and valid heap_table
int heap_create(struct heap* heap, void* ptr, void* end, struct heap_table* table) {

    if(!heap_validate_alignment(ptr) || !heap_validate_alignment(end)) {
        // Badddddd :(
        return -1;
    }

    memset(heap, 0, sizeof(struct heap));
    heap->start_address = ptr;
    heap->table = table;
    return 0;
}