#ifndef	__TM1628_H__
#define	__TM1628_H__




#include "includeall.h"

#define	TM_Com_Max		7




#define	STB_SET()	Port_STB = 1
#define	STB_CLR()	Port_STB = 0

#define	CLK_SET()	Port_CLK = 1
#define	CLK_CLR()	Port_CLK = 0

#define	DIO_SET()	Port_DIO = 1
#define	DIO_CLR()	Port_DIO = 0

#define	DIO_Read()	1//Port_DIO

#define	CLK_OutPut()	//GPIO_ENABLE_OUTPUT(P0TRIS,GPIO_PIN_3)
#define	STB_OutPut()	//GPIO_ENABLE_OUTPUT(P0TRIS,GPIO_PIN_4)

#define	DIO_InPut()		//GPIO_ENABLE_OUTPUT(P0TRIS,GPIO_PIN_3)
#define	DIO_OutPut()	//GPIO_ENABLE_OUTPUT(P0TRIS,GPIO_PIN_3)

#define	TM_COM_1_L		0X00
#define	TM_COM_1_H		0X01
#define	TM_COM_2_L		0X02
#define	TM_COM_2_H		0X03
#define	TM_COM_3_L		0X04
#define	TM_COM_3_H		0X05
#define	TM_COM_4_L		0X06
#define	TM_COM_4_H		0X07
#define	TM_COM_5_L		0X08
#define	TM_COM_5_H		0X09
#define	TM_COM_6_L		0X0A
#define	TM_COM_6_H		0X0B
#define	TM_COM_7_L		0X0C
#define	TM_COM_7_H		0X0D



//CMD
#define	CMD_Display_Mode	0x00		//模式
#define	CMD_Display_DATA	0X40		//数据
#define	CMD_Display_Dis		0x80		//显示
#define	CMD_Display_ADD		0xC0		//地址

//Mode
#define	CMD_Mode_4COM_13SEG	0X00
#define	CMD_Mode_5COM_12SEG	0X01
#define	CMD_Mode_6COM_11SEG	0X02
#define	CMD_Mode_7COM_10SEG	0X03

//DATA
#define	CMD_DATA_Write_DATA		0X00
#define	CMD_DATA_Read_Key		0x02
#define	CMD_DATA_ADD_Inc		0x00	//地址自增
#define	CMD_DATA_ADD_Fixed		0x04	//固定地址
#define	CMD_DATA_TEST_Common	0x00
#define	CMD_DATA_TEST_Mode		0x08

//Display
#define	CMD_Dis_Pulse_1_16		0x00
#define	CMD_Dis_Pulse_2_16		0x01
#define	CMD_Dis_Pulse_4_16		0x02
#define	CMD_Dis_Pulse_10_16		0x03
#define	CMD_Dis_Pulse_11_16		0x04
#define	CMD_Dis_Pulse_12_16		0x05
#define	CMD_Dis_Pulse_13_16		0x06
#define	CMD_Dis_Pulse_14_16		0x07

#define	CMD_Dis_Switch_Off		0x00
#define	CMD_Dis_Switch_On		0x08

//Address
#define	CMD_Dis_Add_Start		0x00

extern unsigned char TM_Key_Val[];


void TM1628_Init(void);
void TM1628_Write(unsigned char Data);
void TM1628_Write_CMD(unsigned char CMD);
void TM1628_Write_CMD_Data(unsigned char CMD,unsigned char Data);
void TM1628_Write_Seg(unsigned char *Data,unsigned char Sum);
unsigned char TM1628_Read(void);
void TM1628_Write_Data(unsigned char Data);
unsigned long TM1628_Key_Process(void);
void TM1628_Read_Key(void);

#endif


