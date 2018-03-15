#include <kernel/peripheral.h>

#ifndef TERMINAL_H
#define TERMINAL_H

struct terminal_buffer {
        uint32_t size = 128*128;
        char character = 0x7f;
        char colour = 0x0;
};

struct terminal_screen {
        uint32_t size = (SCREEN_WIDTH / 8)*(SCREEN_HEIGHT / 16);
        char character = 0x7f;
        char colour = 0x0;
}

struct terminal_buffer terminal_start;
struct terminal_buffer terminal_stop;
struct terminal_buffer terminal_view;
uint32_t terminal_colour;

void terminal_colour(char colour);

#endif
