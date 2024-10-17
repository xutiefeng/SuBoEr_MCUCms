#include"TM1628.h"

//时间计算基于12M晶振

//unsigned char TM_Key_Val[5] = {0};

//_I unsigned char TabAdd[TM_Com_Max * 2] = 
//{
//	TM_COM_1_L,
//	TM_COM_1_H,
//	TM_COM_2_L,
//	TM_COM_2_H,
//	TM_COM_3_L,
//	TM_COM_3_H,
//	TM_COM_4_L,
//	TM_COM_4_H,
//	TM_COM_5_L,
//	TM_COM_5_H,
//};

void TM1628_Write(unsigned char Data)
{
	unsigned char	i;
	DIO_OutPut();
	for(i = 0;i < 8;i ++)
	{
		if((Data & 0X01))
		{
			DIO_SET();
		}
		else
		{
			DIO_CLR();
		}
		//Delay_us(2);
		CLK_CLR();
		//Delay_us(2);
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
		//NOP(),NOP(),NOP(),NOP(),NOP();
		//NOP(),NOP(),NOP(),NOP(),NOP();
		CLK_SET();
		//Delay_us(2);
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
		//NOP(),NOP(),NOP(),NOP(),NOP();
		//NOP(),NOP(),NOP(),NOP(),NOP();
		Data >>= 1;
	}
}

/*
unsigned char TM1628_Read(void)
{
	unsigned char	i;
	unsigned char Data = 0;
	
	PortS_InPut(P1CR,BIT3);
	DIO_SET();
	for(i = 0;i < 8;i ++)
	{
		CLK_SET();
		//Delay_us(2);
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
		CLK_CLR();
		//Delay_us(2);
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
		Data |= DIO_Read();
		Data <<= 1;
	}
	CLK_SET();
	PortS_OutPut(P1CR,BIT3);
	return(Data);
}

void TM1628_Write_CMD_Data(unsigned char CMD,unsigned char Data)
{
	STB_SET();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
	STB_CLR();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
	TM1628_Write(CMD);
	TM1628_Write(Data);
	STB_SET();
	//Delay_us(2);
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
}
*/

void TM1628_Write_CMD(unsigned char CMD)
{
	STB_SET();
	//Delay_us(2);
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
//	NOP(),NOP(),NOP(),NOP(),NOP();
//	NOP(),NOP(),NOP(),NOP(),NOP();
	STB_CLR();
	NOP(),NOP(),NOP(),NOP(),NOP();
	NOP(),NOP(),NOP(),NOP(),NOP();
//	NOP(),NOP(),NOP(),NOP(),NOP();
//	NOP(),NOP(),NOP(),NOP(),NOP();
	//Delay_us(2);
	//TM1628_Write(CMD);
	TM1628_Write_Data(CMD);
}

void TM1628_Write_Data(unsigned char Data)
{
//	TM1628_Write(Data);
	xdata unsigned char	i;
	DIO_OutPut();
	for(i = 0;i < 8;i ++)
	{
		if((Data & 0X01))
		{
			DIO_SET();
		}
		else
		{
			DIO_CLR();
		}
		NOP(),NOP(),NOP(),NOP(),NOP();//Delay_us(2);
		CLK_CLR();
		NOP(),NOP(),NOP(),NOP(),NOP();
//		NOP(),NOP(),NOP(),NOP(),NOP();

		CLK_SET();
		NOP(),NOP(),NOP(),NOP(),NOP();
//		NOP(),NOP(),NOP(),NOP(),NOP();
		Data >>= 1;
	}
}

void TM1628_Write_Seg( unsigned char *pData,unsigned char	Sum)		//0.1mS + nCOM * 0.1mS
{
	unsigned char i;
	unsigned char *p =pData;
	unsigned char temp;
	STB_OutPut();
	CLK_OutPut();
	DIO_OutPut();
#if(TM_Com_Max == 4)
	TM1628_Write_CMD(CMD_Display_Mode | CMD_Mode_4COM_13SEG);
#elif(TM_Com_Max == 5)
	TM1628_Write_CMD(CMD_Display_Mode | CMD_Mode_5COM_12SEG);
#elif(TM_Com_Max == 6)
	TM1628_Write_CMD(CMD_Display_Mode | CMD_Mode_6COM_11SEG);
#elif(TM_Com_Max == 7)
	TM1628_Write_CMD(CMD_Display_Mode | CMD_Mode_7COM_10SEG);
#endif
	TM1628_Write_CMD(CMD_Display_DATA | CMD_DATA_ADD_Inc);		
	TM1628_Write_CMD(CMD_Display_ADD | CMD_Dis_Add_Start);
	for(i = 0;i < Sum;i ++)
	{
		temp = *p;
		TM1628_Write_Data(p[i]);
		TM1628_Write_Data(p[i]);
	}
	TM1628_Write_CMD(CMD_Display_Dis | CMD_Dis_Pulse_4_16 | CMD_Dis_Switch_On);
	STB_SET();
	NOP(),NOP(),NOP(),NOP(),NOP();
	CLK_SET();
	NOP(),NOP(),NOP(),NOP(),NOP();
	DIO_SET();
}

unsigned char TM1628_Read(void)
{
	unsigned char i;
	unsigned char tmp;
	CLK_SET();
	DIO_InPut();
	DIO_SET();
	for(i = 0;i < 8; i ++)
	{
		CLK_CLR();
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
//		NOP(),NOP(),NOP(),NOP(),NOP();
//		NOP(),NOP(),NOP(),NOP(),NOP();
		tmp <<= 1;
		if(DIO_Read())
		{
			tmp |= 1;
		}
		CLK_SET();
		NOP(),NOP(),NOP(),NOP(),NOP();
		NOP(),NOP(),NOP(),NOP(),NOP();
//		NOP(),NOP(),NOP(),NOP(),NOP();
//		NOP(),NOP(),NOP(),NOP(),NOP();
	}
	return(tmp);
}
/*
void TM1628_Read_Key(void)
{
	unsigned char i;
	TM1628_Write_CMD((CMD_Display_DATA | CMD_DATA_Read_Key));
	for(i = 0;i < 5;i ++)
	{
		TM_Key_Val[i] = TM1628_Read();
	}
	STB_SET();
	CLK_SET();
	DIO_SET();
}

unsigned long TM1628_Key_Process(void)		//
{
	unsigned long tmp;
	unsigned long Key_Val = 0l;
	unsigned char i;

	for(i = 0;i < 5;i ++)
	{
		tmp = TM_Key_Val[i];
		tmp <<= (6 * i);
		Key_Val |= tmp;
	}
	return(Key_Val);
}
*/
void TM1628_Init(void)
{
//Port Init
	{
//		STB_OutPut();
//		CLK_OutPut();
//		DIO_OutPut();
		STB_SET();
		CLK_SET();
		DIO_SET();
		NOP();
	}
//DATA Init
	{
		unsigned char i;

		//TM_Key_Val[0]	=	0;
		//TM_Key_Val[1]	=	0;
		//TM_Key_Val[2]	=	0;
		//TM_Key_Val[3]	=	0;
		//TM_Key_Val[4]	=	0;

#if(TM_Com_Max == 4)
		TM1628_Write_CMD(CMD_Display_Mode | CMD_Mode_4COM_13SEG);
#elif(TM_Com_Max == 5)
		TM1628_Write_CMD(CMD_Display_Mode | CMD_Mode_5COM_12SEG);
#elif(TM_Com_Max == 6)
		TM1628_Write_CMD(CMD_Display_Mode | CMD_Mode_6COM_11SEG);
#elif(TM_Com_Max == 7)
		TM1628_Write_CMD(CMD_Display_Mode | CMD_Mode_7COM_10SEG);
#endif
		TM1628_Write_CMD(CMD_Display_DATA);
		TM1628_Write_CMD(CMD_Display_ADD | CMD_Dis_Add_Start);
		for(i = 0;i < 0x0f;i ++)
		{
			TM1628_Write_Data(0x00);
		}
		TM1628_Write_CMD(CMD_Display_Dis | CMD_Dis_Pulse_14_16 | CMD_Dis_Switch_On);
	}
	STB_SET();
	CLK_SET();
	DIO_SET();
}





































