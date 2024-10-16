#include "ThreeStateScan.h"//功能说明 三态，正反转扫描

//xdata sScanStep = 0;

//所有配置成输入
void configInput_io(void)
{
	 P0_DM0  &=0x20;
	 P2_DM0  &=0xfd;
}


void led_1(u8 v)
{
		P0_DM0 |= 1;
		L1_io = v;
}



void led_2(u8 v)
{
	P0_DM0 |= 2;				
	L2_io = v;
}
void led_3(u8 v)
{
	P0_DM0 |= 4;
	L3_io = v;
}

void led_4(u8 v)
{
	P0_DM0 |= 8;						
	L4_io = v;
}

void led_5(u8 V)
{
		
	P0_DM0 |= 16;						
	L5_io = V;
}

void led_6(u8 V)
{
	P0_DM0 |= 64;	
	L6_io = V;
}

void led_7(u8 V)
{
	P0_DM0 |= 128;	
	L7_io = V;
}


void led_8(u8 V)
{
	P2_DM0 |= 0x02;	
	L8_io = V;
}

/************************************************************************************************************************************************
 * 函数： LED_Scan    
 * 功能说明 三态，正反转扫描
			
 * 输入：无  
 * 输出：无
 * 注意： 红色led灯单独扫描
*************************************************************************************************************************************************/
void  LED_Scan(void)
{

//	switch(gstLED_State.Bit.step)
//	{ 
//			case 0:
//			{
//				configInput_io();
//				if(gstLED_State.all&0x7f000000)
//				{
//					
//					led_1(OFF);	
//				
//					if(gstLED_State.Bit.b0)//led1
//					{
//							led_2(ON);
//					}
//					
//					if(gstLED_State.Bit.b1)//led 2
//					{
//						  led_3(ON);
//					}
//					
//				  if(gstLED_State.Bit.b2)//led 3
//					{
//							 led_4(ON);
//					}
//	
//				  if(gstLED_State.Bit.b3)//led 4
//					{
//								led_5(ON);
//					}
//	
//				  if(gstLED_State.Bit.b4)//led 5
//					{	
//								led_6(ON);
//					}
//					
//					if(gstLED_State.Bit.b5)//led6
//					{
//							led_7(ON);
//					}
//				  if(gstLED_State.Bit.b6)//led 7
//					{
//							led_8(ON);
//					}
//					
//				}
//				gstLED_State.Bit.step++;				
//			}
//			break;
//			
//			case 1:
//			{
//				
//				configInput_io();
//				if(gstLED_State.all&0x3f800000)
//				{
//					
//					led_2(OFF);
//				
//					
//					if(gstLED_State.Bit.b7)//led 8 hong deng 
//					{
//							led_1(ON);
//					}
//					if(gstLED_State.Bit.b8)
//					{
//							led_3(ON);
//					}
//					
//					if(gstLED_State.Bit.b9)
//					{	
//							led_4(ON);
//					}
//					if(gstLED_State.Bit.b10)
//					{
//							led_5(ON);
//					}
//				
//					if(gstLED_State.Bit.b11)//led12
//					{
//							led_6(ON);
//					}
//					
//					
//				  if(gstLED_State.Bit.b12)//led13
//					{
//							led_7(ON);
//					}
//					
//					
//				  if(gstLED_State.Bit.b13)//led14
//					{
//							led_8(ON);
//					}
//				}

//					gstLED_State.Bit.step++;	
//			}
//			break;
//		
//			
//			case 2:
//			{
//					configInput_io();
//					if(!gstLED_State.Bit.b14 && !gstLED_State.Bit.b15 && !gstLED_State.Bit.b16 && !gstLED_State.Bit.b17)
//					{
//							gstLED_State.Bit.step ++;// 
//					}
//					else
//					{
//							
//							led_3(OFF);
//						
//							if(gstLED_State.Bit.b14)//led15
//							{	
//									led_1(ON);
//							}		
//							
//							if(gstLED_State.Bit.b15)//led16
//							{
//									led_2(ON);
//							}
//							
//							if(gstLED_State.Bit.b16)//led17
//							{
//									led_4(ON);
//							}					
//							
//							if(gstLED_State.Bit.b17)//b18 b19 b20
//							{
//									led_5(ON);led_6(ON);led_7(ON);led_8(ON);
//							}
//							gstLED_State.Bit.step ++;// 
//					}
//		
//			}
//			break;
//	
//			case 3:
//			{
//					configInput_io();
//					if(!gstLED_State.Bit.b21)
//					{
//							gstLED_State.Bit.step++;	
//					}
//					else
//					{
//							
//							led_4(OFF);
//							
//							if(gstLED_State.Bit.b21)
//							{
//									led_5(ON);led_6(ON);led_7(ON);led_8(ON);
//									led_1(ON);led_2(ON);led_3(ON);
//							}	
//							gstLED_State.Bit.step ++;// 
//					}			
//			}
//			break;
//			
//			case 4:
//			{
//					configInput_io();	
//					if(!gstLED_State.Bit.b21 && !gstLED_State.Bit.b27 && !gstLED_State.Bit.b28)
//					{
//							gstLED_State.Bit.step =0;
//					}
//					else
//					{
//								
//							led_5(OFF);
//			
//							if(gstLED_State.Bit.b21)
//							{	
//									led_4(ON);led_6(ON);
//									led_1(ON);led_2(ON);led_3(ON);
//							}	
//							if(gstLED_State.Bit.b22)
//							{
//									led_2(ON);led_3(ON);
//							}
//							
//							
//							if(gstLED_State.Bit.b27)
//							{
//									led_7(ON);
//							}	
//							
//							if(gstLED_State.Bit.b28)
//							{	
//									led_8(ON);
//							}
//							gstLED_State.Bit.step =0;
//					}	
//			}
//			break;
//			

//			
//			default:
//				break;
//		}
				
}