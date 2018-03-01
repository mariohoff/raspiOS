#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <common/stdio.h>
#include <kernel/gpio.h>
#include <kernel/framebuffer.h>
#include <kernel/draw.h>
#include <kernel/peripheral.h>
#include <kernel/input.h>

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
        puts("Hello Kernel World\n");
        puts("Set GPIO 18 to output.\n");

        /*while(framebuffer_init());
        draw_set_graphicsaddress(fbinfo.buf);

        draw_set_forecolour(0xFFFFFF);
        char *string = "Hello World. Maybe my keyboard input is working now!";
        draw_string(string, 0, 0);
        draw_set_forecolour(0xff00ff); //pink
        
        keyboard_init();*/

        while (1) {
                puts("LED ON!\n");
                gpio_set(18, 1);
                spin_sleep_ms(500);
                puts("LED OFF!\n");
                gpio_set(18, 0);
                spin_sleep_ms(500);
        }
}
