#include <kernel/draw.h>
#include <kernel/framebuffer.h>
#include <kernel/peripheral.h>
#include <kernel/chars_pixels.h>

static uint32_t* graphics_addr;
static uint32_t fore_colour;

void draw_set_graphicsaddress(uint32_t *addr)
{
        graphics_addr = addr;
}

/**
 * set the foreground colour of pixels to be drawn
 */
int draw_set_forecolour(uint32_t colour)
{
        fore_colour = (colour << 4) | colour;
        return 0;
}

int draw_pixel(uint32_t px, uint32_t py)
{
        uint32_t width = SCREEN_WIDTH;
        uint32_t height = SCREEN_HEIGHT;
        if(px > width || py > height)
                return -1;

        /*640x480, high colour specific*/
        px = (py*width)+px;
        volatile uint32_t *pixel_addr =
                (volatile uint32_t *) (graphics_addr + (px));

        *pixel_addr = fore_colour;

        return 0;
}

int draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
        int32_t dx;
        int32_t sx;
        int32_t dyn;
        int32_t sy;
        int32_t err;

        if(x1 > x0) {
                dx = x1 - x0;
                sx = 1;
        } else {
                dx = x0 - x1;
                sx = -1;
        }

        if(y1 > y0) {
                dyn = y0 - y1;
                sy = 1;
        } else {
                dyn = y1 - y0;
                sy =  -1;
        }

        err = dx + dyn;

        while(x0 != x1+sx && y0 != y1+sy) {
                draw_pixel(x0, y0);
                if((err << 1) >= dyn) {
                        x0 += sx;
                        err += dyn;
                }
                if((err << 1) <= dx) {
                        y0 += sy;
                        err += dx;
                }

        }

        return 0;
}/*draw_line()*/

void draw_character(char c, uint32_t x, uint32_t y)
{
        uint32_t x_max = SCREEN_WIDTH/CHAR_WIDTH;
        uint32_t y_max = SCREEN_HEIGHT/CHAR_HEIGHT;

        if(x > x_max || y > y_max)
                return;

        const uint8_t *bmp = font(c);
        uint8_t w, h, mask;
        for(w = 0; w < CHAR_WIDTH; w++) {
                for(h = 0; h < CHAR_HEIGHT; h++) {
                        mask = 1 << (w);
                        if(bmp[h] & mask)
                                draw_pixel(x*CHAR_WIDTH + w, y*CHAR_HEIGHT + h);
                }
        }
}/*draw_character();*/

void draw_string(char *s, uint32_t x, uint32_t y)
{
        uint32_t x0 = x;
        int i;

        while(*s != '\0') {
                if(*s == '\n') {
                        y++;
                        x = x0 -1;
                } else if(*s == '\t') {
                        for(i= 0; i < 4; i++) {
                                draw_character(' ', x++, y);
                        }
                } else {
                        draw_character(*s, x++, y);
                }
                s++;
        }
}/*draw_string()*/


