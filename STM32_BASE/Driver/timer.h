#ifndef timer_h
#define timer_h

#include "stm32f10x.h"
void TIM2_Int_Init(uint16_t arr,uint16_t psc);
void TIM3_Int_Init(uint16_t arr,uint16_t psc);
void TIM4_Int_Init(uint16_t arr,uint16_t psc);
void TIM5_Int_Init(uint16_t arr,uint16_t psc);
void TIM6_Int_Init(uint16_t arr,uint16_t psc);

#endif

