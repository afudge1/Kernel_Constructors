#ifndef KHEAP_H
#define KHEAP_H

#include <stdint.h>
#include <stddef.h>

// Initializes the kernel heap
void kheap_init();

// Allocates a block of memory from the kernel heap of the specified size
void* kmalloc(size_t size);

// Frees a previously allocated block of memory in the kernel heap
void kfree(void* ptr);

// Allocates and sets a block of memory from the kernel heap of the specified size
void* kzalloc(size_t size) {


#endif