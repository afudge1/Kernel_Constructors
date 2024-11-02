#include "vga_text_graphic.c"
#include "libc.h"
void init_vga()
{
    video_mem = (uint16_t*)(0xB8000);
    fill(0,0,VGA_WIDTH, VGA_HEIGHT, " ");
}

void set(int32_t  x, int32_t  y, char* text)
{

}
void fill(int32_t  y, int32_t  x, int32_t  width, int32_t  height, char text)
{

}
void copy(int32_t  x, int32_t  y, int32_t  width, int32_t  height, int32_t tx, int32_t ty)
{
    
}

void vga_put_char(int32_t x, int32_t y, char c)
{
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT)
    {
        return;
    }

    uint32_t position = (y * VGA_WIDTH) + x;
    uint8_t* vga_write_location = ((uint32_t)video_mem + (uint32_t)position)
    *vga_write_location = c;
}