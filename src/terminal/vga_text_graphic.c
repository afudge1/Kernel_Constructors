#include "libc.h"
#include <stddef.h>
#include "vga_text_graphic.h"

size_t strlen(char *text)
{
    size_t length = 0;
    while(text[length]!='\0')
    {
        length++;
    }
    return length;
}

void vga_init()
{
    color_byte = VGA_TEXT_WHITE_DEFAULT;
    video_mem = (uint16_t*)(VGA_ADDRESS);
}

void vga_setForeground(char color)
{
    
}

void vga_setBackground(char color)
{
    color_byte = (color_byte & 0b11110000) | (color & 0b00001111);
}

void vga_set(int32_t  x, int32_t  y, const char* text)
{
    uint32_t length = strlen(text);
    for (int i=0;i<length;i++)
    {
        vga_put_char(x+i,y,text[i]);
    }
}
void vga_fill(int32_t  y, int32_t  x, int32_t  width, int32_t  height, char text)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
        {
            vga_put_char(x,y,text);
        }
    }
}
void vga_copy(int32_t  x, int32_t  y, int32_t  width, int32_t  height, uint32_t tx, uint32_t ty)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
        {
            vga_put_char(x+tx, y+ty, vga_get_char(x,y));
        }
    }
}

char vga_get_char(int32_t x, int32_t y)
{
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT)
    {
        return ' ';
    }

    uint32_t position = (y * VGA_WIDTH) + x;
    uint16_t* vga_write_location = (uint16_t*)((uint32_t)video_memory + (uint32_t)position);

    return *(vga_write_location) >> 8;
}

void vga_put_char(int32_t x, int32_t y, char c)
{
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT)
    {
        return;
    }

    uint32_t position = (y * VGA_WIDTH) + x;
    uint16_t* vga_write_location = (uint16_t*)((uint32_t)video_memory + (uint32_t)position);
    *vga_write_location = (uint16_t)color_byte | (c << 8);
}