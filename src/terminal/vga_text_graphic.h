#ifndef VGA_TEXT_GRAPHIC
#define VGA_TEXT_GRAPHIC
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20
#define VGA_ADDRESS 0xB8000

uint8_t color_byte;
uint16_t* video_memory;

void set(int32_t x, int32_t  y, char* text);
void fill(int32_t y, int32_t  x, int32_t  width, int32_t  height, char text);
void copy(int32_t x, int32_t  y, int32_t  width, int32_t  height, int32_t tx, int32_t ty);
char vga_get_char(int32_t x, int32_t y); 
void vga_put_char(int32_t x, int32_t y, char c);
void init_vga();


#endif