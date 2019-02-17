#ifndef _bottom_sensor
#define _bottom_sensor

#include "include.h"
#define infrared1  GPIO_ReadInputDataBit(infrared_PORT1,infrared_PIN1)
#define infrared2  GPIO_ReadInputDataBit(infrared_PORT2,infrared_PIN2)
#define infrared3  GPIO_ReadInputDataBit(infrared_PORT3,infrared_PIN3)
#define infrared4  GPIO_ReadInputDataBit(infrared_PORT4,infrared_PIN4)
#define infrared5  GPIO_ReadInputDataBit(infrared_PORT5,infrared_PIN5)
void infrared_Init(void);
void ChangeCoordinate(void);
void ROTATE(uint8_t Clockwise);//ClockwiseÎª1Ë³Ê±Õë
void toFetch(void);
#endif
