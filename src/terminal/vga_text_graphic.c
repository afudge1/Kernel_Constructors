#include "vga_text_graphic.h"
#include <stdint.h> 
#include "libc/string.h"
#include "terminal_config.h"

uint16_t* video_memory;
uint16_t color_byte;

void vga_init()
{
    video_memory = (uint16_t*)VGA_ADDRESS;
    color_byte = VGA_TEXT_WHITE_DEFAULT;
    vga_fill(0,0,VGA_WIDTH,VGA_HEIGHT,' ');
}
void vga_set(int32_t  x, int32_t  y, const char* text)
{
    uint32_t length = strlen(text);
    for (int i=0;i<length;i++)
    {
        vga_put_char(x+i,y,text[i]);
    }
}

void vga_put_char(int32_t x, int32_t y, char c)
{
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT)
    {
        return;
    }

    uint32_t position = (y * VGA_WIDTH) + x;
    video_memory[position] = (uint16_t)c | (color_byte << 8);
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
    return video_memory[position] & 0xFF;
}
