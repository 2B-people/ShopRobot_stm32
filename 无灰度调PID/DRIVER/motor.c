#include "motor.h"
Motor motor1;
Motor motor2;
Motor motor3;
Motor motor4;
Motor yt_motor1;
Motor yt_motor2;
void CAN_Mode_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PORTA时钟

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); //使能CAN1时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
	GPIO_Init(GPIOA, &GPIO_InitStructure);			//初始化IO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);		  //初始化IO

	//CAN单元设置
	CAN_InitStructure.CAN_TTCM = DISABLE;		  //非时间触发通信模式
	CAN_InitStructure.CAN_ABOM = DISABLE;		  //软件自动离线管理
	CAN_InitStructure.CAN_AWUM = DISABLE;		  //睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART = DISABLE;		  //禁止报文自动传送
	CAN_InitStructure.CAN_RFLM = DISABLE;		  //报文不锁定,新的覆盖旧的
	CAN_InitStructure.CAN_TXFP = ENABLE;		  //优先级由报文标识符决定
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //模式设置： mode:0,普通模式;1,回环模式;
	//设置波特率
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq; //重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq; //Tbs1=tbs1+1个时间单位CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq; //Tbs2=tbs2+1个时间单位CAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler = 2;	 //分频系数(Fdiv)为brp+1
	CAN_Init(CAN1, &CAN_InitStructure);		 //初始化CAN1

	CAN_FilterInitStructure.CAN_FilterNumber = 0;					 //过滤器0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;  //屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; //32位宽
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				 //32位ID
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000; //32位MASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0; //过滤器0关联到FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;				 //激活过滤器0

	CAN_FilterInit(&CAN_FilterInitStructure); //滤波器初始化

	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE); //FIFO0消息挂号中断允许.
	CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 主优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  // 次优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USB_LP_CAN1_RX0_IRQHandler(void) //该函数用于接受CAN总线数据并转换为电机RPM
{
	CanRxMsg rx_message;
	if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
		switch (rx_message.StdId)
		{
		case 0x201:
		{
			motor1.now_speed = -((rx_message.Data[2] << 8) | rx_message.Data[3]);
		}
		break;
		case 0x202:
		{
			motor2.now_speed = -((rx_message.Data[2] << 8) | rx_message.Data[3]);
		}
		break;
			//				case 0x203:
			//				{
			//					motor3.now_speed=((rx_message.Data[2]<<8)|rx_message.Data[3]);
			//				}break;
			//				case 0x204:
			//				{
			//					motor4.now_speed=((rx_message.Data[2]<<8)|rx_message.Data[3]);
			//				}break;
			//				case 0x205:
			//				{
			//					yt_motor1.now_speed=((rx_message.Data[2]<<8)|rx_message.Data[3]);
			//				}break;
			//				case 0x206:
			//				{
			//					yt_motor2.now_speed=((rx_message.Data[2]<<8)|rx_message.Data[3]);
			//				}break;
		}
	}
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN1, CAN_IT_TME) != RESET) //if transmit mailbox is empty
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_TME);
	}
}

void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq) //设置电机速度
{
	CanTxMsg tx_message;
	//		motor1.output=cm1_iq;
	//		motor2.output=cm2_iq;
	//		motor3.output=cm3_iq;
	//		motor4.output=cm4_iq;
	tx_message.StdId = 0x200;
	tx_message.IDE = CAN_Id_Standard;
	tx_message.RTR = CAN_RTR_Data;
	tx_message.DLC = 0x08;

	tx_message.Data[0] = (uint8_t)(cm1_iq >> 8);
	tx_message.Data[1] = (uint8_t)cm1_iq;
	tx_message.Data[2] = (uint8_t)(cm2_iq >> 8);
	tx_message.Data[3] = (uint8_t)cm2_iq;
	//    tx_message.Data[4] = (uint8_t)(cm3_iq >> 8);
	//    tx_message.Data[5] = (uint8_t)cm3_iq;
	//    tx_message.Data[6] = (uint8_t)(cm4_iq >> 8);
	//    tx_message.Data[7] = (uint8_t)cm4_iq;
	CAN_Transmit(CANx, &tx_message);
}

void Set_YT_Speed(CAN_TypeDef *CANx, int16_t yt1_iq, int16_t yt2_iq) //设置云台电机速度
{

	//		CanTxMsg tx_message;
	//		yt_motor1.output=yt1_iq;
	//		yt_motor2.output=yt2_iq;
	//		tx_message.StdId =0x1FF;
	//		tx_message.IDE = CAN_Id_Standard;
	//		tx_message.RTR = CAN_RTR_Data;
	//		tx_message.DLC = 0x08;

	//		tx_message.Data[0] = (uint8_t)(yt1_iq >> 8);
	//		tx_message.Data[1] = (uint8_t)(yt1_iq);

	//		tx_message.Data[2] = (uint8_t)(yt2_iq >> 8);
	//		tx_message.Data[3] = (uint8_t)(yt2_iq);

	//		tx_message.Data[4] =  0x00;
	//		tx_message.Data[5] =  0x00;

	//		tx_message.Data[6] =  0x00;
	//		tx_message.Data[7] =  0x00;
	//		CAN_Transmit(CANx,&tx_message);
}
