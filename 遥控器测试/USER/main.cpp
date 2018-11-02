extern "C"
{
#include "delay.h"
#include "sys.h"
#include "usart.h"
}
#include "lcd.h"
#include "remote.h"
/************************************************
 ALIENTEK 战舰STM32F103开发板实验13
 TFTLCD显示实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
 extern REMOTE RC_CtrlData;
int count;
double required_angular_vel;
double required_vel_x;
double required_vel_y;
 int main(void)
 {	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LCD_Init();
	RC_Init();	 
	 LCD_Clear(WHITE);
  	while(1) 
	{		 
		LCD_ShowNum(10,10,RC_CtrlData.ch0,5,16); 
		LCD_ShowNum(10,40,RC_CtrlData.ch1,5,16); 
		LCD_ShowNum(10,70,RC_CtrlData.ch2,5,16); 
		LCD_ShowNum(10,100,RC_CtrlData.ch3,5,16); 
		LCD_ShowNum(10,130,RC_CtrlData.s1,5,16); 
		LCD_ShowNum(10,160,RC_CtrlData.s2,5,16); 
		LCD_ShowNum(10,190,(int)required_angular_vel,3,16); 
		LCD_ShowNum(10,220,(int)required_vel_x,3,16); 
		LCD_ShowNum(10,250,(int)required_vel_y,3,16); 
		count++;
	} 
}
