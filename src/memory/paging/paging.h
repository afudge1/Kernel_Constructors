#ifndef PAGING_H
#define PAGING_H
#include <stdint.h>
#include <stddef.h>

#define PAGING_CACHE_DISABLED 0x10
#define PAGING_WRITE_THROUGH 0x8
#define PAGING_ACCESS_FROM_ALL 0x4
#define PAGING_IS_WRITEABLE 0x2
#define PAGING_IS_PRESENT 0x1

#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024
#define PAGING_PAGE_SIZE 4096
struct paging_4gb_chunk {
    uint32_t* directory_entry;
};

struct paging_4gb_chunk* paging_new_4gb(uint8_t flags);
void paging_switch(uint32_t* directory);
void enable_paging(); // From assembly
uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk);


#endif