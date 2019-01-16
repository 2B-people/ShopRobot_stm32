#ifndef _usart1_h
#define _usart1_h
#include "include.h"
void usart1_Init(uint32_t baud);
uint32_t usart1_write(uint8_t ch);
void usart1_print(const char *format, ...);
void usart1_putstr(const char *str);

#endif
