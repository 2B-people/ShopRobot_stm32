//              SCL   接PD6（SCL）
//              SDA   接PD7（SDA）
//////////key_PIN1   	//中
//////////key_PIN2  	//左
//////////key_PIN3  	//下
//////////key_PIN4  	//右
//////////key_PIN5  	//上
//////////key_PIN6  	//独立
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"
#include "millisecondtimer.h"
void OLED_SHOW_MANU()
{
	static uint8_t manu=4;
	static uint8_t key;
	
	switch(manu)
  {				
		case 1:			//速度坐标界面
	 {
		OLED_ShowString(0, 0, "X", 16);
		OLED_ShowNum(16,0,position_x,3,16);		//X坐标
		OLED_ShowString(0, 2, "Y", 16);
		OLED_ShowNum(16,2,position_y,3,16);		//Y坐标
		OLED_ShowString(0, 4, "D", 16);	
		OLED_ShowNum(16,4,Distance,3,16);				
		OLED_ShowString(0, 6, "V", 16);	
		if(required_vel<0)
			OLED_ShowChar(10,6,'-',16);
		else
			OLED_ShowChar(10,6,' ',16);
		OLED_ShowNum(16,6,(abs)(required_vel*100),3,16);	
		OLED_ShowString(50, 0, "M1", 16);
		if(motor1.target_speed<0)
			OLED_ShowChar(70,0,'-',16);
		else
			OLED_ShowChar(70,0,' ',16);
		OLED_ShowNum(76,0,(abs)(motor1.now_speed),4,16);//电机1速度
		OLED_ShowString(50, 2, "M2", 16);
		if(motor2.target_speed<0)
			OLED_ShowChar(70,2,'-',16);
		else
			OLED_ShowChar(70,2,' ',16);
		OLED_ShowNum(76,2,(abs)(motor2.now_speed),4,16);//电机2速度
		OLED_ShowString(50, 4, "H1", 16);
		OLED_ShowNum(76,4, ADC_JIHE[0],4,16);			//灰度1值
		OLED_ShowString(50, 6, "H2", 16);
		OLED_ShowNum(76,6, ADC_JIHE[1],4,16);			//灰度2值
		key=KEY_Scan(0);
		switch(key)
		{
			case KEY1_PRES:required_vel=0;break;
			case KEY5_PRES:required_vel+=0.1;break;
			case KEY3_PRES:required_vel-=0.1;break;
			case KEY4_PRES:OLED_Clear();manu=2;break;
			case KEY6_PRES:ROTATE(1);break;
		}
		break;
	 }
	 
	 case 2:		//遥控器界面
	 {
		OLED_ShowString(0, 0, "C0", 16);
		OLED_ShowNum(25,0,RC_CtrlData.ch0,4,16);		
		OLED_ShowString(0, 2, "C1", 16);
		OLED_ShowNum(25,2,RC_CtrlData.ch1,4,16);		
		OLED_ShowString(0, 4, "C2", 16);	
		OLED_ShowNum(25,4,RC_CtrlData.ch2,4,16);		
		OLED_ShowString(0, 6, "C3", 16);	
		OLED_ShowNum(25,6,RC_CtrlData.ch3,4,16);		
		OLED_ShowString(80, 0, "S1", 16);
		OLED_ShowNum(106,0,RC_CtrlData.s1,1,16);
		OLED_ShowString(80, 2, "S2", 16);
		 OLED_ShowNum(106,2,RC_CtrlData.s2,1,16);
		key=KEY_Scan(0);
		switch(key)
		{
			case KEY1_PRES:required_vel=0;break;
			case KEY5_PRES:required_vel+=0.1;break;
			case KEY3_PRES:required_vel-=0.1;break;
			case KEY2_PRES:OLED_Clear();manu=1;break;
			case KEY4_PRES:OLED_Clear();manu=3;break;
			case KEY6_PRES:ROTATE(1);break;
		}
		break;
	 }
	 
		case 3:			//控制参数界面
	 {
		OLED_ShowString(0, 0, "stop", 16);
		OLED_ShowNum(50,0,IsStop,1,16);		
		OLED_ShowString(0, 2, "hd", 16);
		OLED_ShowNum(50,2,IsHD,1,16);		
		OLED_ShowString(0, 4, "Mofi", 16);	
		OLED_ShowNum(50,4,IsMoveFinsh,1,16);		
		OLED_ShowString(0, 6, "Rota", 16);	
		OLED_ShowNum(50,6,IsRotate,1,16);		
		OLED_ShowString(70, 0, "Remo", 16);
		OLED_ShowNum(120,0,IsRemote,1,16);
		OLED_ShowString(70, 2, "Fetc", 16);
		OLED_ShowNum(120,2,IsFetch,1,16);
		OLED_ShowString(70, 4, "Mode", 16);
		OLED_ShowNum(120,4,mode,1,16);
		OLED_ShowString(70, 6, "Pat", 16);
		OLED_ShowNum(120,6,patrolStatus,2,16);
		key=KEY_Scan(0);
		switch(key)
		{
			case KEY1_PRES:required_vel=0;break;
			case KEY5_PRES:required_vel+=0.1;break;
			case KEY3_PRES:required_vel-=0.1;break;
			case KEY2_PRES:OLED_Clear();manu=2;break;
			case KEY4_PRES:OLED_Clear();manu=4;break;
			case KEY6_PRES:ROTATE(1);break;
		}
		break;
	 }
	 
		case 4:		//底层灰度界面
	 {
		 OLED_ShowString(0, 0, "B1", 16);
		 OLED_ShowNum(35,0,infrared1,1,16);
		 OLED_ShowString(0, 2, "B2", 16);
	   OLED_ShowNum(35,2,infrared2,1,16);
		 OLED_ShowString(0, 4, "B3", 16);
		 OLED_ShowNum(35,4,infrared3,1,16);
		 OLED_ShowString(0, 6, "B4", 16);
		 OLED_ShowNum(35,6,infrared4,1,16);
		 OLED_ShowString(50, 0, "H1", 16);
		 OLED_ShowNum(76,0, ADC_JIHE[0],4,16);			//灰度1值
		 OLED_ShowString(50, 2, "H2", 16);
		 OLED_ShowNum(76,2, ADC_JIHE[1],4,16);			//灰度2值
		 OLED_ShowString(50, 4, "H3", 16);
		 OLED_ShowNum(76,4, ADC_JIHE[2],4,16);			//灰度1值
		 OLED_ShowString(50, 6, "H4", 16);
		 OLED_ShowNum(76,6, ADC_JIHE[3],4,16);			//灰度2值		 
		 key=KEY_Scan(0);
			switch(key)
			{
				case KEY1_PRES:required_vel=0;break;
				case KEY5_PRES:required_vel+=0.1;break;
				case KEY3_PRES:required_vel-=0.1;break;
				case KEY2_PRES:OLED_Clear();manu=3;break;
				case KEY4_PRES:OLED_Clear();manu=5;break;
				case KEY6_PRES:ROTATE(1);break;
			}
			break;
	 }
		
		case 5:				//路径规划界面
	 {
		 OLED_ShowString(0, 0, "X", 16);
		 OLED_ShowNum(35,0,position_x,1,16);
		 OLED_ShowString(0, 2, "Y", 16);
	   OLED_ShowNum(35,2,position_y,1,16);
		 OLED_ShowString(0, 4, "TX", 16);
		 OLED_ShowNum(35,4,target_position_x,1,16);
		 OLED_ShowString(0, 6, "TY", 16);
		 OLED_ShowNum(35,6,target_position_y,1,16);
		 OLED_ShowString(50, 0, "NX", 16);
		 OLED_ShowNum(76,0, nextx,4,16);			
		 OLED_ShowString(50, 2, "NY", 16);
		 OLED_ShowNum(76,2, nexty,4,16);			
		 OLED_ShowString(50, 4, "Ob", 16);
		 OLED_ShowNum(76,4, Obstacle,4,16);			
		 OLED_ShowString(50, 6, "Or", 16);
		 OLED_ShowNum(76,6, orientation,4,16);			
		 	key=KEY_Scan(0);
			switch(key)
			{
				case KEY1_PRES:OLED_Clear();manu=3;break;
				case KEY5_PRES:position_y+=1;break;
				case KEY3_PRES:position_y-=1;break;
				case KEY2_PRES:position_x-=1;break;
				case KEY4_PRES:position_x+=1;break;
				case KEY6_PRES:ROTATE(1);break;
			}
			break;
	 }
 }
}

void IIC_Start()
{

	OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
	OLED_SCLK_Set();
	//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
}

void IIC_Wait_Ack()
{

	//GPIOB->CRH &= 0XFFF0FFFF;	//设置PB12为上拉输入模式
	//GPIOB->CRH |= 0x00080000;
	//	OLED_SDA = 1;
	//	delay_us(1);
	//OLED_SCL = 1;
	//delay_us(50000);
	/*	while(1)
	{
		if(!OLED_SDA)				//判断是否接收到OLED 应答信号
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//设置PB12为通用推免输出模式
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
	OLED_SCLK_Set();
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m, da;
	da = IIC_Byte;
	OLED_SCLK_Clr();
	for (i = 0; i < 8; i++)
	{
		m = da;
		//	OLED_SCLK_Clr();
		m = m & 0x80;
		if (m == 0x80)
		{
			OLED_SDIN_Set();
		}
		else
			OLED_SDIN_Clr();
		da = da << 1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
	}
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78); //Slave address,SA0=0
	IIC_Wait_Ack();
	Write_IIC_Byte(0x00); //write command
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_Command);
	IIC_Wait_Ack();
	IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78); //D/C#=0; R/W#=0
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40); //write data
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();
	IIC_Stop();
}
void OLED_WR_Byte(unsigned dat, unsigned cmd)
{
	if (cmd)
	{

		Write_IIC_Data(dat);
	}
	else
	{
		Write_IIC_Command(dat);
	}
}

/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m, n;
	for (m = 0; m < 8; m++)
	{
		OLED_WR_Byte(0xb0 + m, 0); //page0-page1
		OLED_WR_Byte(0x00, 0);	 //low column start address
		OLED_WR_Byte(0x10, 0);	 //high column start address
		for (n = 0; n < 128; n++)
		{
			OLED_WR_Byte(fill_Data, 1);
		}
	}
}

/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for (; Del_50ms > 0; Del_50ms--)
		for (m = 6245; m > 0; m--)
			;
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while (Del_1ms--)
	{
		for (j = 0; j < 123; j++)
			;
	}
}

//坐标设置

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
	OLED_WR_Byte(0xb0 + y, OLED_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte((x & 0x0f), OLED_CMD);
}
//开启OLED显示
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC命令
	OLED_WR_Byte(0X14, OLED_CMD); //DCDC ON
	OLED_WR_Byte(0XAF, OLED_CMD); //DISPLAY ON
}
//关闭OLED显示
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC命令
	OLED_WR_Byte(0X10, OLED_CMD); //DCDC OFF
	OLED_WR_Byte(0XAE, OLED_CMD); //DISPLAY OFF
}
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
void OLED_Clear(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //设置页地址（0~7）
		OLED_WR_Byte(0x00, OLED_CMD);	 //设置显示位置—列低地址
		OLED_WR_Byte(0x10, OLED_CMD);	 //设置显示位置—列高地址
		for (n = 0; n < 128; n++)
			OLED_WR_Byte(0, OLED_DATA);
	} //更新显示
}
void OLED_On(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //设置页地址（0~7）
		OLED_WR_Byte(0x00, OLED_CMD);	 //设置显示位置—列低地址
		OLED_WR_Byte(0x10, OLED_CMD);	 //设置显示位置—列高地址
		for (n = 0; n < 128; n++)
			OLED_WR_Byte(1, OLED_DATA);
	} //更新显示
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 Char_Size)
{
	unsigned char c = 0, i = 0;
	c = chr - ' '; //得到偏移后的值
	if (x > Max_Column - 1)
	{
		x = 0;
		y = y + 2;
	}
	if (Char_Size == 16)
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
	}
	else
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i < 6; i++)
			OLED_WR_Byte(F6x8[c][i], OLED_DATA);
	}
}
//m^n函数
u32 oled_pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)
		result *= m;
	return result;
}
//显示2个数字
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2)
{
	u8 t, temp;
	u8 enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				OLED_ShowChar(x + (size2 / 2) * t, y, ' ', size2);
				continue;
			}
			else
				enshow = 1;
		}
		OLED_ShowChar(x + (size2 / 2) * t, y, temp + '0', size2);
	}
}
//显示一个字符号串
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 Char_Size)
{
	unsigned char j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j], Char_Size);
		x += 8;
		if (x > 120)
		{
			x = 0;
			y += 2;
		}
		j++;
	}
}
//显示汉字
void OLED_ShowCHinese(u8 x, u8 y, u8 no)
{
	u8 t, adder = 0;
	OLED_Set_Pos(x, y);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_Byte(Hzk[2 * no][t], OLED_DATA);
		adder += 1;
	}
	OLED_Set_Pos(x, y + 1);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_Byte(Hzk[2 * no + 1][t], OLED_DATA);
		adder += 1;
	}
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{
	unsigned int j = 0;
	unsigned char x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++)
		{
			OLED_WR_Byte(BMP[j++], OLED_DATA);
		}
	}
}

//初始化SSD1306
void OLED_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG , ENABLE); //使能PC,D,G端口时钟

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_0 ; //PD3,PD6推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;														   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														   //速度50MHz
	GPIO_Init(GPIOG, &GPIO_InitStructure);																	   //初始化GPIOD3,6
	GPIO_SetBits(GPIOG, GPIO_Pin_6 | GPIO_Pin_7 );		   //PD3,PD6 输出高

	delay(200);

	OLED_WR_Byte(0xAE, OLED_CMD); //--display off
	OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
	OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
	OLED_WR_Byte(0x40, OLED_CMD); //--set start line address
	OLED_WR_Byte(0xB0, OLED_CMD); //--set page address
	OLED_WR_Byte(0x81, OLED_CMD); // contract control
	OLED_WR_Byte(0xFF, OLED_CMD); //--128
	OLED_WR_Byte(0xA1, OLED_CMD); //set segment remap
	OLED_WR_Byte(0xA6, OLED_CMD); //--normal / reverse
	OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F, OLED_CMD); //--1/32 duty
	OLED_WR_Byte(0xC8, OLED_CMD); //Com scan direction
	OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset
	OLED_WR_Byte(0x00, OLED_CMD); //

	OLED_WR_Byte(0xD5, OLED_CMD); //set osc division
	OLED_WR_Byte(0x80, OLED_CMD); //

	OLED_WR_Byte(0xD8, OLED_CMD); //set area color mode off
	OLED_WR_Byte(0x05, OLED_CMD); //

	OLED_WR_Byte(0xD9, OLED_CMD); //Set Pre-Charge Period
	OLED_WR_Byte(0xF1, OLED_CMD); //

	OLED_WR_Byte(0xDA, OLED_CMD); //set com pin configuartion
	OLED_WR_Byte(0x12, OLED_CMD); //

	OLED_WR_Byte(0xDB, OLED_CMD); //set Vcomh
	OLED_WR_Byte(0x30, OLED_CMD); //

	OLED_WR_Byte(0x8D, OLED_CMD); //set charge pump enable
	OLED_WR_Byte(0x14, OLED_CMD); //

	OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel
}

