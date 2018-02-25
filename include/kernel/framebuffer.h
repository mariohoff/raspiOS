#include <stdint.h>
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

typedef struct framebuffer_info {
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint32_t * buf;
    uint32_t buf_size;
    uint32_t chars_width;
    uint32_t chars_height;
    uint32_t chars_x;
    uint32_t chars_y;
} framebuffer_info_t;


framebuffer_info_t fbinfo;

int framebuffer_init(void);

#endif
