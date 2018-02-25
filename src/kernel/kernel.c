#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <kernel/gpio.h>
#include <kernel/framebuffer.h>
#include <kernel/draw.h>
#include <kernel/peripheral.h>

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

//loop <delay> times in a way that the compiler wont optiimize away
static inline void delay(int32_t count)
{
        asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n" 
                        : "=r"(count): [count]"0"(count) : "cc");
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
        uart_puts("Hello Kernel World\n");
        uart_puts("Set GPIO 18 to output.\n");

        while(framebuffer_init());
        draw_set_graphicsaddress(fbinfo.buf);

        draw_set_forecolour(0xFFFFFF);
        char *string = "Hello World\n Is this really working?\t Do tabs work?";
        draw_string(string, 0, 0);
        draw_line(0,16,639,16);

        draw_set_forecolour(0x999999);
        string = "Testing another colour out.";
        draw_string(string, 0, 3);

        draw_set_forecolour(0xff00ff);
        char *s;
        draw_string("Hello World", 0, 5);

        while (1) {
                gpio_set(18, 1);
                spin_sleep_ms(500);
                gpio_set(18, 0);
                spin_sleep_ms(500);
        }
}
