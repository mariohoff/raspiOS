#include <kernel/gpio.h>
#include <kernel/peripheral.h>

#define GPIO_BASE (PERIPHERAL_BASE + GPIO_OFFSET)

int gpio_set_func(uint8_t gpio, uint8_t func) 
{
        if(gpio > 54 || func > 7) return -1; // fail
        
        uint8_t offset = 0;
        uint8_t pin = gpio;
        while(pin > 9) {
                pin -= 10;
                offset += 4;
        }
        volatile uint32_t *gpio_addr = (volatile uint32_t *) (GPIO_BASE+offset);

        pin = pin + (pin << 1);
        *gpio_addr |= (func << pin);

        return 0; // set function success
}

/*
 * WHEN GPIO NUM IS BIGGER THAN 31 HAS TO BE FIXED
 */
int gpio_set(uint8_t num, uint8_t val)
{
        if(num > 31) {
                num = (num >> 5);
        }
        volatile uint32_t *ADDR_SET = (volatile uint32_t *) (GPIO_BASE+0x1C);
        volatile uint32_t *ADDR_CLR = (volatile uint32_t *) (GPIO_BASE+0x28);
        if(val == 1)
                *ADDR_SET |= (1 << num);
        else
                *ADDR_CLR |= (1 << num);

        return 0;
}
