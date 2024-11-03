#include "idt.h"

struct idt_desc idt_descriptors[total_interrupts];
struct idtr_desc idtr_descriptor;

extern void* interrupt_pointer_table[total_interrupts];

void idt_init() {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base = (uint32_t)idt_descriptors;

    for(int i = 0; i < total_interrupts; i++) {
        idt_set(i, interrupt_pointer_table[i]);
    }
    idt_set(0, idt_zero);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}

idt_zero() {
    printf("Divide by zero error");
}
