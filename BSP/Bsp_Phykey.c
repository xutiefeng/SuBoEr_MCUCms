/*
 * @Author: xu_tie_feng xu_tie_feng@163.com
 * @Date: 2024-06-02 01:28:30
 * @LastEditors: xu_tie_feng xu_tie_feng@163.com
 * @LastEditTime: 2024-06-02 19:56:31
 * @FilePath: \LanYaDianReTan_8501\BSP\Bsp_Phykey.c
 * @Description: https://github.com/xu
 */
#include "Bsp_Phykey.h"

#define NO_KEY_PRESS_VALUE   0
#define COLEECT_KEY_VALUE(X) str_IO.In_Put
volatile TYP_IO	 str_IO;

extern void KeyShortPress(u8 v);
extern void KeyLongPress(u8 v);

/****************************************************************************************************************************************** 


******************************************************************************************************************************************/
void KeyProsess(u8 v)
{
	u8 KeyValue = v;
	
	if( (NO_KEY_PRESS_VALUE == KeyValue)  || SysDelayFlag )
	{
			sKey_yyy.Bit.sProsessTime = 0;
			if(sKey_yyy.Bit.gNoKeyTime > 0)
		  {
						sKey_yyy.Bit.gNoKeyTime--;								
		  }	
			else
			{
						SysDelayFlag = 0;
			}
	}
	else
	{
			  if(sKey_yyy.Bit.sProsessTime <0x3f)
					sKey_yyy.Bit.sProsessTime++;
				else
					return;
			

				if(sKey_yyy.Bit.sProsessTime >= _3S_Per50MS )//long press
				{					
							SysDelayFlag = 1;//qu dou	
							sKey_yyy.Bit.gNoKeyTime = _500MS_Per50MS;
							KeyLongPress(KeyValue);	  				
							sKey_yyy.Bit.sProsessTime = 0;
				}
				else
				{
							sKey_yyy.Bit.sProsessTime = 0x3f;
							KeyShortPress(KeyValue);
				}	
	}
}

void Kye_Scan(void)
{
	if(str_IO.State < 2)//
	{ 
			str_IO.In_Tmp[str_IO.State] = COLEECT_KEY_VALUE();
	}
	else
	{
		if((str_IO.In_Tmp[0] == str_IO.In_Tmp[1]))//
		{
		  str_IO.KeyValue = str_IO.In_Tmp[0];
			KeyProsess(str_IO.In_Tmp[0] );
		}
		str_IO.State = 0;
		return;
	}
	str_IO.State ++;
}

/****************************************************************************************************************************************** 


******************************************************************************************************************************************/


u8 getKeyValue(void)
{
		return	str_IO.KeyValue;
}




