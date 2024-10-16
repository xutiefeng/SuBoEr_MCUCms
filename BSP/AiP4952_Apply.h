#ifndef AIP4952_Apply_H
#define AIP4952_Apply_H

#include "AiP4952A_SPI.h"

//**********宏定义**********************************
#define   C_Payload_Len     			10-1
//******函数声明*************************************

//**********宏定义**********************************
#define   C_TX_Payload_Len     			47

void Download_Data(void);
void Clear_RX_Data(void);

void AiP4952_Sys_Init(void);
void AiP4952_Reg_Init(void);
void AiP4952_Reg_Check(void);

void RF_TX_Set_Channel(uint8 ch);
void RF_RX_Set_Channel(void);

void AiP4952_TX_Data(uint8 *TX_Number ,uint8 Len);
void AiP4952_RX_Data(void);
void Check_RX_Data(void);

void delay_5us(uint8	z);
void delay_100us(uint8 c);

#endif