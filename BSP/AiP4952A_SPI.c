#include "AiP4952A_SPI.h"



xdata RF_Set_Class  RF_Set =
{
	76,				// channel
};

/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: write a byte
***************************************************************************/	
void AiP4952_WriteByte_3Line (uint8 dat) 
{
	uint8 i;
	
	for(i = 0;i < 8;i ++) 
	{	
		P_AiP4952_CLK = 0;
		P_AiP4952_CLK = 0;

		if( dat & 0x80 )
		{
			P_AiP4952_SDA = 1;
		}	
		else
		{
			P_AiP4952_SDA = 0;
		}

		P_AiP4952_CLK = 1;
		P_AiP4952_CLK = 1;
		dat = (dat<<1);
  }
  P_AiP4952_CLK = 0;
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: read a byte
***************************************************************************/		
uint8 AiP4952_ReadByte_3Line(void)		
{
	uint8 tmp;
	uint8 dat;

	SDA_Input;//P2IO &= 0xFE;								//P20配置为输入
	for(tmp=0x80;tmp!=0;tmp>>=1)
	{
		P_AiP4952_CLK = 1;
		P_AiP4952_CLK = 1;

		if(P_AiP4952_SDA == 0)
			dat &= ~tmp;		
		else 
			dat |= tmp;
		
		P_AiP4952_CLK = 0;
		P_AiP4952_CLK = 0;
	}
	P_AiP4952_CLK = 0;
	SDA_Output;//P2IO |= 0x01;								//P20配置为输出
	return dat;
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: write double bytes to register
***************************************************************************/	
void AiP4952_WriteReg(uint8 Addr, uint8 Data_High, uint8 Data_Low)
{
		P_AiP4952_CS = 0;
    AiP4952_WriteByte_3Line(Addr);					//写命令
    AiP4952_WriteByte_3Line(Data_High);
	  AiP4952_WriteByte_3Line(Data_Low);
    P_AiP4952_CS = 1; 
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: read double bytes to register(Attention: the MSB of register address must set 1)
***************************************************************************/
uint16 AiP4952_ReadReg(uint8 Addr)
{
		uint16 dat = 0;
		uint8 Data_High = 0;
		uint8 Data_Low = 0;
		
		P_AiP4952_CS = 0;
		AiP4952_WriteByte_3Line(Addr | 0x80);		//读命令，写：0，读：1
		Data_High = AiP4952_ReadByte_3Line();
		Data_Low = AiP4952_ReadByte_3Line();
		P_AiP4952_CS = 1;
		dat = (Data_High << 8) + Data_Low;
		return dat;
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: write fifo ram
***************************************************************************/		
void AiP4952_Write_FIFO(uint8 *Ptr ,uint8 Len)
{
	uint8 i,j;
	
	P_AiP4952_CS = 0;
	AiP4952_WriteByte_3Line(0x27);
	for(i = 0;i < (Len+1);i ++)
	{
		j = Ptr[i];//*(Ptr+i);
		AiP4952_WriteByte_3Line(j);
	}
	P_AiP4952_CS = 1;
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: read fifo ram
***************************************************************************/	
void AiP4952_Read_FIFO(uint8 *Ptr, uint8 Len)
{
	uint8 i;
	
	P_AiP4952_CS = 0;
	AiP4952_WriteByte_3Line(0xA8);   //0xA8:0x28|0x80,0x28:MCU读FIFO数据的接口	
	for(i = 0; i< (Len+1); i++)
	{
		*(Ptr+i) = AiP4952_ReadByte_3Line();
	}	
	P_AiP4952_CS = 1;
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: enter tx state and set channel in the same time
***************************************************************************/
void AiP4952_TX_State(void)
{
  AiP4952_WriteReg(0x00, 0x80, RF_Set.Channel & 0x7F);
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: enter rx state and set channel in the same time
***************************************************************************/
void AiP4952_RX_State(void)
{
  AiP4952_WriteReg(0x00, 0x40, RF_Set.Channel & 0x7F);
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: enter idle state and set channel in the same time
***************************************************************************/
void AiP4952_Idle_State(void)
{
  AiP4952_WriteReg(0x00, 0x00, RF_Set.Channel & 0x7F);
}
/**************************************************************************
* @brief:clear tx fifo
* @param[in]:
* @param[out]: 
* @return:
* @others:
***************************************************************************/
void AiP4952_Clear_TX_FIFO(void)
{
		AiP4952_WriteReg(0x26, 0x80, 0x80);
}
/**************************************************************************
* @brief:clear rx fifo
* @param[in]:
* @param[out]: 
* @return:
* @others:
***************************************************************************/
void AiP4952_Clear_RX_FIFO(void)
{
		AiP4952_WriteReg(0x25, 0x80, 0x80);      
}
/**************************************************************************
* @brief: spi drive
* @param[in]:
* @param[out]: 
* @return:
* @others: enter sleep state 
***************************************************************************/
//void AiP4952_Sleep_State(void)
//{
//	AiP4952_WriteReg(0x01,0x20|0x80,0x77);	//Sleep
//}

