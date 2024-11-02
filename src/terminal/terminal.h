#ifndef TERMINAL_H
#define TERMINAL_H
#include "vga_text_graphic.h"
#include <stdint.h>
char cwd[MAX_TERMINAL_PREFIX_BUFF+1];
char terminal_buff[(MAX_TEMRINAL_HISTORY+1)* VGA_WIDTH];
char terminal_input_buff[MAX_INPUT_BUFFER+1];
int terminal_active = 1;
uint32_t textbuffSize = 1;

//char** terminal_text_history = (char* )malloc(sizeof(char*) * MAX_TEMRINAL_HISTORY);

void terminal_init();
int terminal_input(const char* text);
void terminal_enter();
void terminal_backspace();

void keyboard_input_handler(char c);

void terminal_pause_render();
void terminal_resume_render();

void terminal_reload();


#endif