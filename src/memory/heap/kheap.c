#include "kheap.h"
#include "heap.h"
#include "config.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init() {
    // Initialize kernel heap

    // Should be 25600
    int total_table_entries = PAINOS_HEAP_SIZE_BYTES / PAINOS_HEAP_BLOCK_SIZE;
    
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)PAINOS_HEAP_TABLE_ADDRESS;
    kernel_heap_table.total = total_table_entries;

    void* end = (void*)(PAINOS_HEAP_ADDRESS + PAINOS_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void*)(PAINOS_HEAP_ADDRESS), end, &kernel_heap_table);

    if (res != 0) {
        print("Failed\n");
    }
}