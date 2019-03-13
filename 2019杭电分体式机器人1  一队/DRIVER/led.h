#ifndef led_h
#define led_h
#include "include.h"
void Ledbeep_init(void);
void LED_On_Off(char status, uint16_t LED_Pin);
void Beep_On_Off(char status);
#define LED1 PCout(0)
#define LED2 PCout(1)
#define LED3 PFout(10)
#endif
