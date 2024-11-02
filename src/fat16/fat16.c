#include "fat16.h"
#include "syscall_handler.h"
#include <stdint.h>
#include <string.h>

#define SECTOR_SIZE 512
#define MAX_FILENAME_LENGTH 13 // 8.3 filename format
#define CLUSTER_SIZE (boot_sector.sectors_per_cluster * SECTOR_SIZE)

static fat16_boot_sector_t boot_sector;

// Function prototypes
static int locate_file(const char *filename);
static int read_cluster(uint32_t cluster, void *buffer);
static int write_cluster(uint32_t cluster, const void *buffer);
static uint32_t get_next_cluster(uint32_t cluster);
static int allocate_cluster();

/*
// Initialize the video memory
uint16_t* video_memory = (uint16_t*)0xb8000;
*video_memory = (uint16_t)0x020F;  // Set character and attribute (e.g., ' ' and bright white)

// Initialize the FAT16 filesystem
init_fat16();

// Example: Read a file from the FAT16 filesystem
const char *filename = "FILE.TXT"; // Example filename (must match your FAT16 file)
char file_buffer[512];  // Buffer to hold the file data
int bytes_read = read_file(filename, file_buffer, sizeof(file_buffer)); // Read the file

if (bytes_read > 0) {
    // Optionally, display the contents to the screen
    for (int i = 0; i < bytes_read; i++) {
        // Replace null characters with spaces for display
        char display_char_value = (file_buffer[i] == '\0') ? ' ' : file_buffer[i];

        // Display character at corresponding video memory position
        display_char(display_char_value | 0x0F00, i); // Set attribute to white
    }
}

// Function to display a character at a specific position in video memory
void display_char(uint16_t character, int position) {
    uint16_t* video_memory = (uint16_t*)0xb8000; // Video memory base address
    video_memory[position] = character; // Write character and attribute
}
*/


void init_fat16() {
    // read boot sector
    syscall(SYS_READ, &boot_sector, SECTOR_SIZE);

    // Verify if it's a FAT16 filesystem
    if (boot_sector.bytes_per_sector != SECTOR_SIZE || boot_sector.num_fats == 0) {
        // Not a FAT16 filesystem, handle error
        return; // Consider logging the error
    }
}

int read_file(const char *filename, void *buffer, size_t size) {
    uint32_t cluster = locate_file(filename);
    if (cluster < 0) {
        return -1; // File not found
    }

    size_t bytes_read = 0;
    while (bytes_read < size) {
        if (read_cluster(cluster, (uint8_t *)buffer + bytes_read) < 0) {
            return -1; // Read error
        }
        bytes_read += CLUSTER_SIZE; // Read entire cluster
        cluster = get_next_cluster(cluster); // Get next cluster
        if (cluster == 0) break; // Stop if there are no more clusters
    }

    return bytes_read; // Return number of bytes read
}

int write_file(const char *filename, const void *buffer, size_t size) {
    uint32_t cluster = locate_file(filename);
    if (cluster < 0) {
        // Handle file not found; may need to create it
        cluster = allocate_cluster(); // Allocate cluster for new file
        if (cluster < 0) {
            return -1; // Allocation error
        }
    }

    size_t bytes_written = 0;
    while (bytes_written < size) {
        if (write_cluster(cluster, (const uint8_t *)buffer + bytes_written) < 0) {
            return -1; // Write error
        }
        bytes_written += CLUSTER_SIZE; // Write entire cluster
        cluster = allocate_cluster(); // Allocate more clusters if necessary
        if (cluster < 0) break; // Stop if allocation fails
    }

    return bytes_written; // Return number of bytes written
}

static int locate_file(const char *filename) {
    uint32_t root_dir_start = (boot_sector.reserved_sectors + (boot_sector.num_fats * boot_sector.fat_size)) * boot_sector.bytes_per_sector;
    uint32_t dir_entry_offset = 0;

    // Calculate the number of entries in the root directory
    uint32_t num_entries = boot_sector.max_root_dir_entries;

    for (uint32_t i = 0; i < num_entries; i++) {
        // Read each directory entry
        uint8_t dir_entry[32]; // Size of a single directory entry
        if (syscall(SYS_READ, (void *)(root_dir_start + dir_entry_offset), dir_entry, sizeof(dir_entry)) < 0) {
            return -1; // Error reading directory
        }

        // Check if the entry is unused
        if (dir_entry[0] == 0x00) {
            break; // No more entries
        }

        // Check if the entry is deleted (0xE5)
        if (dir_entry[0] == 0xE5) {
            dir_entry_offset += sizeof(dir_entry);
            continue; // Skip deleted entries
        }

        // Extract the filename and compare
        char entry_filename[MAX_FILENAME_LENGTH] = {0};
        strncpy(entry_filename, (char *)dir_entry, 8);
        entry_filename[8] = '\0'; // Null-terminate the filename

        // Handle the extension
        if (dir_entry[8] != ' ') {
            strncat(entry_filename, ".", 1);
            strncat(entry_filename, (char *)(dir_entry + 8), 3); // Add extension
        }

        // Compare with the given filename
        if (strncmp(entry_filename, filename, MAX_FILENAME_LENGTH) == 0) {
            // Found the file; return the starting cluster
            uint16_t first_cluster_low = *(uint16_t *)(dir_entry + 26);
            uint16_t first_cluster_high = *(uint16_t *)(dir_entry + 20);
            return (first_cluster_high << 16) | first_cluster_low; // Return full cluster number
        }

        dir_entry_offset += sizeof(dir_entry); // Move to the next entry
    }

    return -1; // File not found
}

static int read_cluster(uint32_t cluster, void *buffer) {
    uint32_t cluster_start = (boot_sector.reserved_sectors + (boot_sector.num_fats * boot_sector.fat_size) + 
                              (cluster - 2) * boot_sector.sectors_per_cluster) * boot_sector.bytes_per_sector;
    return syscall(SYS_READ, (void *)cluster_start, buffer, CLUSTER_SIZE);
}

static int write_cluster(uint32_t cluster, const void *buffer) {
    uint32_t cluster_start = (boot_sector.reserved_sectors + (boot_sector.num_fats * boot_sector.fat_size) + 
                              (cluster - 2) * boot_sector.sectors_per_cluster) * boot_sector.bytes_per_sector;
    return syscall(SYS_WRITE, (void *)cluster_start, buffer, CLUSTER_SIZE);
}

static uint32_t get_next_cluster(uint32_t cluster) {
    uint16_t fat_entry;
    uint32_t fat_start = boot_sector.reserved_sectors * boot_sector.bytes_per_sector;
    uint32_t fat_offset = (cluster + 2) * sizeof(fat_entry); // Each FAT16 entry is 2 bytes

    // Read the FAT entry corresponding to the current cluster
    if (syscall(SYS_READ, (void *)(fat_start + fat_offset), &fat_entry, sizeof(fat_entry)) < 0) {
        return 0; // Error reading FAT
    }

    // Check for end of file markers (0xFFF8 to 0xFFFF)
    if (fat_entry >= 0xFFF8) {
        return 0; // End of file or bad cluster
    }

    return fat_entry; // Return the next cluster
}

static int allocate_cluster() {
    uint32_t fat_start = boot_sector.reserved_sectors * boot_sector.bytes_per_sector;
    uint16_t fat_entry;

    // Loop through the FAT to find a free cluster
    for (uint32_t cluster = 2; cluster < (boot_sector.total_sectors_large / boot_sector.sectors_per_cluster); cluster++) {
        uint32_t fat_offset = cluster * sizeof(fat_entry);

        // Read the FAT entry
        if (syscall(SYS_READ, (void *)(fat_start + fat_offset), &fat_entry, sizeof(fat_entry)) < 0) {
            return -1; // Error reading FAT
        }

        // Check if the cluster is free (value is 0)
        if (fat_entry == 0) {
            // Mark the cluster as used (e.g., set it to a marker value)
            uint16_t next_cluster_value = 0xFFF8; // Mark as end of file
            if (syscall(SYS_WRITE, (void *)(fat_start + fat_offset), &next_cluster_value, sizeof(next_cluster_value)) < 0) {
                return -1; // Error writing to FAT
            }
            return cluster; // Return the allocated cluster
        }
    }

    return -1; // No free clusters found
}
