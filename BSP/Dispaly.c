
#include "Dispaly.h"
#include "TM1628.h"



extern void ShuMaGuanDis_1(byte v);
extern void ShuMaGuanDis_2(byte v);
 xdata  byte 	xxxx[2] ;
 xdata  byte 	ShuMaGuanDis[7] ;

 xdata u8 DataNum1[23]={
  CHAR1_0,
  CHAR1_1,
  CHAR1_2,
  CHAR1_3,
  CHAR1_4,
  CHAR1_5,
  CHAR1_6,
  CHAR1_7,
  CHAR1_8,
  CHAR1_9,
  CHAR1_A,
  CHAR1_b,
  CHAR1_C,
  //CHAR1_d,
  CHAR1_D,
  CHAR1_E,
  CHAR1_F,
  CHAR1_H,
  CHAR1_o,
  CHAR1_P,
  CHAR1_N,
  CHAR1_n, 
  CHAR1_U,
	CHAR1__
};


void display_standby(void)
{
	xxxx[0].all = DataNum1[22];
	xxxx[1].all = DataNum1[22];
}

void display_Close(void)
{
		xxxx[0].all = 0;
		xxxx[1].all = 0;
		ShuMaGuanDis[0].all = 0;
		ShuMaGuanDis[1].all = 0;
		ShuMaGuanDis[2].all = 0;
		ShuMaGuanDis[3].all = 0;
		ShuMaGuanDis[4].all = 0;
		ShuMaGuanDis[5].all = 0;
		ShuMaGuanDis[6].all = 0;
}

u8 GetDisplayValue(u8 v)
{		
	u8 tem = v;
	if(tem == 0)
		return ShuMaGuanDis[0].all;
	else if(tem == 1)
		return ShuMaGuanDis[3].all;
	else
		return ShuMaGuanDis[0].all;
}

void SetIcon_ShuShui_1628(u8 v)
{
		u8 tem = v;
		if(tem > 0)
			ShuMaGuanDis[2].all |= 0x01;
		else
			ShuMaGuanDis[2].all &= 0xfe;
}

void SetIcon_DingShi_1628  (u8 v)
{
		u8 tem = v;
		if(tem > 0)
			ShuMaGuanDis[2].all |= 0x02;
		else
			ShuMaGuanDis[2].all &= 0xfd;
}

void SetIcon_ChuMan_1628(u8 v)
{
		u8 tem = v;
		if(tem > 0)
			ShuMaGuanDis[2].all |= 0x04;
		else
			ShuMaGuanDis[2].all &= 0xfb;
}

void SetIconH_1628(u8 v)
{
		u8 tem = v;
		if(tem > 0)
			xxxx[0].all |= 0x80;//伴随动作
		else
			xxxx[0].all &= 0x7f;//伴随动作
}

void SetIconC_1628(u8 v)
{
		u8 tem = v;
		if(tem > 0)
			xxxx[1].all |= 0x80;//伴随动作
		else
			xxxx[1].all &= 0x7f;//伴随动作
}

//10进制 显示 
void display_dec(u8 v)
{
		u8 tem = v;
		if(tem >99)
			return;
		tem = v%10;
		xxxx[0].all =DataNum1[tem];
		tem = v*0.1;
		xxxx[1].all =DataNum1[tem];
}

//16进制 显示 
void display_hex(u8 v)
{
		volatile u8 tem = v;
		tem = v&0x0f;
		xxxx[0].all =DataNum1[tem];
		tem = v>>4;
		tem &=0x0f;
		xxxx[1].all =DataNum1[tem];	
		
}

//log 显示 
void display_log(u8 v)
{
	u8 tem = v;
	if(tem > 0)
		ShuMaGuanDis[2].all |= 0x78;
	else
		ShuMaGuanDis[2].all &= 0x87;
}

void LED_Key_1628(u8 v1,u8 v2)
{
		ShuMaGuanDis[3].all = v1;
	  ShuMaGuanDis[4].all = v2;
}	

void SetIcon_AllLight_ON(void)
{
	  u8 i;
		for(i= 0;i<7;i++)
		{
				ShuMaGuanDis[i].all =0xff;
		}
		for(i= 0;i<2;i++)
		{
				xxxx[i].all =0xff;
		}
}

void display_process(u8 u)
{
	if(u == 0)
	{
		ShuMaGuanDis[1].all = xxxx[1].all;
		ShuMaGuanDis[0].all = xxxx[0].all;
		ShuMaGuanDis[5].all = ShuMaGuanDis[0].all;
		ShuMaGuanDis[6].all = ShuMaGuanDis[1].all;
	}
	else if(u == 1)
	{
		ShuMaGuanDis[6].all = xxxx[1].all;
		ShuMaGuanDis[5].all = xxxx[0].all;
	}
	
	else
	{
		ShuMaGuanDis[1].all = xxxx[1].all;
		ShuMaGuanDis[0].all = xxxx[0].all;
	}
	  
	TM1628_Write_Seg((u8 *)ShuMaGuanDis,7);
}



