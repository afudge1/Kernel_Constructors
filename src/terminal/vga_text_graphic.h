#ifndef VGA_TEXT_GRAPHIC
#define VGA_TEXT_GRAPHIC
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20
#define VGA_ADDRESS 0xB8000
#define VGA_TEXT_WHITE_DEFAULT 0b00001111

uint8_t color_byte;
uint16_t* video_memory;

void vga_setForeground(char color);
void vga_setBackground(char color);
void vga_set(int32_t x, int32_t  y, const char* text);
void vga_fill(int32_t y, int32_t  x, int32_t  width, int32_t  height, char text);
void vga_copy(int32_t x, int32_t  y, int32_t  width, int32_t  height, uint32_t tx, uint32_t ty);
char vga_get_char(int32_t x, int32_t y); 
void vga_put_char(int32_t x, int32_t y, char c);
void vga_init();


#endif