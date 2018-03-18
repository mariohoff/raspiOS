#include <stdint.h>
#include <kernel/peripheral.h>

#ifndef TERMINAL_H
#define TERMINAL_H
       
#define TERMINAL_SIZE ((SCREEN_WIDTH / 8)*128)
#define TERMINAL_DEFAULT_CHAR 0x7f
#define TERMINAL_DEFAULT_COLOUR 0x00
#define TERMINAL_VIEW_SIZE (SCREEN_WIDTH / 8)*(SCREEN_HEIGHT / 16)

/*uint32_t size = 128*128;
char character = 0x7f;
char colour = 0x0;*/

/*uint32_t size = (SCREEN_WIDTH / 8)*(SCREEN_HEIGHT / 16);
char character = 0x7f;
char colour = 0x0;*/

uint32_t *terminal_start;
uint32_t *terminal_stop;
uint32_t *terminal_view;

uint16_t terminal_buffer[TERMINAL_SIZE];
uint16_t terminal_screen[TERMINAL_VIEW_SIZE];

uint32_t terminal_curr_colour;
void terminal_init(void);
void terminal_colour(uint8_t colour);
void terminal_display(void);

#endif
