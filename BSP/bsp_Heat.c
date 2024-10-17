/*
 * @Author: xu_tie_feng xu_tie_feng@163.com
 * @Date: 2024-06-02 01:28:30
 * @LastEditors: xu_tie_feng xu_tie_feng@163.com
 * @LastEditTime: 2024-06-02 20:50:56
 * @FilePath: \LanYaDianReTan_8501\BSP\bsp_Heat.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "bsp_Heat.h"
#include "Functab.h"

#if HEAT_CONFIG


static xdata  STHeat gstHeat;
static xdata  u8 sHeatLevel[___HeatToatl];


#define  TEMP_SET_VALUE_1 35
#define  TEMP_SET_VALUE_2 45
#define  TEMP_SET_VALUE_3 55

#if  HEAT_CONFIG

void HeatInit(void)
{
	sHeatLevel[0] = 0;
	sHeatLevel[1] = 0;
	gstHeat.CurMode = 0;
	gstHeat.time = 0;
	gstHeat.id = 0;
}
/****************************************************************************************************************************************** 
* 功能说明:	有传感器反馈的加热温度
* 输    入: 设置的当前温度，小于当前温度就加热
* 输    出: 无

******************************************************************************************************************************************/
void ntc_temp(u8 id,u8 setValue)
{
	if(sTemp_v < (setValue))
	{
		if(id == HEAT_ID)
		HEAT_io = 1;
		else
		HEAT_io_1 = 1;	
	}
	else
	{
		if(id == HEAT_ID)
		HEAT_io = 0;
		else
		HEAT_io_1 = 0;	
	}
}

void NTC_Process(void)
{
	if(HaveNTCFlag)
	{
		if(!SysRunFlag)
		{
			ntc_temp(HEAT_ID,OFF);
		}
		else
		{
			ntc_temp(HEAT_ID,sHeatLevel[0]);
		}
	}
	
	if(HaveNTCFlag_1)
	{
		if(!SysRunFlag)
		{
			ntc_temp(HEAT_ID_1,OFF);
		}
		else
		{
			ntc_temp(HEAT_ID_1,sHeatLevel[1]);
		}
	}
}
#endif
///****************************************************************************************************************************************** 
//* 函数名称:	SetLHeat
//* 功能说明:	无传感器反馈的普通加热
//* 输    入: 对象(id)，加热动作(acction)	，加热时间(time)
//* 输    出: 无

//******************************************************************************************************************************************/
//void  SetLHeat(u8 id,u8 acction,u8 time)
//{
//		gstHeat.id = id;
//    gstHeat.action = acction;
//    gstHeat.time = time;
//    if(HeatProcess() == 1)
//    {
//        ////设备id 不对
//    }
//}

/************************************************************************************************************************************************
 * 描述：设置工作温度等级  
 * 参数：
 *       TempLevel 温度等级，0表示关闭功能
 * 返回：无
 * 注意：无
*************************************************************************************************************************************************/
void  SetLHeatLevel(HeatUnit_t HeatUnit,u8 level)
{       
    switch(HeatUnit)
    {
			
			case HEAT_ID_1 :
				sHeatLevel[0] = level;
				gstHeat.id = HEAT_ID;
			break;
				
			case HEAT_ID:
         sHeatLevel[1] = level;
				 gstHeat.id = HEAT_ID_1;
      break;
		
			case HEAT_ALL_Unit:
				sHeatLevel[0] = level;
				sHeatLevel[1] = level;
			break;

        default:          
        break;

    }
}
/************************************************************************************************************************************************
 * 描述：设置加热的工作模式
 * 参数：选择加热单元
 * 返回：无
 * 注意：无
*************************************************************************************************************************************************/
void SetHeatUnit(u8 v)
{
	gstHeat.CurMode = v;
}

/************************************************************************************************************************************************
 * 描述：获取加热的工作模式
 * 参数：無
 * 返回：（1，or 2 or 3路加热）
 * 注意：无
*************************************************************************************************************************************************/
u8 GetHeatUnit(void)
{
	return gstHeat.CurMode ;
}


/************************************************************************************************************************************************
 * 描述：设置加热的工作模式
 * 参数：無
 * 返回：
 * 注意：无
*************************************************************************************************************************************************/
void HeatModeSwitch(void)
{
	if(gstHeat.CurMode == 0)
	{
		gstHeat.CurMode	 = 1;
	}
	else if(gstHeat.CurMode == 1)
	{
		gstHeat.CurMode	 = 2;	
	}
	else
	{
		gstHeat.CurMode = 0;
	}
}

/************************************************************************************************************************************************
 * 描述：返回工作温度等级  
 * 参数：無
 * 返回：
 * 注意：无
*************************************************************************************************************************************************/
u8 getHeatLevel(void)
{
	if(gstHeat.CurMode == 0)
	{
		return sHeatLevel[0];
	}

	else if(gstHeat.CurMode == 1)
	{
		return sHeatLevel[1];
	}
		
	else 
	{
		return sHeatLevel[0];	
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	HeatProcess,周期性处理加热函数
* 功能说明:	无传感器反馈的普通加热,此函数用于无温度传感器的加热
* 输    入: 对象，加热动作	，加热时间
* 输    出: 无

******************************************************************************************************************************************/
u8 HeatProcess(u8 id_v)
{		
	u8 id =  id_v;	
	
	switch(id)
	{
		case HEAT_ID:
			
		if(HaveNTCFlag)
			return 2;//没有NTC
				
		if(sHeatLevel[0] >3)
		{
			gstHeat.action  = AccompanyFunc_OnOffHandle1(&gHeatTime,2,HeatOnOffTimeTab);
		}
		else
		{
			gstHeat.action  =OFF;
		}
		
		if(gstHeat.action == ON)
		{
			HEAT_io =  1;
		}
		else
		{
			HEAT_io =  0;//HEAT_io =  0;
		}
		break;
		
		case HEAT_ID_1:
		
		if(HaveNTCFlag_1)
			return 2;//没有NTC
			
		if(sHeatLevel[1] >3)
		{
			gstHeat.action  = AccompanyFunc_OnOffHandle1(&gHeatTime,2,HeatOnOffTimeTab);
		}
		else
		{
			gstHeat.action  =OFF;
		}
		if(gstHeat.action == ON)
		{
			HEAT_io_1 =  1;
		}
		else
		{
			HEAT_io_1 =  0;//HEAT_io =  0;
		}
		break;
		
		default:
			break;
	}	
   return 0;
}

void HeatHandle(void)
{
//	if(!SysRunFlag)
//		return;
	
	HeatProcess(HEAT_ID);
	HeatProcess(HEAT_ID_1);
}

#endif