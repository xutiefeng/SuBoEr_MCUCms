#ifndef FUNCTAB_H
#define FUNCTAB_H

#include "globe.h"
extern code u16 TempTab[];
extern code u8   LEDOnOffTimeTab[][2];
extern code u8   HeatOnOffTimeTab[][2];
extern code u8   LED_BinkTimeTab[][2];
extern code u8   DefaultTempTab[];
extern code u8   DefaultTimerTab[];
#define   DefaultTempMIN_Value   DefaultTempTab[0]
#define   DefaultTempMAX_Value   DefaultTempTab[1]


#define LONG_TO_BIN(n)                       \
                     (                       \
                       ((n >> 21) & 0x80) |  \
                       ((n >> 18) & 0x40) |  \
                       ((n >> 15) & 0x20) |  \
                       ((n >> 12) & 0x10) |  \
                       ((n >> 9)  & 0x08) |  \
                       ((n >> 6)  & 0x04) |  \
                       ((n >> 3)  & 0x02) |  \
                       ((n )      & 0x01)    \
                     )

#define BIN(n) LONG_TO_BIN(0x##n##l)
#define B(n)   BIN(n)
#define b(n)   BIN(n)

#define  TAB_ISUM(x)              (sizeof(x)/sizeof(x[0]))
	
u8  AccompanyFunc_OnOffHandle1( u8 *pOnOffTime, u8  level,const u8 OnOffTimeTab[][2]);
u8  searchInArray(u16 * array, u8 arrayLen, u16 num);	// 二分法查找 大头在前
u8 searchInArray_Temp(u16 * array, u8 arrayLen, u16 num);
#endif


