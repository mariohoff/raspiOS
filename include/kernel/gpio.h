#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

int gpio_set_func(uint8_t gpio, uint8_t func);
int gpio_set(uint8_t num, uint8_t val);

#endif
