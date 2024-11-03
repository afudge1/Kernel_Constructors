#include "terminal.h"
#include <stdint.h>
#include "vga_text_graphic.c"
//#include "libc/libc.h"

char cwd[MAX_TERMINAL_PREFIX_BUFF+1];
char terminal_buff[(MAX_TEMRINAL_HISTORY+1)* VGA_WIDTH];
char terminal_input_buff[MAX_INPUT_BUFFER+1];
int terminal_active = 1;
uint32_t textbuffSize = 1;

void terminal_init()
{
    vga_fill(0,0,VGA_WIDTH,VGA_HEIGHT,' ');
    for (int i=0;i<(MAX_TEMRINAL_HISTORY+1)* VGA_WIDTH;i++) 
    {
        terminal_buff[i] = 0;
    }

}


int terminal_input(const char* text)
{
    //uint32_t textLength = strlen(text);
    //char buffer[VGA_WIDTH];
    //uint32_t textIndex = 0;

    vga_copy(0,1,VGA_WIDTH,VGA_HEIGHT-2,0,-1);
    vga_set(0,VGA_HEIGHT-1, text);
    return 0;

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