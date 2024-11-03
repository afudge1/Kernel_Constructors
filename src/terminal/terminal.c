#include "terminal.h"
#include <stdint.h>
#include "libc/string.h"
#include "vga_text_graphic.h"
#include "terminal_config.h"

void terminal_init()
{
    vga_init();
    vga_fill(0,0,VGA_WIDTH,VGA_HEIGHT,' ');
    //for (int i=0;i<(MAX_TEMRINAL_HISTORY+1)* VGA_WIDTH;i++) 
    //{
    //    terminal_buff[i] = 0;
    //}

}


int terminal_input(const char* text)
{
    //uint32_t textLength = strlen(text);
    //char buffer[VGA_WIDTH];
    //uint32_t textIndex = 0;
    vga_copy(0,0,VGA_WIDTH,VGA_HEIGHT,0,-1);
    vga_set(0,VGA_HEIGHT-1, text);
    return 0;

}

