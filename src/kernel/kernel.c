#include "kernel.h"
#include <stdint.h>

void display_char(uint16_t character, int position);

int kmain() {
    uint16_t* buffer = (uint16_t*)0xb8000;
    *buffer = (uint16_t)0x020F;
    return 0;
}