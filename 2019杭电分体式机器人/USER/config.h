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

#define K_P 2.5  // P constant
#define K_I 0.08 // I constant
#define K_D 0.1  // D constant

#define YT_KP 3
#define YT_KI 0
#define YT_KD 0

#define True 1
#define False 0

/** motor param **/
#define MAX_RPM 8000      //motor's maximum RPM最大转速
#define COUNTS_PER_REV 19 //wheel encoder's no of ticks per rev(gear_ratio * pulse_per_rev)减速比
#define LENGTH_A 0.165
#define LENGTH_B 0.12
#define WHEEL_DIAMETER 0.127 //wheel's diameter in meters直径
#define YT_WHELL_DIAMETER 1
#define YT_MAX_RPM 600

/** LED config **/
#define RIKI_LED_PIN GPIO_Pin_12
#define RIKI_LED_GPIO_PORT GPIOA
#define RIKI_LED_GPIO_CLK RCC_APB2Periph_GPIOA

/** LASER config **/
#define CHOSE_LAS_PIN1 GPIO_Pin_0
#define CHOSE_LAS_PORT1 GPIOB
#define CHOSE_LAS_CLK1 RCC_APB2Periph_GPIOB //接数据选择器

#define CHOSE_LAS_PIN2 GPIO_Pin_1
#define CHOSE_LAS_PORT2 GPIOB
#define CHOSE_LAS_CLK2 RCC_APB2Periph_GPIOB //接数据选择器

#endif // _CONFIG_H_
