#include "libc.h"
#include "vga_text_graphic.h"

void init_vga()
{
    color_byte = 0b00001111;
    video_mem = (uint16_t*)(VGA_ADDRESS);
    fill(0,0,VGA_WIDTH, VGA_HEIGHT, " ");
}

void set(int32_t  x, int32_t  y, char* text)
{
    uint32_t length = strlen(text);
    for (int i=0;i<length;i++)
    {
        vga_put_char(x+i,y,text[i]);
    }
}
void fill(int32_t  y, int32_t  x, int32_t  width, int32_t  height, char text)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
        {
            vga_put_char(x,y,text)
        }
    }
}
void copy(int32_t  x, int32_t  y, int32_t  width, int32_t  height, int32_t tx, int32_t ty)
{
    for (int y=0;y<height;y++)
    {
        for (int x=0;x<width;x++)
        {
            
        }
    }
}

char vga_get_char(int32_t x, int32_t y)
{
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT)
    {
        return 0;
    }

    uint16_t* vga_write_location = ((uint32_t)video_mem + (uint32_t)position)

    return *(vga_write_location & 0b11111111);
}

void vga_put_char(int32_t x, int32_t y, char c)
{
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT)
    {
        return;
    }

    uint32_t position = (y * VGA_WIDTH) + x;
    uint16_t* vga_write_location = ((uint32_t)video_mem + (uint32_t)position)
    *vga_write_location = (uint16_t)c | (color_byte << 8);
}