#include <stdint.h>

#ifndef DRAW_H
#define DRAW_H

void draw_set_graphicsaddress(uint32_t *addr);
int draw_set_forecolour(uint32_t colour);
int draw_pixel(uint32_t px, uint32_t py);
int draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void draw_character(char c, uint32_t x, uint32_t y);
void draw_string(char* s, uint32_t x, uint32_t y);
#endif
