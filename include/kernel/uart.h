#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>

/*static inline void mmio_write(uint32_t reg, uint32_t data);
static inline uint32_t mmio_read(uint32_t reg);
static inline void delay(int32_t count);*/

void uart_init();
void uart_putc(unsigned char c);
unsigned char uart_getc();
void uart_puts(const char* str);

#endif
