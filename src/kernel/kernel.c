#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <common/stdio.h>
#include <kernel/gpio.h>
#include <kernel/peripheral.h>
#include <kernel/framebuffer.h>
#include <kernel/draw.h>

static void spin_sleep_us(unsigned int us)
{
        unsigned int i;
        for(i = 0; i < us*6; i++) {
                asm volatile("nop");
        }
}

static void spin_sleep_ms(unsigned int ms) 
{
        spin_sleep_us(ms * 1000);
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
        // Declare as unused
        (void) r0;
        (void) r1;
        (void) atags;


        gpio_set_func(18, 1);
        uart_init();
        keyboard_init();

        while(framebuffer_init());
        draw_set_graphicsaddress(fbinfo.buf);

        draw_set_forecolour(0xFFFFFF);
        char *string = "Hello World. Maybe my keyboard input is working now!";
        draw_string(string, 0, 0);
        uint32_t pink = 0xff00ff;
        uint32_t black = 0x000000;
        draw_set_forecolour(pink); //pink
        
        /*keyboard_init();*/
        int x = 0, y = 2;
        const int X_MAX = SCREEN_WIDTH/CHAR_WIDTH;
        const int Y_MAX = SCREEN_HEIGHT/CHAR_HEIGHT;

        char c;

        while (1) {
                keyboard_update();
                c = keyboard_getchar();
                if(c != 0) {
                        switch(c) {
                                case 127:
                                case 8:
                                        draw_set_forecolour(black);
                                        draw_character(' ', --x, y);
                                        draw_set_forecolour(pink);
                                        break;
                                case '\n':
                                        puts("\r\n");
                                        x = 0;
                                        y++;
                                        break;
                                default:
                                        draw_character(c, x, y);
                                        putc(c);
                                        x++;
                                        break;
                        }
                }

                if(x >= X_MAX) {
                        x = 0;
                        y++;
                        puts("\r\n");
                }
                if(y >= Y_MAX) {
                        y = 0;
                }

                /*puts("LED AN\r\n");
                gpio_set(18, 1);
                spin_sleep_ms(500);
                puts("LED AUS\r\n");
                gpio_set(18, 0);
                spin_sleep_ms(500);*/
        }
}
