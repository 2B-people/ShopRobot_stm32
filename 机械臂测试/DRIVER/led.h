#ifndef led_h
#define led_h
#include "include.h"
void Ledbeep_init(void);
void LED_On_Off(char status, uint16_t LED_Pin);
void SW_LED(char led_nemberx, char status);
void Beep_On_Off(char status);
#endif
