#ifndef _bottom_sensor
#define _bottom_sensor
#include "include.h"
#define infrared1  GPIO_ReadInputDataBit(infrared_PORT1,infrared_PIN1)
#define infrared2  GPIO_ReadInputDataBit(infrared_PORT2,infrared_PIN2)
void infrared_Init(void);
#endif
