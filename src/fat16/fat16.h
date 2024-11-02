#ifndef FAT16_H
#define FAT16_H

#include <stdint.h>
#include <stddef.h>

#pragma pack(push, 1) // Start packing with 1-byte alignment

typedef struct {
    uint8_t jump[3];
    char filesystem_name[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t num_fats;
    uint16_t max_root_dir_entries;
    uint16_t total_sectors;
    uint8_t media_descriptor;
    uint16_t fat_size;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_large;
} fat16_boot_sector_t;

#pragma pack(pop) // Restore previous packing alignment

// Function prototypes
void init_fat16();
int read_file(const char *filename, void *buffer, size_t size);
int write_file(const char *filename, const void *buffer, size_t size);

#endif // FAT16_H
