#include <stdint.h>
#include <kernel/peripheral.h>

#ifndef TERMINAL_H
#define TERMINAL_H
       
#define TERMINAL_SIZE 128*128
#define TERMINAL_DEFAULT_CHAR 0x7f
#define TERMINAL_DEFAULT_COLOUR 0x00
#define TERMINAL_VIEW_SIZE (SCREEN_WIDTH / 8)*(SCREEN_HEIGHT / 16)

/*uint32_t size = 128*128;
char character = 0x7f;
char colour = 0x0;*/

/*uint32_t size = (SCREEN_WIDTH / 8)*(SCREEN_HEIGHT / 16);
char character = 0x7f;
char colour = 0x0;*/

struct terminal_buffer {
        uint32_t size;
        char character;
        char colour;
};

struct terminal_screen {
        uint32_t size;
        char character;
        char colour;
};

struct terminal_buffer *terminal_start;
struct terminal_buffer *terminal_stop;
struct terminal_buffer *terminal_view;

uint32_t terminal_curr_colour;
void terminal_init(void);
void terminal_colour(char colour);
void terminal_display(void);

#endif
