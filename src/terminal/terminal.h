#ifndef TERMINAL_H
#define TERMINAL_H
#include "vga_text_graphic.h"
#include "terminal_config.h"
#include <stdint.h>

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