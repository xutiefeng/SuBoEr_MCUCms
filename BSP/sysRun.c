
////////min sys//////
//#include "globe.h"
//#include "clib.h"
//#include "FuncTab.h"
//#include "sysRun.h"
//#include "buzzer.h"
//#include "string.h"
#include "includeall.h"
//#include "AiP4952_Apply.h"	
//#include "Dispaly,h"
//extern void SetSysRunTime(u8 v);
//extern u8 GetSysRunTime(void);
//extern void  LED_Scan(void);
//extern void display_hex(u8 v);
//extern void display_dec(u8 v);
//extern void display_log(u8 v);
//extern void SetIcon_DingShi_1628(u8 v);
//extern void SetIcon_ShuShui_1628(u8 v);
//extern void SetIcon_ChuMan_1628 (u8 v);
//extern void LED_Key_1628(u8 v1,u8 v2);
//extern void display_process(u8 u);
//void CloseFuZai(void)
//{
//	HEAT_io =  0;
//}

//void sysRest(void)
//{
//	 SetSysRunTime(gSetSysRunTime);
// 	 memset(gbFlagData,0,sizeof(gbFlagData));
//	 memset(&gstRDsysTick,0,sizeof(gstRDsysTick));
//	 CloseFuZai();
//	 Auto1Flag = 0;
//	 Auto2Flag = 0;
//	 Auto3Flag = 0;
//	 SysRunFlag = 0;
//	 gstFactory.RunTimeMax = 0;
//   
//	 gStep.Bit.sStep = 0;
//	 BuzzerFlag = 1;
//	 SetNoKeyTime(200);
//	 HeatInit();
//	 SetLED_Init();
//	 CheckFinishFlag = 0;
//}

//void DaiJiMode(void)
//{
//	 SetSysRunTime(gSetSysRunTime);
//	 CloseFuZai();
//	 display_Close();
//	 display_standby();
//}

//u8 SelfCheck(void)
//{
//	u8 sw;
//	
//	if(SysRunFlag)
//		return 0;
//	
//	if(CheckFinishFlag)
//		return 0;

//	switch(gStep.Bit.sStep)
//	{
//		case 0:
//		
//			sw = AccompanyFunc_OnOffHandle1(&gHeatTime,gStep.Bit.sStep,LEDOnOffTimeTab);
//			
//			if(sw == 1)
//			{
//					display_Heat(ON);
//				  SetIcon_AllLight_ON();
//			}
//			else
//			{
//					display_Heat(OFF);
//			}
//			
//			if(gHeatTime == 0)
//			{
//					CheckFinishFlag = 1;
//			}

//		break;
//		
//		default:
//			break;

//		return 0;
//	}
//}
//void display_logic(void)
//{
//	extern  void SetIconH_1628(u8 v);
//	extern  void SetIconC_1628(u8 v);
//	  static xdata u8 sBlinkTime;
//	  u8 sw;

//		if(!CheckFinishFlag)
//			return;
//		if(SysRunFlag)
//		{
//				
//				if(Auto3Flag && !JieDianDisplayFlag)
//				{
//						display_hex(0xf0);
//  					SetIconH_1628(OFF);
//						SetIconC_1628(OFF);
//						SetIcon_ChuMan_1628(ON);
//						SetIcon_ShuShui_1628(OFF);
//						SetIcon_DingShi_1628(OFF);
//				}
//				else if(Auto1Flag && !JieDianDisplayFlag)
//				{
//						display_dec(36);
//						SetIconC_1628(ON);
//						SetIconH_1628(OFF);
//						SetIcon_ChuMan_1628(OFF);
//						SetIcon_ShuShui_1628(ON);
//						SetIcon_DingShi_1628(OFF);
//				}
//				else if(Auto2Flag && !JieDianDisplayFlag)
//				{						
//						SetIcon_DingShi_1628(ON);
//					  SetIcon_ShuShui_1628(OFF);
//						SetIcon_ChuMan_1628(OFF);
//					
//						sw = AccompanyFunc_OnOffHandle1(&sBlinkTime,0,LED_BinkTimeTab);						
//						
//						if(sw == 1)
//						{
//								display_dec(gSetSysRunTime);
//						}
//						else
//						{
//								display_Close();
//						}	
//						SetIconH_1628(ON);
//						SetIconC_1628(OFF);
//				}
//				else
//				{			
//						if(sKey_yyy.Bit.gNoKeyTime  == 0)
//						{
//								display_Close();
//								SetIconC_1628(OFF);
//								display_log(OFF);
//						}
//						else
//						{			
//								display_dec(getHeatLevel());
//								SetIconC_1628(ON);
//								SetIconH_1628(OFF);
//								display_log(ON);
//						}
//						
//						if(DaiJiDispalyFlag)
//						{
//								display_standby();
//								SetIcon_ChuMan(OFF);								
//						}
//						
//						if(Auto3Flag)
//						{
//								SetIcon_ChuMan(ON);
//						}
//						else if(Auto1Flag)
//						{
//								SetIcon_ShuShui_1628(ON);
//						}
//						else
//						{
//								SetIcon_DingShi_1628(ON);
//						}
//				}			
//				if(GetKeySongKai_time())
//				{
//						LED_Key_1628(0xff,0xff);//LED_Key(ON);
//				}
//				else
//				{
//						LED_Key_1628(OFF,OFF);//LED_Key(OFF);
//				}
//		}
//		else
//		{
//			if(GetKeySongKai_time()== 0)
//			{		
//					display_Close();
//					//display_log(OFF);
//			}
//			else if(GetKeySongKai_time()<= 100 )
//			{
//					//SetIcon_C(OFF);
//					display_standby();
//					LED_Key_1628(OFF,OFF);//LED_Key(OFF);//LED_Key(OFF);//PowerLed_OFF
//					
//			}
//			else
//			{
//					LED_Key_1628(0xff,0xff);//LED_Key(OFF);//LED_Key(ON);
//					
//					display_dec(25);
//					SetIconC_1628(ON);
//					SetIconH_1628(OFF);
//					display_log(ON);
//			}				
//		}
//		
//		if(getHeatLevel() == 0)
//		{
//			display_Heat(OFF);				
//		}
//		else
//		{
//			display_Heat(ON);
//		}
//}
///****************************************************************************************************************************************** 
//* 函数名称	SysRunTime
//* 功能说明	：功能运行时间倒计时，最小单位S
//* 输入：		无
//* 输出：		无
//* 注意 无
//******************************************************************************************************************************************/
//void SysRunTime(void)
//{
//		if(!SysRunFlag)
//			return ;
//		
//		if(gSysRunTime >0)
//		{
//				gSysRunTime--;
//				
//				if(gSysRunTime == 0)
//				{
//						SetLHeatLevel(GetHeatUnit(),0);
//						DaiJiDispalyFlag =1;
//				}				
//		}
//		
//}


///****************************************************************************************************************************************** 
//* 函数名称	SetSysRunTime
//* 功能说明	：设置功能运行时间
//* 输入：		时间，单位h	
//* 输出：		无
//*注意 无
//******************************************************************************************************************************************/
//void SetSysRunTime(u8 v)
//{
//	gSetSysRunTime = v;
//	gSysRunTime = gSetSysRunTime*3600;
//}

///****************************************************************************************************************************************** 
//* 函数名称	GetSysRunTime
//* 功能说明	：获取系统时间时长
//* 输入：		无	
//* 输出：		已经设置的系统时间时长
//* 注意 无
//******************************************************************************************************************************************/
//u8 GetSysRunTime(void)
//{
//	return gSetSysRunTime;
//}

///****************************************************************************************************************************************** 
//* 函数名称:	sysRuning
//* 功能说明:	逻辑框架运行
//* 输    入: 无
//* 输    出: 无
//******************************************************************************************************************************************/

void sysRuning(void)
{	
		
	EventCollect();
    switch(PopEvent())
    {  
		case evSysRest:

		break;

		case ev5MS:       
		{
	
		}	
		break;  
		
		case ev20MS:
		{
//			Kye_Scan();	         					
		}
		break;

		case ev50MS:
		{
//			KeyProsess();            					
    }
    break;
				
		case ev100MS:
		{				
						
		}
		break;
				
		case ev1S:
    {	

		}
        break;
				
        default:
        break;
    }
		
}
