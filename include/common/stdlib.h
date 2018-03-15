#ifndef STDLIB_H
#define STDLIB_H

void memcpy(void * dst, void * src, int bytes); /* copy N bytes from src to dst */
void bzero(void * dst, int bytes);/* zero out N bytes */
char * itoa(int i);
int atoi(char *num);

#endif
