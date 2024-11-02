#ifndef VGA_TEXT_GRAPHIC
#define VGA_TEXT_GRAPHIC
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20


uint16_t* video_memory = 0;

void set(int32_t x, int32_t  y, char* text);
void fill(int32_t y, int32_t  x, int32_t  width, int32_t  height, char text);
void copy(int32_t x, int32_t  y, int32_t  width, int32_t  height, int32_t tx, int32_t ty);
void vga_put_char(int32_t x, int32_t y, char c);
void init_vga();


#endif