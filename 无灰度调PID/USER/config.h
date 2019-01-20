#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "stm32f10x.h"
#include "millisecondtimer.h"

#define VEL_PUBLISH_RATE 10    //10HZ
#define LAS_PUBLISH_RATE 100   //100HZ
#define REMOTE_PUBLISH_RATE 10 //10HZ
#define PI 3.1415926

//#define K_P 2.5  // P constant
//#define K_I 0.08 // I constant
//#define K_D 0.1  // D constant


#define True 1
#define False 0

/** motor param **/
#define MAX_RPM 8000      //motor's maximum RPM最大转速
#define COUNTS_PER_REV 19 //wheel encoder's no of ticks per rev(gear_ratio * pulse_per_rev)减速比
//#define LENGTH_A 0.165
//#define LENGTH_B 0.12
#define WHEEL_DIAMETER 0.055 //wheel's diameter in meters直径
//#define YT_WHELL_DIAMETER 1
//#define YT_MAX_RPM 600

/** LED config **/
#define LED_PIN1 GPIO_Pin_0
#define LED_PIN2 GPIO_Pin_1
#define LED_PIN3 GPIO_Pin_2
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_CLK RCC_APB2Periph_GPIOC

/** LASER config **/
#define CHOSE_LAS_PIN1 GPIO_Pin_0
#define CHOSE_LAS_PORT1 GPIOB
#define CHOSE_LAS_CLK1 RCC_APB2Periph_GPIOB //接数据选择器

#define CHOSE_LAS_PIN2 GPIO_Pin_1
#define CHOSE_LAS_PORT2 GPIOB
#define CHOSE_LAS_CLK2 RCC_APB2Periph_GPIOB //接数据选择器


/**bottom_sensor config**/
#define infrared_PIN1          GPIO_Pin_2
#define infrared_PORT1          GPIOE
#define infrared_CLK1          RCC_APB2Periph_GPIOE

#define infrared_PIN2          GPIO_Pin_3
#define infrared_PORT2          GPIOE
#define infrared_CLK2          RCC_APB2Periph_GPIOE





/**key config**/
#define key_PIN1          GPIO_Pin_4
#define key_PIN2          GPIO_Pin_5
#define key_PIN3          GPIO_Pin_6
#define key_PIN4          GPIO_Pin_7
#define key_PIN5          GPIO_Pin_8
#define key_PIN6          GPIO_Pin_9

#define key_PORT          GPIOE
#define key_CLK         RCC_APB2Periph_GPIOE


#endif // _CONFIG_H_
