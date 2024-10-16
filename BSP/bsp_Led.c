/*
 * @Author: xu_tie_feng xu_tie_feng@163.com
 * @Date: 2024-06-02 01:28:30
 * @LastEditors: xu_tie_feng xu_tie_feng@163.com
 * @LastEditTime: 2024-06-02 22:10:45
 * @FilePath: \LanYaDianReTan_8501\BSP\bsp_Led.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "..\bsp\bsp_Led.h"
#include "..\bsp\includeall.h"

#if  LED_CONFIG

static STLED gstLED;


xdata volatile byte32 gstLED_State;





u32 GetLedState(void)
{
	return gstLED_State.all;
}



void SetLED_Init(void)
{
//	gstLED_State.Bit.b17 = 1;
//	gstLED_State.Bit.step = 0;
}

void display_Heat(u8 v)
{
	if(v == 0)
	{
		HEAT_LED_io = 0;
	}
	else
	{
		HEAT_LED_io = 1;
	}
		
}

void LED_Key(u8 v)
{
//	switch(v)
//	{
//		case ON:
//			gstLED_State.Bit.b22 = 1;
//			gstLED_State.Bit.b21 = 1;
//		break;
//		
//		case OFF:
//			gstLED_State.Bit.b22 = 0;
//			gstLED_State.Bit.b21 = 0;
//		break;
//		
//		case PowerLed_ON:
//			gstLED_State.Bit.b22 = 0;
//			gstLED_State.Bit.b21 = 1;
//		break;
//		
//		case PowerLed_OFF:
//			gstLED_State.Bit.b22 = 0;
//		break;
//		
//		default :
//			break;
//	}
//	gstLED_State.Bit.b21 = v;
//	if(SysRunFlag)
//		gstLED_State.Bit.b22 = v;
//	else
//		gstLED_State.Bit.b22 = 0;
}

void closeAll_display(void)
{
//	gstLED_State.all = 0;
//	gstLED_State.Bit.b17 = 1;
}

//void SetIcon_C(u8 v)
//{
//	gstLED_State.Bit.b27 =v;
//	gstLED_State.Bit.b28 =0;
//}

//void SetIcon_H(u8 v)
//{
//	gstLED_State.Bit.b28 =v;
//	gstLED_State.Bit.b27 =0;
//}

void SetIcon_ShuShui (u8 v)
{
	gstLED_State.Bit.b14 =v;
	gstLED_State.Bit.b15 =0;
	gstLED_State.Bit.b16 =0;
}

void SetIcon_ChuMan (u8 v)
{
	gstLED_State.Bit.b16 =v;
	gstLED_State.Bit.b15 =0;
	gstLED_State.Bit.b14 =0;
}

void SetIcon_DingShi(u8 v)
{
	gstLED_State.Bit.b15 = v;
	gstLED_State.Bit.b14 = 0; 
	gstLED_State.Bit.b16 = 0;
}

void ShuMaGuanDis_1(byte v)
{
		
	gstLED_State.Bit.b0 = v.Bit.b0;//a
	gstLED_State.Bit.b1 = v.Bit.b1;//b
	gstLED_State.Bit.b2 = v.Bit.b2;//c
	gstLED_State.Bit.b3 = v.Bit.b3;//d
	gstLED_State.Bit.b4 = v.Bit.b4;//e
	gstLED_State.Bit.b5 = v.Bit.b5;//f
	gstLED_State.Bit.b6 = v.Bit.b6;//g
}

void ShuMaGuanDis_2(byte v)
{
	gstLED_State.Bit.b7 = v.Bit.b0;//a
	gstLED_State.Bit.b8 = v.Bit.b1;//b
	gstLED_State.Bit.b9 = v.Bit.b2;//c
	gstLED_State.Bit.b10 = v.Bit.b3;//d
	gstLED_State.Bit.b11 = v.Bit.b4;//e
	gstLED_State.Bit.b12 = v.Bit.b5;//f
	gstLED_State.Bit.b13 = v.Bit.b6;//g
}

//���ܼ���
code STLED gstLedTab[]=
{
	{LED_ID,LED_close,time_ingore},//�ػ�
	{LED_ID,BlueColor,time_ingore},//1��
	{LED_ID,MixColor, time_ingore},//2��
	{LED_ID,RedColor, time_ingore},//3��
};

u8 LED_Ctrol(STLED *pstLED)
{
		STLED *pst = pstLED;
	

		if(pstLED->time < time_ingore)//����ƹ�������ʱ����ִ��һ��ʱ����1
		{
			if(pstLED->time > 0)
			{
				pstLED->time--;
			}
			else
			{
				pstLED->action = LED_close;
			}
		}
		
		if(pstLED->action == RedColor)
		{
			Redled_io = LED_0N;
			Blueled_io = LED_0FF;
		}
		else if(pstLED->action == BlueColor)
		{
			Redled_io =  LED_0FF;
			Blueled_io = LED_0N;
		}
		else if(pstLED->action == MixColor)
		{			
			if(YellowLedFlag)
			{
					YellowLedFlag =0;
					Redled_io = LED_0N;
					Blueled_io = LED_0FF;
			}
			else
			{
					YellowLedFlag = 1;
					Redled_io =  LED_0FF;
					Blueled_io = LED_0N;
			}		
		}
		else
		{
			Redled_io =  LED_0FF;
			Blueled_io = LED_0FF;
		}
		return 0;//ִ��ok
}

void SetLed_ShortPress(u8 level)//应用于不同等级，亮什么灯
{
	u8 lev = level;
	STLED *st;
	
	if(lev > 3)
		lev = 1;
	
	st = &gstLedTab[lev];
	LED_Ctrol(st);
}

STLED* getLED(u8 id)
{
	if(id == LED_ID)
	{
		return &gstLED;//ִ��ok
	}
	return 1; // id����
}
	

#endif