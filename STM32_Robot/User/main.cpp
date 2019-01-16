#include <stdio.h>

#include "hardwareserial.h"
#include "motor.h"
#include "timer.h"
#include "usart1.h"
#include "remote.h"
#include "oled.h"


void CM_control()


int main()
{
    SystemInit();
    initialise();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    TIM5_Int_Init(71, 9999); //100HZ		PID调速
    // TIM6_Int_Init(71, 999);  //10HZ		路径规划

    CAN_Mode_Init();
    RC_Init();

    OLED_Init();
    OLED_Clear();
  
    while(1){}

    return 0;
}
