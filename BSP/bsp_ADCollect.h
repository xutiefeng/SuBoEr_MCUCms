/* 
 * File:   bsp_ADCollect.h
 * Author: lix
 *
 * Created on 2023年2月28日, 下午7:01
 */

#ifndef BSP_ADCOLLECT_H
#define	BSP_ADCOLLECT_H
#include "globe.h"



u16 Get_ADValue(u8 num);
	
typedef struct 
{
    u16   ADTab[10] ;
	u16   ADTab_1[10] ;
	u16   avergeValue[2];
    union
	{
			struct
			{
				u8  step:  2;
				u8  step1: 2;
				u8	cnt:   4;
			}Bit;
			u8         All;
	}Run;
	
}STAD_Collect;

typedef enum
{
	NTC_AD,
	KEY_AD
}enum_AD;
	
void ADCollect(void);
void ADCollectProcess(void);
u8 GetAD_Heat(void);
#endif	/* BSP_ADCOLLECT_H */

