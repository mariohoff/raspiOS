#include <common/stdio.h>
#include <kernel/uart.h>

void putc(char c) 
{
        uart_putc(c);
}

char getc(void)
{
        return uart_getc();
}

void puts(const char *s)
{
        int i = 0;
        while(s[i] != '\0') {
                putc(s[i++]);
        }
}


void gets(char *buf, int buflen)
{
        int i;
        char c;
        //leave a spot for null char in buffer
        for(i = 0; (c = getc()) != '\r' && buflen > 1; i++, buflen--) {
                putc(c);
                buf[i] = c;
        }

        putc('\n');
        if(c == '\n')
                buf[i] = '\0';
        else
                buf[buflen-1] = '\0';
}
