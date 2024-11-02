#include "terminal.h"
#include "stdint.h"
#include "vga_text_graphic.c"
//#include "libc.h"


void terminal_init()
{
    vga_fill(0,0,VGA_WIDTH,VGA_HEIGHT,' ');
    for (int i=0;i<(MAX_TEMRINAL_HISTORY+1)* VGA_WIDTH;i++)
    {
        terminal_buff = 0;
    }

}


void terminal_input(const char* text)
{
    uint32_t textLength = strlen(text)
    char buffer[VGA_WIDTH];
    uint32_t textIndex = 0;

    vga_copy(0,1,VGA_WIDTH,VGA_HEIGHT-2,0,-1);
    vga_set(0,VGA_HEIGHT-1, text);

}
void terminal_enter()
{

}
void terminal_backspace()
{

}

void keyboard_input_handler(char c)
{

}

void terminal_pause_render()
{

}
void terminal_resume_render()
{

}

void terminal_reload()
{
    vga_fill(0,0,VGA_WIDTH,VGA_HEIGHT,' '); //clear screen
}