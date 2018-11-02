<<<<<<< HEAD
#ifndef remote_h
#define remote_h
#include "stm32f10x.h"



#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)

#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)

#define RC_FRAME_LENGTH 18u

typedef __packed struct
{
	uint16_t ch0;
	uint16_t ch1;
	uint16_t ch2;
	uint16_t ch3;
	uint8_t s1;
	uint8_t s2;
}REMOTE;




void RC_Init(void);
void RemoteDataProcess(volatile uint8_t *pData);




=======
#ifndef remote_h
#define remote_h
extern "C"{
#include "stm32f10x.h"
}


#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)

#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)

#define RC_FRAME_LENGTH 18u

typedef __packed struct
{
	uint16_t ch0;
	uint16_t ch1;
	uint16_t ch2;
	uint16_t ch3;
	uint8_t s1;
	uint8_t s2;
}REMOTE;




void RC_Init(void);
void RemoteDataProcess( uint8_t *pData);




>>>>>>> d13f5f0ab27e128bee545c36e70a70630e8c91e1
#endif