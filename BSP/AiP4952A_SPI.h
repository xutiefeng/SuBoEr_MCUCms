
#ifndef AIP4952A_SPI_H
#define AIP4952A_SPI_H

#include "includeall.h"

typedef struct
{
		u8 Channel;
}RF_Set_Class;
#define uint8  u8
#define uint16 u16

//************************函数声明*************************************
void AiP4952_WriteByte_3Line (uint8 dat); 
uint8   AiP4952_ReadByte_3Line(void);
void AiP4952_WriteReg(uint8 Addr, uint8 Data_High, uint8 Data_Low);
uint16  AiP4952_ReadReg(uint8 Addr);
void AiP4952_Write_FIFO(uint8 *Ptr ,uint8 Len);
void AiP4952_Read_FIFO(uint8 *Ptr, uint8 Len);
void AiP4952_TX_State(void);
void AiP4952_RX_State(void);
void AiP4952_Idle_State(void);						
void AiP4952_Clear_TX_FIFO(void);	
void AiP4952_Clear_RX_FIFO(void);	
void AiP4952_Sleep_State(void);

#endif