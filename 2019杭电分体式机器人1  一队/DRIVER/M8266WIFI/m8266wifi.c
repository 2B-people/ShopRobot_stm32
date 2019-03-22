#include "stdio.h"
#include "brd_cfg.h"
#include "M8266WIFIDrv.h"
#include "M8266HostIf.h"
#include "M8266WIFI_ops.h"
#include "m8266wifi.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "include.h"
#include "string.h"

// void M8266WIFI_Test()
// {
// 	u16 status = 0;
// 	u16 i = 3;
// 	u16 b = 3;
// 	u8 a[10][20] = {"I'm fine", "I'm bad"};
// 	u8 snd_data[20];
// 	u8 RecvData[20];
// 	u16 num_char;
// 	u16 batch;
// 	for (batch = 1;; batch++)
// 	{
// 		delay_ms(400);
// 		num_char = strlen(snd_data)
// 		M8266WIFI_SPI_Send_Data(snd_data, num_char, 0, &status); //发送数据
// 		M8266WIFI_SPI_RecvData(RecvData, 20, 10, NULL, &status); //接收数据
// 		if (strcmp(RecvData, "how are you") == 0)
// 			i = 0;
// 		else
// 			i = 1;
// 		if (strcmp(RecvData, "\0") != 0)
// 			b = i;
// 		else
// 			i = 5;
// 		memset(snd_data, '\0', 19); //清零发送数据
// 		strcpy(snd_data, a[b]); //将接收到的数据复制到发送数据
// 		memset(RecvData, '\0', 19); //清零接收数据
// 	}
// }

u8 wifi_wait_begin(void)
{
	char RecvData[9];

	u16 status = 0;
	u32 batch;
	for (batch = 0;; batch++)
	{
		M8266WIFI_SPI_RecvData(RecvData, 9, 10, NULL, &status); //接收数据
		if (strcmp(RecvData, "HDUgo") == 0)
			break;
	}
	memset(RecvData, '\0', 8);
	return status;
}

u8 wifi_finish()
{
	char snd_data[9] = "HDUfinish";
	u16 num_char;
	u16 status = 0;
	num_char = strlen(snd_data);
	M8266WIFI_SPI_Send_Data(snd_data, num_char, 0, &status); //发送数据
	memset(snd_data, '\0', 8);
	return status;
}


void sifi_send(void)
{
	char snd_data[9];
	char *FH = "HDU";
	u16 num_char;
	u16 status = 0;
	memset(snd_data, '\0', 9);
	//发送当前坐标
	memcpy(snd_data, "HDUR", 4);
	snd_data[4] = position_x + 48;
	snd_data[5] = ' ';
	snd_data[6] = position_y + 48;
	snd_data[7] = ' ';
	snd_data[8] = orientation + 48;
	snd_data[9] = '\0';
	num_char = strlen(snd_data);
	M8266WIFI_SPI_Send_Data(snd_data, num_char, 0, &status); //发送数据
	memset(snd_data, '\0', 8);
}

void wifi_connect(void)
{
	char RecvData[9];
	char *FH = "HDU";
	u16 status = 0;
	u8 x = 10;
	u8 y = 10;
	u8 in_orientation = 0;
	memset(RecvData, '\0', 9);

	M8266WIFI_SPI_RecvData(RecvData, 9, 5, 0, &status); //接收数据
	if (strcmp(RecvData, "\0") != 0)
	{
		if (memcmp(RecvData, FH, 3) == 0)
		{
			if (memcmp(RecvData + 3, "stop", 4)==0)
			{
				IsStop = 1;
			}
			else if (RecvData[3] == 'R')
			{
				IsStop = 0;				
				x = (RecvData[4] - '0');
				y = (RecvData[6] - '0');
				in_orientation = (RecvData[8] - '0');
				toCoordinate(x, y);
				target_orientation = in_orientation;
			}
			else if (RecvData[3] == 'C')
			{
					Goods_num = RecvData[5] - '0'-1;
					toFetch(Goods_num,2);
					wifi_finish();
			}			
			else if(RecvData[3] == 'D')
			{
					Com_run();
					wifi_finish();
			}
			else if(RecvData[3] == 'T')
			{
					Goods_floor(1);
					wifi_finish();
			}
			else if(RecvData[3] == 'O')
			{
				Obstacle = (RecvData[5] - '0');
				wifi_finish();
			}
			else if (RecvData[3] == 'P')
			{
				if(RecvData[5] == '1')
				{
					toFetch(100,0);
				}
				if(RecvData[5] == '2')
				{
					toFetch(100,1);
				}	
				Com_run();
				wifi_finish();
			}
		}
		memset(RecvData, '\0', 9);
	}
}
// u8 wifi_wait_move(void)
// {
// 	char RecvData[20];
// 	u16 status = 0;
// 	u8 x;
// 	u8 y;
// 	u8 in_orientation;
// 	memset(RecvData, '\0', 19);
// 	OLED_Clear();
// 	while (1)
// 	{
// 		LED3 = 0;
// 		M8266WIFI_SPI_RecvData(RecvData, 20, 10, 0, &status); //接收数据
// 		// if (strcmp(RecvData,"\0") != 0)
// 		// break;
// 		OLED_ShowString(0, 2, RecvData, 20);
// 	}
// 	x = (RecvData[0] - '0');
// 	y = (RecvData[2] - '0');
// 	in_orientation = (RecvData[4] - '0');
// 	memset(RecvData, '\0', 19);
// 	toCoordinate(x, y);
// 	target_orientation = in_orientation;
// 	return status;
// }
