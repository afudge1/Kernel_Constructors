#ifndef FAT16_H
#define FAT16_H

#include <stdint.h>
#include <stddef.h>

#pragma pack(push, 1) // start packing with 1-byte alignment

// FAT16 Boot Sector Structure
typedef struct {
    uint8_t jump[3];                        // jump instruction for bootloader
    char filesystem_name[8];                // OEM Name
    uint16_t bytes_per_sector;               // bytes per sector
    uint8_t sectors_per_cluster;             // sectors per cluster
    uint16_t reserved_sectors;               // reserved sectors before the FAT
    uint8_t num_fats;                        // number of FATs
    uint16_t max_root_dir_entries;           // maximum number of entries in root directory
    uint16_t total_sectors;                  // total sectors (if < 65536)
    uint8_t media_descriptor;                // media descriptor
    uint16_t fat_size;                       // size of one FAT in sectors
    uint16_t sectors_per_track;              // sectors per track
    uint16_t number_of_heads;                // number of heads
    uint32_t hidden_sectors;                 // hidden sectors
    uint32_t total_sectors_large;            // total sectors if total_sectors == 0
} fat16_boot_sector_t;

#pragma pack(pop) // restore previous packing alignment

// function prototypes for FAT16 file operations
void init_fat16();                          // initialize FAT16 file system
int read_file(const char *filename, void *buffer, size_t size); // read a file
int write_file(const char *filename, const void *buffer, size_t size); // write to a file

#endif // FAT16_H
