

#include "includeall.h"
#include	"FuncLogic_key.h"
#include "FuncTab.h"



extern u8 GetDisplayValue(u8 v);
extern void SetSysRunTime(u8 v);
extern void display_hex(u8 v);
extern void display_dec(u8 v);

/****************************************************************************************************************************************** 
* ��������:	RestKeyProcess
* ����˵��:	��λ�����£�ȡ��������о
* ��    ��: ��	
* ��    ��: ��
* ע������:
******************************************************************************************************************************************/
void RestKeyProcess(void)
{
		//LongPress_3sFlag = 0;
}





/****************************************************************************************************************************************** 
* ��������:	GetKeySongKai_time
* ����˵��:	��ȡ�����ɿ�ʱ��
* ��    ��: ��	
* ��    ��: ��
******************************************************************************************************************************************/
u8 GetKeySongKai_time(void)
{
		 return sKey_yyy.Bit.gNoKeyTime;
}


/****************************************************************************************************************************************** 
* ��������:	KeyCancelRestKey
* ����˵��:	
* ��    ��: ��	
* ��    ��: ��
* ע������: �̰���Ч
******************************************************************************************************************************************/
void KeyCancelRestKey(void)
{
	

}

/****************************************************************************************************************************************** 
* ��������:	KeySelect
* ����˵��:	ѡ�񰴼�
* ��    ��: ��	
* ��    ��: ��
* ע������: �����������л�
******************************************************************************************************************************************/
void KeySelectMode(void)
{
		if(!SysRunFlag)
			return;
		
		if(/*!Auto1Flag && !Auto2Flag !*/Auto3Flag)
		{
				Auto1Flag = 1;
				Auto2Flag = 0;
				Auto3Flag = 0;	
				
				SetSysRunTime(DefaultTimerTab[0]);
				SetLHeatLevel(GetHeatUnit(),DefaultTempMAX_Value);
		}
		else if(Auto1Flag)
		{
				Auto1Flag = 0;
				Auto2Flag = 1;
				SetLHeatLevel(GetHeatUnit(),DefaultTempMIN_Value);
				SetSysRunTime(DefaultTimerTab[1]);
		}
		else
		{
				Auto1Flag = 0;
				Auto2Flag = 0;
				Auto3Flag = 1;
				SetSysRunTime(DefaultTimerTab[1]);
				SetLHeatLevel(GetHeatUnit(),DefaultTempMIN_Value);	
		}		
}


/****************************************************************************************************************************************** 
* ����˵��:	* ��������:	KeySelect
* ����˵��:	ѡ�񰴼�
* ��    ��: ��	
* ��    ��: ��
* ��    ��: ��	
* ��    ��: ��
* ע������:
******************************************************************************************************************************************/
void SelectWorkMode(u8 v)
{
		if(!SysRunFlag)
			return;
		
		if(v ==1)
		{
				Auto1Flag = 1;
				Auto2Flag = 0;
				Auto3Flag = 0;	
				
				SetSysRunTime(DefaultTimerTab[0]);
				SetLHeatLevel(GetHeatUnit(),DefaultTempMIN_Value);
		}
		else if(v == 2)
		{
				Auto1Flag = 0;
				Auto2Flag = 1;
				Auto3Flag = 0;	
				SetLHeatLevel(GetHeatUnit(),DefaultTempMIN_Value);
				SetSysRunTime(DefaultTimerTab[1]);
		}
		else
		{
				Auto1Flag = 0;
				Auto2Flag = 0;
				Auto3Flag = 1;
				SetSysRunTime(DefaultTimerTab[1]);
				SetLHeatLevel(GetHeatUnit(),DefaultTempMAX_Value);	
		}		
}

/****************************************************************************************************************************************** 
* ��������:	KeyLongPress
* ����˵��:	�ж��ĸ���������,ִ�е��ǿ��ػ�����
* ��    ��: ����ֵ	
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void KeyLongPress(u8 v)
{
	u8 KeyChanal = v;
	
	switch(KeyChanal)//�ж��ĸ���������
	{
		case 4://ִ�еĿ��ػ�����
			if(SysRunFlag > 0)
			{
				sysRest();
				SysRunFlag = 0;
				DaiJiDispalyFlag = 0;
				SetLHeatLevel(GetHeatUnit(),0);
				
				SetNoKeyTime(0);	
			}
			else
			{
				SysRunFlag = 1;		
				DaiJiDispalyFlag = 0 ;
				SetLHeatLevel(GetHeatUnit(),DefaultTempMIN_Value);
				display_dec(getHeatLevel());
			}
			BuzzerFlag =1;
		break;
		
		case 0x40:
				SelectWorkMode(3);
				BuzzerFlag =1;
		break;
		
		
		
		default:
			break;
			
	}
}

/****************************************************************************************************************************************** 
* ��������:	KeyShortPress
* ����˵��:	�ж��ĸ���������
* ��    ��: ����ֵ	
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/

void KeyShortPress(u8 v)
{
	u8 KeyChanal = v;
	u8 level = getHeatLevel();
	u8 temp =GetDisplayValue(GetHeatUnit()); 
	
	if(DaiJiDispalyFlag)
	{
			DaiJiDispalyFlag = 0;
			display_dec(getHeatLevel());
			SetSysRunTime(DefaultTimerTab[1]);
			return;
	}
  
	switch(KeyChanal)//�ж��ĸ���������
	{
			
			
			case 2:	

			if(Auto1Flag || Auto3Flag || !SysRunFlag)
			{
					BuzzerFlag =1;
					return;
			}
					
			
			
			if(Auto2Flag)
			{
					level = GetSysRunTime();
					if(level  >= DefaultTimerTab[2])
					{
							SetSysRunTime(DefaultTimerTab[2]);
					}
					else
					{
							SetSysRunTime(level+1);
					}
			}
			else
			{
				if(temp == 0)
				{
						display_dec(getHeatLevel());
				}
				else
				{
						if(level  >= DefaultTempMAX_Value)
						{
								SetLHeatLevel(GetHeatUnit(),DefaultTempMAX_Value);
						}
						else if(level == 0)
						{
								SetLHeatLevel(GetHeatUnit(),DefaultTempMIN_Value);
						}
						else
						{		
								SetLHeatLevel(GetHeatUnit(),level+1);
						}	
						display_dec(getHeatLevel());
				}														
			}		
			BuzzerFlag =1;
			
			break;
			
			case 8:
				//HeatModeSwitch();
				BuzzerFlag =1;
			break;
			
			case 0x20:	
				if(Auto1Flag || Auto3Flag || !SysRunFlag)
				{
						BuzzerFlag =1;
						return;
				}
					
				if(Auto2Flag)
				{
					level = GetSysRunTime();
					if(level  <= DefaultTimerTab[1])
					{
							SetSysRunTime(DefaultTimerTab[1]);
					}
					else
					{
							SetSysRunTime(level-1);
					}
				}
				else
				{
					if(temp == 0)
					{
							display_dec(getHeatLevel());
					}
					else
					{
						if(level  <= DefaultTempMIN_Value)
						{
								SetLHeatLevel(GetHeatUnit(),DefaultTempMIN_Value);
						}
						else
						{
								SetLHeatLevel(GetHeatUnit(),level-1);
						}
						display_dec(getHeatLevel());
					}
						
				}
				BuzzerFlag =1;
				break;
			
			case 1:
				SelectWorkMode(1);
				BuzzerFlag =1;
			break;
			
			
			
			case 0x10:
				SelectWorkMode(2);
				BuzzerFlag =1;
			break;
			
			default :
				break;			
	}
}

 void 	QuitMode(void)
 {	 
	Auto1Flag = 0;
	Auto2Flag = 0;
	Auto3Flag = 0;			
 }
 

/****************************************************************************************************************************************** 
* ��������:	JieDianMode
* ����˵��:	�����������̰�����
* ��    ��: ��	
* ��    ��: ��
* ע������: ����ʱ��50ms
******************************************************************************************************************************************/
void JieDianMode(u16 xxx)
{ 
		STKeyType v;
	
		v.all = xxx;
		JieDianDisplayFlag = 0;
		if(Auto2Flag)
		{
			if(v.Bit.gNoKeyTime == 100)
			{
					Auto2Flag = 0;
					display_dec(getHeatLevel());
			}
		}
		if(v.Bit.gNoKeyTime == 0)
		{
				JieDianDisplayFlag = 1;//QuitMode();
		}
				
}
#define NO_KEY_PRESS_VALUE 0
//void KeyProsess(void)
//{
//		u8 KeyValue,level;
//	
//		if(!CheckFinishFlag)
//			return;
//		
//		KeyValue = getKeyValue();
//		level   =  getHeatLevel();
//		
//		if(SysDelayFlag)
//		{
//				if(KeyValue == NO_KEY_PRESS_VALUE)
//				{
//						SysDelayFlag = 0;
//				}
//				sKey_yyy.Bit.sProsessTime = !NO_KEY_PRESS_VALUE;
//				return ;
//		}
//		
//		if(KeyValue > 0  )
//		{
//				sKey_yyy.Bit.gNoKeyTime = 200;
//				if(sKey_yyy.Bit.sProsessTime <0x3f)
//					sKey_yyy.Bit.sProsessTime++;
//			
//				if(sKey_yyy.Bit.sProsessTime >= _3S_Per50MS && sKey_yyy.Bit.sProsessTime<0x3f)//long press
//				{					
//						SysDelayFlag = 1;//qu dou		
//						KeyLongPress(KeyValue);	  				
//						sKey_yyy.Bit.sProsessTime = 0;
//				}
//				
//			sKey_yyy.Bit.hisKey = KeyValue;

//		}
//		else
//		{
//			  if(sKey_yyy.Bit.gNoKeyTime > 0)//�ڵ�ģʽ����ʱ
//			  {
//						sKey_yyy.Bit.gNoKeyTime--;						
//						JieDianMode(sKey_yyy.all);	
//			  }
//	   
//				if(sKey_yyy.Bit.sProsessTime >= 1 && sKey_yyy.Bit.sProsessTime < _2S_Per50MS)//short press
//				{				
//							KeyShortPress(sKey_yyy.Bit.hisKey);
//				}
//				sKey_yyy.Bit.sProsessTime = 0;
//		}
//}
void SetNoKeyTime(u8 v)
{
		sKey_yyy.Bit.gNoKeyTime = v;
}

void KeyProsess(void)
{
		u8 KeyValue,level;
	
		if(!CheckFinishFlag)
			return;
		
		KeyValue = getKeyValue();
		level   =  getHeatLevel();
		
		if(SysDelayFlag)
		{
				if(KeyValue == NO_KEY_PRESS_VALUE)
				{
						SysDelayFlag = 0;
				}
				sKey_yyy.Bit.sProsessTime = !NO_KEY_PRESS_VALUE;
				return ;
		}
		
		if(KeyValue > 0  )
		{
				SetNoKeyTime(200);
				if(sKey_yyy.Bit.sProsessTime <0x3f)
					sKey_yyy.Bit.sProsessTime++;
				else
					return;
			
				if(KeyValue == 4 || KeyValue == 0x40)
				{
						if(sKey_yyy.Bit.sProsessTime >= _3S_Per50MS )//long press
						{					
								SysDelayFlag = 1;//qu dou		
								KeyLongPress(KeyValue);	  				
								sKey_yyy.Bit.sProsessTime = 0;
						}
				}
				else
				{
						sKey_yyy.Bit.sProsessTime = 0x3f;
						KeyShortPress(KeyValue);
				}			
		}
		else
		{
			  if(sKey_yyy.Bit.gNoKeyTime > 0)//�ڵ�ģʽ����ʱ
			  {
						sKey_yyy.Bit.gNoKeyTime--;						
						JieDianMode(sKey_yyy.all);	
			  }
				sKey_yyy.Bit.sProsessTime = 0;
		}
}
