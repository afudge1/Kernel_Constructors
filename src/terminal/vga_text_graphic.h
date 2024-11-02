#ifndef VGA_TEXT_GRAPHIC_H
#define VGA_TEXT_GRAPHIC_H
#include <stdint.h>

extern uint16_t* video_memory;
extern uint16_t color_byte;

void vga_init();
void vga_put_char(int32_t x, int32_t y, char c);
void vga_set(int32_t  x, int32_t  y, const char* text);
void vga_fill(int32_t  y, int32_t  x, int32_t  width, int32_t  height, char text);
void vga_copy(int32_t  x, int32_t  y, int32_t  width, int32_t  height, uint32_t tx, uint32_t ty);
char vga_get_char(int32_t x, int32_t y);
#endif