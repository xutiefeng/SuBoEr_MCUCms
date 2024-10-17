#ifndef TM_16XX_H
#define TM_16XX_H


#include "intrins.h"
#include "HC89F3541.h"

#define u8 unsigned char
#define HuiDu_1_16  0x88
#define HuiDu_2_16  0x89
#define HuiDu_4_16  0x8A
#define HuiDu_10_16  0x8B
#define HuiDu_11_16  0x8C
#define HuiDu_12_16  0x8D
#define HuiDu_13_16  0x8E
#define HuiDu_14_16  0x8F
#define HuiDu_0_16  0x80

typedef union
{
	u8	all;
	struct
	{
		u8 b0	:1;
		u8 b1	:1;
		u8 b2	:1;
		u8 b3	:1;
		u8 b4	:1;
		u8 b5	:1;
		u8 b6	:1;
		u8 b7	:1;
	}Bit;
}byte;
	
extern byte   A_Disp_buf[];

#define MainCtrolFlag A_Disp_buf[0].Bit.b4

void xianshi(void);

#endif