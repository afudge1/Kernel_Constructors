#include "terminal.h"
#include <stdint.h>
#include "libc/string.h"
#include "vga_text_graphic.h"
#include "terminal_config.h"

char terminal_buff[VGA_WIDTH+1];
uint32_t terminal_buff_i;

void terminal_init()
{
    terminal_buff_i = 0;
    for (int i=0;i<VGA_WIDTH+1;i++)
    {
        terminal_buff[i] = ' ';
    }
    vga_init();
    vga_fill(0,0,VGA_WIDTH,VGA_HEIGHT,' ');
    //for (int i=0;i<(MAX_TEMRINAL_HISTORY+1)* VGA_WIDTH;i++) 
    //{
    //    terminal_buff[i] = 0;
    //}

}

void terminal_enter()
{
    terminal_input(terminal_buff);
    terminal_buff_i = 0;

    if (strcmp("aa",terminal_buff))
    {
        
    }

    for (int i=0;i<VGA_WIDTH+1;i++)
    {
        terminal_buff[i] = ' ';
    }
    
    vga_set(0,VGA_HEIGHT-1,terminal_buff);
}
void terminal_push_cli(char c)
{
    terminal_buff[terminal_buff_i] = c;
    terminal_buff_i++;
    vga_set(0,VGA_HEIGHT-1,terminal_buff);
}

int terminal_input(char* text)
{
    //uint32_t textLength = strlen(text);
    //char buffer[VGA_WIDTH];
    //uint32_t textIndex = 0;
    char emptyText[VGA_WIDTH+1];
    for (int i=0;i<VGA_WIDTH+1;i++)
    {
        emptyText[i] = ' ';
    }
    emptyText[VGA_WIDTH] = '\0';
    vga_copy(0,0,VGA_WIDTH,VGA_HEIGHT,0,-1);
    vga_set(0,VGA_HEIGHT-2, emptyText);
    vga_set(0,VGA_HEIGHT-2, text);
    return 0;

}

