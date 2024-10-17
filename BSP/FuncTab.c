#include "FuncTab.h"

code u8   DefaultTempTab[] = {36,50};

code u8   DefaultTimerTab[] = {2,8,12};


code u8   LED_BinkTimeTab[][2] =
{	
	{5,      10, },
};

code u8   LEDOnOffTimeTab[][2] = 
{
	{100,    200, },	
	{100,    200, },	
	{100,    200, },
};

code u8   HeatOnOffTimeTab[][2] = 
{
	/*kai, zhou_qi 	Unit 100ms*/
    {00,    30},//yi zhi guan
    {12,    30},//1dang： 1.2s kai  1.8S关
    {20,    30},//2dang： 2s kai  1关 
    {30,    30},//3dang：yi zhi kai
};



/************************************************************************************************************************************************
 * ??:?????????          
 * ??:
 *       Func            ??
 *       pOnOffTime      ????
 *       OnOffTimeTab    ??????                             
 * ??:ON     ???
 *       OFF    ???
 *       ??? ?????
 * ??:?   
*************************************************************************************************************************************************/
u8  AccompanyFunc_OnOffHandle1( u8 *pOnOffTime, u8  level,const u8 OnOffTimeTab[][2])
{
     u8 OnTime;
     u8 OffTime;
     u8  OnOff = OFF;
		 u8  *Value =pOnOffTime;

      OnTime  = OnOffTimeTab[level][0];
      OffTime =  OnOffTimeTab[level][1];
			(*Value)++;
      if(*Value< OnTime) 
      {
        OnOff = ON;
      }
      else if(*Value< OffTime)
      {
        OnOff = OFF;
      }
      else
      {
        *Value = 0;
      }
			
			return OnOff;
}

u8 searchInArray_Temp(u16 * array, u8 arrayLen, u16 num)
{
		u8 i;
	
		u8 *p = array;
		u8 len = arrayLen;
		i= 0;
		for(i= 0; i<arrayLen ; i++)
		{
				if(num < array[i])
					break;
		}
		return (i);
}

//u8  searchInArray(u16 * array, u8 arrayLen, u16 num)	// 二分法查找 小头在前
//{		
//	u8 xdata first, last, mid;
//	
//	u16* p=array;
//	u8   len = arrayLen;
//	if(num < p[0])	return 0;
//	else if(num > p[len - 1]) return len - 1; 
//	
//	first = 0;
//	last = arrayLen;
//	
//	while(last != first + 1)
//	{
//		mid = (first + last) >> 1;
//		if(num >= p[mid])
//		{
//			first = mid;
//			last = mid;
//			break;
//		}
//		else if(num < p[mid]) last = mid;	// 如果数值小于中间值 二分的后一个数等于中间值
//		else if(num > p[mid]) first = mid;
//	}
//	
//	if(num != p[last])
//	{
//		len = num-p[last];
//		mid = p[last+1]-num;
//		if(len > mid)
//			return (last+1);
//	}		
//	return last;
//}










