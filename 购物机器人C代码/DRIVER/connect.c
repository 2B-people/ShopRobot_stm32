#include "connect.h"
Connect_Typedef connectMicorw2PC;
void Set_Type(Connect_Typedef co,uint16_t type)
{
	uint8_t low =(uint8_t)type&0x00FF;
	uint8_t high=(uint8_t)((type>>8)&0x00FF);
	co.Type_L=low;
	co.Type_H=high;
}

void Set_Data(Connect_Typedef co,uint32_t data)
{
	uint8_t data1=(uint8_t)data&0x000000FF;
	uint8_t data2=(uint8_t)(data>>8)&0x000000FF;
	uint8_t data3=(uint8_t)(data>>16)&0x000000FF;
	uint8_t data4=(uint8_t)(data>>24)&0x000000FF;
	
	co.Date_1=data1;
	co.Date_2=data2;
	co.Date_3=data3;
	co.Date_4=data4;
}

void Send_Message(Connect_Typedef co)
{
	usart1_write(0x89);
	usart1_write(0x89);
	usart1_write(co.Type_L);
	usart1_write(co.Type_H);
	usart1_write(co.Date_1);
	usart1_write(co.Date_2);
	usart1_write(co.Date_3);
	usart1_write(co.Date_4);
	usart1_write(0xfe);
	usart1_write(0xfe);
}

void publish_vel(void)
{
	Set_Type(connectMicorw2PC,MSG_vel_x);
	Set_Data(connectMicorw2PC,required_linear_vel_x);
	Send_Message(connectMicorw2PC);
	Set_Type(connectMicorw2PC,MSG_vel_y);
	Set_Data(connectMicorw2PC,required_linear_vel_y);
	Send_Message(connectMicorw2PC);
	Set_Type(connectMicorw2PC,MSG_vel_z);
	Set_Data(connectMicorw2PC,required_angular_vel);
	Send_Message(connectMicorw2PC);	
}
void publish_remote(void)
{
	Set_Type(connectMicorw2PC,MSG_remote_ch0);
	Set_Data(connectMicorw2PC,RC_CtrlData.ch0);
	Send_Message(connectMicorw2PC);
	Set_Type(connectMicorw2PC,MSG_remote_ch1);
	Set_Data(connectMicorw2PC,RC_CtrlData.ch1);
	Send_Message(connectMicorw2PC);
	Set_Type(connectMicorw2PC,MSG_remote_ch2);
	Set_Data(connectMicorw2PC,RC_CtrlData.ch2);
	Send_Message(connectMicorw2PC);	
	Set_Type(connectMicorw2PC,MSG_remote_ch3);
	Set_Data(connectMicorw2PC,RC_CtrlData.ch3);
	Send_Message(connectMicorw2PC);
	Set_Type(connectMicorw2PC,MSG_remote_s1);
	Set_Data(connectMicorw2PC,RC_CtrlData.s1);
	Send_Message(connectMicorw2PC);		
	Set_Type(connectMicorw2PC,MSG_remote_s2);
	Set_Data(connectMicorw2PC,RC_CtrlData.s2);
	Send_Message(connectMicorw2PC);		
}
void publish_las(void)
{
	las_measure(FORWARD);
	las_measure(BACK);
	las_measure(LEFT);
	las_measure(RIGHT);
	Set_Type(connectMicorw2PC,MSG_distance_f);
	Set_Data(connectMicorw2PC,Distance_F);
	Send_Message(connectMicorw2PC);
	Set_Type(connectMicorw2PC,MSG_distance_b);
	Set_Data(connectMicorw2PC,Distance_B);
	Send_Message(connectMicorw2PC);
	Set_Type(connectMicorw2PC,MSG_distance_l);
	Set_Data(connectMicorw2PC,Distance_L);
	Send_Message(connectMicorw2PC);	
	Set_Type(connectMicorw2PC,MSG_distance_r);
	Set_Data(connectMicorw2PC,Distance_R);
	Send_Message(connectMicorw2PC);
}

