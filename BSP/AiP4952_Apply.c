#include "AiP4952_Apply.h"	

#if AiP4952_Apply
extern uint8 bleWhitenStart(uint8 chan);
extern void bleWhiten(uint8 *dat, uint8 len, uint8 whitenCoeff);
extern xdata RF_Set_Class  RF_Set;
extern xdata uint8 ble_tx_buffer[48] ;
extern xdata uint8 buffer[39];
//************标志位定义***************************
bit F_TX_PKT_OK = 0;			//tx ok flag
bit F_RF_Error = 0;			  //check 4952 flag  0：ok  1：error
bit	F_RX_Head = 0;				// head flag of rx data packet
bit F_Check_OK = 0;				// check ok flag of rx data packet
bit F_Reset_RxState = 1;	// enter rx state flag
//************全局变量定义**************************						
xdata uint16 	R_TX_Data_Cnt = 0;

xdata uint8		R_RX_Set_Channel_Num = 3;

xdata uint8	R_Cycle_Num = 0;				 // 循环次数
xdata uint8	R_Set_Channel_Num = 0;   // 跳频通道数
xdata uint8	R_One_Channel_TX_Num = 0;// 每个通道发射包数

xdata uint8	R_ReadPKT_Cnt = 0;			 //read pkt counter

xdata   uint8 ch;

xdata uint8 TX_Number[C_Payload_Len + 1] = {0};
xdata uint8 RX_Number[C_Payload_Len + 1] = {0};
xdata uint8	R_ReadReg_Cnt = 0;			 //read reg counter

/**************************************************************************
* @brief:initialize AiP4952 
* @param[in]:
* @param[out]: 
* @return:
* @others: enable 3 line spi if use AiP4952A
***************************************************************************/	
//void AiP4952_Reg_Init(void)
//{
//	//delay_100us(50);			//延时等待上电初始化
//	AiP4952_WriteReg(0x2A,0x20,0x01); //三线制SPI使能	
//	AiP4952_WriteReg(0x01,0x20,0x77);	//CRC开启，PKT/FIFO 高有效，失能软件复位，失能Auto-ack，Payload第一字节作为包长度，自动结束TX状态
////	AiP4952_WriteReg(0x0B,0x83,0x60); //重发次数默认3次，等待一次ACK返回时间 16*32us=512us
//	AiP4952_WriteReg(0x23,0x00,0x00);	    //FIFO长度设置，RX/TX FIFO 不共享，各32字节
//	AiP4952_WriteReg(0x0A,0x20,0x53);	    //VCO_FC	Setting	 
//	AiP4952_WriteReg(0x03,0x4A,0x10);	    //Preamble:3bytes Syncword:32bits(reg31 34) Trailer:8bits FEC Type:FEC13 	
//	AiP4952_WriteReg(0x02,0x40,0x60);	    //发射功率 +7 dBm
//	AiP4952_WriteReg(0x24,0x44,0x02);			//同步字允许错1bit
//	AiP4952_WriteReg(0x1F,0x12,0x34);			//reg31 设置同步字节
//	AiP4952_WriteReg(0x22,0x03,0x80);			//reg34 设置同步字节
//}
extern void re_calcu_white_value(uint8 ch);
void AiP4952_Reg_Init(void)
{
	

	AiP4952_WriteReg(0x2A,0x20,0x01); //三线制SPI使能	
	delay_100us(50);			//延时等待上电初始化
	AiP4952_WriteReg(0x23,0x80,0x00);	    //FIFO长度设置，RX/TX FIFO共享，共64个字节
	AiP4952_WriteReg(0x0A,0x20,0x53);	    //VCO_FC	Setting	 
	AiP4952_WriteReg(0x02,0x40,0x60);	    //发射功率 +7 dBm
	AiP4952_WriteReg(0x24,0x47,0xC3);			//FIFO为满阈值：0x1F,同步字设为允许错2bit	
	//if(F_TR_MODE == C_RX_MODE)
	{
		AiP4952_WriteReg(0x01,0x00,0x73);	  //关闭CRC，payload第一字节不作包长度指示
		AiP4952_WriteReg(0x03,0x1A,0x00);	  //Preamble:1byte(0xAA) Syncword:64bit(reg31 32 33 34) Trailer:8bit(0xAA) FEC Type:NO FEC
		re_calcu_white_value(0);
		AiP4952_WriteReg(0x1F,0xBE,0xD6);						//填入接入地址充当同步字节
		AiP4952_WriteReg(0x20,0x8E,0x89);							
//		AiP4952_WriteReg(0x21,0xF7,0xCF);//AiP4952_WriteReg(0x21,0x25,0x42);	//反白化数据填入同步字中
//		AiP4952_WriteReg(0x22,0xB0,0x57);//AiP4952_WriteReg(0x22,0x11,0);
		AiP4952_WriteReg(0x21,buffer[1],buffer[0]);	//???????????
		AiP4952_WriteReg(0x22,buffer[3],buffer[2]);
//	buffer[0] = 0xCF; //0x42
//	buffer[1] = 0xF7; //37
//	buffer[2] = 0x57; //MAC_0
//	buffer[3] = 0xB0; //MAC_1
//	buffer[4] = 0x1F; //MAC_2	
	}
	//else
	{
		//tx端同步字 配置上电默认值
//		AiP4952_WriteReg(0x01,0x00,0x77);	//关闭CRC，payload第一字节作包长度指示
//		AiP4952_WriteReg(0x05,0x7C,0x26);	// 
	}
	
}

/**************************************************************************
* @brief: check AiP4952 regsiter
* @param[in]:
* @param[out]: 
* @return:
* @others:  spend about 600us to run this function
***************************************************************************/
//code  uint16 Reg_Write_Value[9] = {0x2077,0x837F,0x0000,0x2053,0x4A10,0x4060,0x4402,0x1234,0x0380};
//code  uint8  Reg_Addr[9] = {0x01,0x0B,0x23,0x0A,0x03,0x02,0x24,0x1F,0x22};
//void AiP4952_Reg_Check(void)
//{
//	xdata	 uint16 Reg_Read_Value[9] = {0};
//	xdata	 uint8  i = 0; 
//	xdata	 uint8  R_Check_RegOk_Cnt = 0;
//			 

//  for (i = 0;i<9;i++)
//  {
//    if (AiP4952_ReadReg(Reg_Addr[i]) == Reg_Write_Value[i])
//		{
//			R_Check_RegOk_Cnt++;
//		}			
//	}
//	if (R_Check_RegOk_Cnt == 9)
//	{
//		F_RF_Error = 0;
//	}
//	else
//	{
//		F_RF_Error = 1;
//	}
//}
void AiP4952_Reg_Check(void)
{
			code  uint8  Reg_Addr[8] = {0x23,0x0A,0x02,0x24,0x01,0x03,0x1F,0x20};
			code  uint16 Reg_Write_Value[8] = {0x8000,0x2053,0x4060,0x47C3,0x0073,0x1A00,0xBED6,0x8E89};
			 uint16 Reg_Read_Value[8] = {0};
			 uint8  i = 0; 
			 uint8  R_Check_RegOk_Cnt = 0;
			 

  for (i = 0;i<9;i++)
  {
    if (AiP4952_ReadReg(Reg_Addr[i]) == Reg_Write_Value[i])
		{
			R_Check_RegOk_Cnt++;
		}			
	}
	if (R_Check_RegOk_Cnt >=4)
	{
		F_RF_Error = 0;
	}
	else
	{
		F_RF_Error = 1;
	}
}
/**************************************************************************
* @brief: initialize AiP4952
* @param[in]:
* @param[out]: 
* @return:
* @others:  spend about 10ms to run 1 cycle
***************************************************************************/
void AiP4952_Sys_Init(void)
{
xdata	uint8 i;
	
	for(i=0;i<3;i++)
	{
		AiP4952_Reg_Init();
		delay_100us(40);	
		AiP4952_Reg_Check();
		if(F_RF_Error == 0)
		{
			i = 3;
		}
		//CLR_WDT();
	}
}

/**************************************************************************
* @brief:download tx data in TX_Number[]
* @param[in]:
* @param[out]: 
* @return:
* @others: the same packet tx 2*3 times
***************************************************************************/	
void Download_Data(void)
{
	xdata uint8 k;
	xdata uint16 Check_TX_Sum = 0;
	
	if(R_TX_Data_Cnt == 0)
	{
		R_TX_Data_Cnt =1;
	}
	else 
	{
		if((R_Set_Channel_Num == 3) && (R_Cycle_Num == 2))
		{
			R_TX_Data_Cnt ++;
		}
		else
		{
			return;
		}
	}
	
	TX_Number[0] = C_Payload_Len;
	TX_Number[1] = 0x55;
	TX_Number[2] = 0xAA;
	TX_Number[3] = (R_TX_Data_Cnt >> 8) & 0xFF;
	TX_Number[4] = R_TX_Data_Cnt & 0xFF;
	TX_Number[5] = 0xAA;
	TX_Number[6] = 0xAA;
	TX_Number[7] = 0xAA;
	for(k=0;k<C_Payload_Len-1;k++)	//the sum of tx packet save in last two bytes
	{
		Check_TX_Sum += TX_Number[k];					
	}
	TX_Number[C_Payload_Len-1] = Check_TX_Sum & 0xFF;  
	TX_Number[C_Payload_Len] = Check_TX_Sum >> 8;
	
//	TX_Number[0] = C_Payload_Len;
//	for(k=1;k<C_Payload_Len+1;k++)
//	{
//		TX_Number[k] = 0x55;
//	}
}


/**************************************************************************
* @brief:tx set channel = 2402 + RF_Set.Channel
* @param[in]:
* @param[out]: 
* @return:
* @others: the order of tx is 16 54 100
***************************************************************************/
void RF_TX_Set_Channel(uint8 ch)
{
	switch(ch)
	{
		case 0:
			 RF_Set.Channel = 0;//37	2402
			break;
		case 1:
			 RF_Set.Channel = 24;//38	2426
			break;
		case 2:
			 RF_Set.Channel = 78;//39	2480
			break;
		default:
			 RF_Set.Channel = 76;
			break;
	}
}
/**************************************************************************
* @brief:rx set channel = 2402 + RF_Set.Channel
* @param[in]:
* @param[out]: 
* @return:
* @others: the order of rx is 16 100 54
***************************************************************************/	
void RF_RX_Set_Channel(void)
{
switch(R_RX_Set_Channel_Num)
	{
		case 1:
			 RF_Set.Channel = 0;
			break;
		case 2:
			 RF_Set.Channel = 0;
			break;
		case 3:
			 RF_Set.Channel = 0;
			break;
		default:
			 RF_Set.Channel = 76;
			break;
	}
	R_RX_Set_Channel_Num --;
	if(R_RX_Set_Channel_Num == 0)
	{
		R_RX_Set_Channel_Num = 3;
	}
}
/**************************************************************************
* @brief: clear rx data
* @param[in]:
* @param[out]: 
* @return:
* @others:  
***************************************************************************/	
void Clear_RX_Data(void)
{
	xdata uint8 i;
	
	for(i=0;i<C_Payload_Len+1;i++)
	{
		RX_Number[i] = 0;
	}
}		
/**************************************************************************
* @brief:take frequency hopping algorithm in tx function
* @param[in]:
* @param[out]: F_TX_PKT_OK(1:tx ok 0:tx error)
* @return:
* @others:after enter tx state,need some time to wait pkt signal pull up 
* the wait time ≈ 24*(C_Payload_Len+1)+316 (us)
***************************************************************************/
extern void blePacketEncode( uint8 *Ptr, uint8 len, uint8 chan);
extern code	uint8	chLe[3];
void AiP4952_TX_Data(uint8 *Ptr ,uint8 Len)
{
xdata   uint8 i,j;																	
xdata 	uint8 R_TX_PKT_State = 0;

	Download_ble_Data();
	blePacketEncode(ble_tx_buffer, Len+1, chLe[0]);
	RF_TX_Set_Channel(0);
	AiP4952_Clear_TX_FIFO();
	AiP4952_Write_FIFO(Ptr ,Len);//AiP4952_Write_FIFO(Ptr ,Len);//
	for(j = 0; j < 10; j++)//only tx in 37ch(2402MHz)
	{
		for(ch = 0; ch < 1; ch++)  
		{
//			P_LED_TX = 1;
			AiP4952_TX_State();		
			delay_5us(140);					//delay about 700us to wait pkt signal pull up 
			for(i=0;i<30;i++)						
			{	
				R_TX_PKT_State = (uint8)AiP4952_ReadReg(0x16); //AiP4952_ReadReg(0x16) spends about 70us
				if( R_TX_PKT_State & 0x40 )//whether the pkt is received
				{			
					R_TX_PKT_State = 0;							
					i=51;
					F_TX_PKT_OK = 1;
				}
				delay_5us(5);	//read pkt again for ever 50us if  pkt signal is still low level
			}          
//			P_LED_TX = 0;	
		}
	}
}
/**************************************************************************
* @brief:  check the rx packet data from tx device
* @param[in]:
* @param[out]: 
* @return:
* @others:
***************************************************************************/
void Check_RX_Data(void)
{
	xdata	uint8 k;
	xdata	uint16 Check_RX_Sum = 0;
	
//	if(F_RX_Head == 1)
//	{
//		F_RX_Head = 0;
//		for(k=0;k<C_Payload_Len-1;k++)
//		{
//			Check_RX_Sum += RX_Number[k];
//		}
//		if( ( RX_Number[C_Payload_Len-1] == (Check_RX_Sum & 0xFF) ) &&
//			  ( RX_Number[C_Payload_Len] == (Check_RX_Sum >>8) ) )
//		{
//			F_Check_OK = 1;
//		}
//	}
	if(F_RX_Head == 1)
	{
			F_RX_Head = 0;
			buffer[0] = 0xCF; //0x42
			buffer[1] = 0xF7; //37
			buffer[2] = 0x57; //MAC_0
			buffer[3] = 0xB0; //MAC_1
			buffer[4] = 0x1F; //MAC_2
			bleWhiten( buffer ,39,bleWhitenStart(chLe[0]) );
		
			for(k=0;k<20;k++)
			{
				Check_RX_Sum += buffer[k+17];
			}
			if( ( buffer[37] == (Check_RX_Sum >>8) ) &&
					( buffer[38] == (Check_RX_Sum & 0xFF) ) )
			{
				F_Check_OK = 1;
			}
	}
}

/**************************************************************************
* @brief:delay function
* @param[in]:
* @param[out]: 
* @return:
* @others:
***************************************************************************/	
void delay_5us(uint8 z)
{
	xdata uint8 x,y;
	for(x = z;x > 0;x--)
      for(y = 2;y > 0;y--); // for(y = 30;y > 0;y--);
}
/**************************************************************************
* @brief:delay function
* @param[in]:
* @param[out]: 
* @return:
* @others:
***************************************************************************/
void delay_100us(uint8 c)   
{
  xdata uint8 b;
	xdata uint16 a;
	
	for(b = c;b > 0;b--)
			for(a = 95 ;a > 0;a--);//for(a = 95 ;a > 0;a--);
}
extern xdata uint8	R_Check_Header[];
void AiP4952_RX_Data(void) 
{
	uint8 R_RX_Reg_State = 0;
	
	
		
	if(F_Reset_RxState == 1 )
	{			
		//delay_5us(100);      //delay about 500us to make sure the rf-chip stable 
		if(gStep.Bit.Step_1 == 0)
		{
				gStep.Bit.Step_1 = 1;
				F_Reset_RxState = 0;
				RF_RX_Set_Channel();	//only rx in 37ch(2402MHz)
				AiP4952_Clear_RX_FIFO();		
				AiP4952_RX_State();
		}
		else
		{
				gStep.Bit.Step_1 = 0;
		}
	}
	
	R_RX_Reg_State = (uint8)AiP4952_ReadReg(0x16);	//AiP4952_ReadReg(0x16) spends about 70us	
	R_ReadReg_Cnt ++;
	if(R_ReadReg_Cnt >= 30)
	{
		R_ReadReg_Cnt = 0;		//clear counter if timer out
		F_Reset_RxState = 1;	//enter next channel
	}
	if(R_RX_Reg_State & 0x80)// whether the syncword is received
	{
//		P_Test_Pin_1 = ~P_Test_Pin_1;
		delay_5us(30); 			 //need some time to let the rx device write data into rx-fifo
		AiP4952_Idle_State();//the first byte of payload does not indicate the packet length,
//												 //rx state must be turned off by software
		R_RX_Reg_State = 0;
		R_ReadReg_Cnt = 0;    //clear counter if gets signal
		F_Reset_RxState = 1;	//enter next channel

		Clear_RX_Data();
		AiP4952_Read_FIFO(buffer+5,34);
		if( (buffer[5] == R_Check_Header[0]) && (buffer[6] == R_Check_Header[1]) && 
			  (buffer[7] == R_Check_Header[2]) )
		{
			F_RX_Head = 1;
		}
	}

}

#endif
