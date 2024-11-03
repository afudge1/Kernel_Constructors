#ifndef TERMINAL_H
#define TERMINAL_H
#include "vga_text_graphic.h"
#include "terminal_config.h"
#include <stdint.h>

//char** terminal_text_history = (char* )malloc(sizeof(char*) * MAX_TEMRINAL_HISTORY);

extern char cwd[MAX_TERMINAL_PREFIX_BUFF+1];
extern char terminal_input_buff[MAX_INPUT_BUFFER+1];
extern int terminal_active;
extern uint32_t textbuffSize;

void terminal_init();
void terminal_push_cli(char c);
void terminal_enter();
int terminal_input(char* text);


#endif