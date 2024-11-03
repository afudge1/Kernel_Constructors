#include "idt.h"
#include "memory/memory.h"
#include "terminal/terminal.h"
struct idt_desc idt_descriptors[total_interrupts];
struct idtr_desc idtr_descriptor;

extern void* interrupt_pointer_table[total_interrupts];

extern void idt_load(struct idtr_desc* ptr);

void interrupt_handler(int interrupt, struct interrupt_frame* frame) {
    switch(interrupt) {
        default:
            terminal_input("Interrupt!");
    }
    outb(0x20, 0x20);
}

void idt_set(int interrupt_no, void* address) {
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t)address & 0x0000FFFF;
    desc->selector = 0x08;
    desc->zero = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2 = (uint32_t)address >> 16;
}

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

void idt_zero() {
    terminal_input("Divide by zero error");
}