#ifndef _connect_h
#define _connect_h
#include "include.h"
typedef struct
{
	uint8_t Type;
	uint8_t Date_1;
	uint8_t Date_2;
	uint8_t Date_3;
	uint8_t Date_4;
}Connect_TypedefU;
typedef struct
{
	uint8_t Type;
	int8_t Date_1;
	int8_t Date_2;
	int8_t Date_3;
	int8_t Date_4;
}Connect_Typedef;


enum
{
	SVEL=1,
	SREMOTE,
	SLAS,
	SSTATE
};	
extern Connect_TypedefU unsigned_connet;
extern Connect_Typedef signed_connet;
extern uint8_t SEND_STA;
void Set_TypeU(Connect_TypedefU *co,uint8_t type);
void Set_Type(Connect_Typedef *co,uint8_t type);
void Set_Datau32(Connect_TypedefU *co,uint32_t data);
void Set_Datau16(Connect_TypedefU *co,uint16_t data);
void Set_Data32(Connect_Typedef *co,int32_t data);
void Set_Data16(Connect_Typedef *co,int16_t data);
void Send_Begin(uint8_t STA);
void Send_End(void);
void Send_MessageU16(Connect_TypedefU *co);
void Send_Message16(Connect_Typedef *co);
void Send_MessageU32(Connect_TypedefU *co);
void Send_Message32(Connect_Typedef *co);
void publish_vel(void);
void publish_remote(void);
void publish_las(void);
void publish_state(void);


#define MSG_vel_x         0X01
#define MSG_vel_y         0X02
#define MSG_vel_z         0X03
#define MSG_distance_f    0X04		//Ç°¾àÀë
#define MSG_distance_b    0X05		//ºó¾àÀë
#define MSG_distance_l    0X06		//×ó¾àÀë
#define MSG_distance_r    0X07		//ÓÒ¾àÀë
#define MSG_remote_ch0    0x08   //Ò£¿ØÆ÷ch0
#define MSG_remote_ch1    0x08   //Ò£¿ØÆ÷ch1
#define MSG_remote_ch2    0x09   //Ò£¿ØÆ÷ch2
#define MSG_remote_ch3    0x0A   //Ò£¿ØÆ÷ch3
#define MSG_remote_s1     0x0B   //Ò£¿ØÆ÷s1
#define MSG_remote_s2     0x0C   //Ò£¿ØÆ÷s2

#endif
