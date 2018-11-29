#include "connect.h"
Connect_TypedefU unsigned_connet;
Connect_Typedef signed_connet;
uint8_t SEND_STA;
void Set_TypeU(Connect_TypedefU *co,uint8_t type)
{
	co->Type=type;
}
void Set_Type(Connect_Typedef *co,uint8_t type)
{
	co->Type=type;
}

void Set_Datau32(Connect_TypedefU *co,uint32_t data)
{
	uint8_t data1=(uint8_t)data&0x000000FF;
	uint8_t data2=(uint8_t)(data>>8)&0x000000FF;
	uint8_t data3=(uint8_t)(data>>16)&0x000000FF;
	uint8_t data4=(uint8_t)(data>>24)&0x000000FF;
	
	co->Date_1=data1;
	co->Date_2=data2;
	co->Date_3=data3;
	co->Date_4=data4;
}
void Set_Datau16(Connect_TypedefU *co,uint16_t data)
{
	uint8_t data1=(uint8_t)data&0x00FF;
	uint8_t data2=(uint8_t)(data>>8)&0x00FF;
	co->Date_1=data1;
	co->Date_2=data2;
}
void Set_Data32(Connect_Typedef *co,int32_t data)
{
	int8_t data1=(int8_t)data&0x000000FF;
	int8_t data2=(int8_t)(data>>8)&0x000000FF;
	int8_t data3=(int8_t)(data>>16)&0x000000FF;
	int8_t data4=(int8_t)(data>>24)&0x000000FF;
	
	co->Date_1=data1;
	co->Date_2=data2;
	co->Date_3=data3;
	co->Date_4=data4;
}

void Set_Data16(Connect_Typedef *co,int16_t data)
{
	int8_t data1=(int8_t)data&0x00FF;
	int8_t data2=(int8_t)(data>>8)&0x00FF;
	co->Date_1=data1;
	co->Date_2=data2;
}
void Send_MessageU16(Connect_TypedefU *co)
{
	usart1_write(co->Type);
	usart1_write(co->Date_1);
	usart1_write(co->Date_2);
}
void Send_MessageU32(Connect_TypedefU *co)
{
	usart1_write(co->Type);
	usart1_write(co->Date_1);
	usart1_write(co->Date_2);
	usart1_write(co->Date_3);
	usart1_write(co->Date_4);	
}
void Send_Message16(Connect_Typedef *co)
{
	usart1_write(co->Type);
	usart1_write(co->Date_1);
	usart1_write(co->Date_2);
}
void Send_Message32(Connect_Typedef *co)
{
	usart1_write(co->Type);
	usart1_write(co->Date_1);
	usart1_write(co->Date_2);
	usart1_write(co->Date_3);
	usart1_write(co->Date_4);	
}
void Send_Begin(uint8_t STA)
{
	usart1_write(0x49);
	usart1_write(0x39);
	switch(STA)
	{
		case SVEL:
			usart1_write(0x13);	SEND_STA=True;
			break;
		case SREMOTE:
			usart1_write(0x36);	SEND_STA=True;
			break;
		case SLAS:
			usart1_write(0x34);	SEND_STA=True;
			break;
		default:
			SEND_STA=False;break;
	}

}
void Send_End(void)
{
	usart1_write(0x55);
	usart1_write(0x39);
	SEND_STA=False;
}
void publish_vel(void)
{
	Send_Begin(SVEL);
	if(SEND_STA)
	{
		Set_Type(&signed_connet,MSG_vel_x);
		Set_Data16(&signed_connet,(int16_t)required_linear_vel_x*100);
		Send_Message16(&signed_connet);
		Set_Type(&signed_connet,MSG_vel_y);
		Set_Data16(&signed_connet,(int16_t)required_linear_vel_y*100);
		Send_Message16(&signed_connet);
		Set_Type(&signed_connet,MSG_vel_z);
		Set_Data16(&signed_connet,(int16_t)required_angular_vel*100);
		Send_Message16(&signed_connet);
	}
	Send_End();
}

void publish_remote(void)
{
	Send_Begin(SREMOTE);
	if(SEND_STA)
	{
		Set_TypeU(&unsigned_connet,MSG_remote_ch0);
		Set_Datau16(&unsigned_connet,(uint16_t)RC_CtrlData.ch0);
		Send_MessageU16(&unsigned_connet);
		Set_TypeU(&unsigned_connet,MSG_remote_ch1);
		Set_Datau16(&unsigned_connet,(uint16_t)RC_CtrlData.ch1);
		Send_MessageU16(&unsigned_connet);
		Set_TypeU(&unsigned_connet,MSG_remote_ch2);
		Set_Datau16(&unsigned_connet,(uint16_t)RC_CtrlData.ch2);
		Send_MessageU16(&unsigned_connet);
		Set_TypeU(&unsigned_connet,MSG_remote_ch3);
		Set_Datau16(&unsigned_connet,(uint16_t)RC_CtrlData.ch3);
		Send_MessageU16(&unsigned_connet);
		Set_TypeU(&unsigned_connet,MSG_remote_s1);
		Set_Datau16(&unsigned_connet,(uint16_t)RC_CtrlData.s1);
		Send_MessageU16(&unsigned_connet);
		Set_TypeU(&unsigned_connet,MSG_remote_s2);
		Set_Datau16(&unsigned_connet,(uint16_t)RC_CtrlData.s2);
		Send_MessageU16(&unsigned_connet);			
	}
	Send_End();
}

void publish_las(void)
{
	Send_Begin(SVEL);
	if(SEND_STA)
	{
		Set_TypeU(&unsigned_connet,MSG_distance_f);
		Set_Datau16(&unsigned_connet,(uint16_t)Distance_F);
		Send_MessageU16(&unsigned_connet);
		Set_TypeU(&unsigned_connet,MSG_distance_b);
		Set_Datau16(&unsigned_connet,(uint16_t)Distance_B);
		Send_MessageU16(&unsigned_connet);
		Set_TypeU(&unsigned_connet,MSG_distance_l);
		Set_Datau16(&unsigned_connet,(uint16_t)Distance_L);
		Send_MessageU16(&unsigned_connet);
		Set_TypeU(&unsigned_connet,MSG_distance_r);
		Set_Datau16(&unsigned_connet,(uint16_t)Distance_R);
		Send_MessageU16(&unsigned_connet);		
	}
	Send_End();
}
