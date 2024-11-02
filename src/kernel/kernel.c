#include "kernel.h"
#include <stdint.h>

int kmain() {
    uint16_t* buffer = (uint16_t*)0xb8000;
    *buffer = (uint16_t)0x020F;
    return 0;
}