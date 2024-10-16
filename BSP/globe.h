#ifndef GLOBLE_H
#define GLOBLE_H

#include "includeall.h"

/*
////LI GONG SDK
#include "device_registers.h"          
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
*/

#include "config.h"


//#define  TAB_ISUM(tab)              (sizeof(tab)/sizeof(tab[0]))

#define Byte8	byte
#define u8	unsigned char
#define u16	unsigned short
#define Uchar	unsigned char
#define u32	unsigned long
#define EVENT_BUFFER_LENGTH  3

typedef union
{
	u8 all;
	struct
	{
		u8	time  :5;
		u8	Cnt		:3;	
	}Bit;
}ST_Heat;

typedef union
{
	u8 all;
	struct
	{
	u8	ppc :2;
	u8	C		:2;	
	u8	RO 	:2;
	u8	Water :1;
	u8	wifi 	:1;
	}Bit;
}uLED_Dliaplay;

typedef enum
{
    AD_ntc,
		AD_ntc_1,
    ADMax ,
}BSP_ADChangeEnum;

typedef enum
{
	OFF,
	ON,
	RedColor ,
	BlueColor,
	MixColor,
	LED_close,
	LED_ID,
	PowerLed_ON,
	PowerLed_OFF,
	time_ingore = 255
	
}emColor;

typedef enum
{
	HEAT_ALL_Unit,
	HEAT_ID,
	HEAT_ID_1,		
}emHeat;

typedef enum
{
	 lightOn,//��
	 lightOff,//��
	 blink
}U_LED;


typedef struct
{
	 u8 dis1  ;
	 u8 dis2  ;
}STDisplayCode;





typedef struct 
{
	u8  FaultCnt;
    u8  ErrorCodeDisplayData;  
    u8  ErrorToNomalCnt;
    u8  ErrorCodeData;
    u8  YSJErrowCnt;    
    u8  LowLevelTimeCnt;
    u8  HighLevelTimeCnt;
    u16 ErrowCnt;
}ST_MakeWater;
	
typedef struct 
{
    u8 WriteEventCount;
    u8 ReadEventCount;
}ST_PushPop;

 typedef  union
 {
		u16 all;
		struct
		{
			u8 sProsessTime :6;
//			u8 hisKey  		 :6;
			u8 gNoKeyTime  :8;
		}Bit;
 }STKeyType;
 


typedef struct    
{
		u16 RunTimeCur;
		u16 RunTimeMax;
    u8 step			;
    u8 sFactoryTime	;
    u8 FactoryCnt	;
		
	u8 step1			;
}STFactory;

typedef struct 
{
  u8 DisplayMode;
	signed char CompensationValue;
}STSetVaue;

typedef struct 
{
		u8 PowerOnTimer;
		u8 RecoverTimer;//u8 Run;
		union
		{
			struct
			{
				u8 RunFlag 			:1;
				u8 DisplayModeFlag 	:1;
				u8 DisplayValueFlag :1;
			}Bit;
			u8         All;
		}Run;
		
		u8 mode;
		u8 value;
		
}STSetTempCompensation;

typedef struct
{
    u8  KeyNum;
    u8  Value;
}STLingMin;




typedef union
{
	u8	all;
	struct
	{
		u8 cnt1   :6;
		u8 cnt2		:2;
	}Bit;
}STLightByte;

typedef union
{
	u8	all;
	struct
	{
		u8 His         :1;
		u8 cnt			:7;
        
	}Bit;
}ST_Beep;

typedef union
{
	u16	all;
	struct
	{
		u8 Step_AD    :2;
		u8 sStep		  :2;
		u8 Step_1		  :1;
		u8 Step_2		  :1;
    u8 Step		  	:4;    
	}Bit;
}ST_Step;

/////////////////////////
 typedef union
{
	u8	all;
	struct
	{
		u8 b0	:1;
		u8 b1	:1;
		u8 b2	:1;
		u8 b3	:1;
		u8 b4	:1;
		u8 b5	:1;
		u8 b6	:1;
		u8 b7	:1;
	}Bit;
}byte;

 typedef union
{
	unsigned long	all;
	struct
	{
		u8 b0	:1;
		u8 b1	:1;
		u8 b2	:1;
		u8 b3	:1;
		u8 b4	:1;
		
		u8 b5	:1;
		u8 b6	:1;
		u8 b7	:1;		
		u8 b8		:1;
		u8 b9		:1;
		
		u8 b10	:1;
		u8 b11	:1;
		u8 b12	:1;
		u8 b13	:1;
		u8 b14	:1;
		
		u8 b15	:1;		
		u8 b16	:1;
		u8 b17	:1;
		u8 b18	:1;
		u8 b19	:1;
		
		///////////////////////////		
		u8 b20	:1;
		u8 b21	:1;
		u8 b22	:1;
///////////////////////////		
		u8 b23	:1;		
		u8 b24	:1;
///////////////////////////		
		u8 b25	:1;
		u8 b26	:1;
		u8 b27	:1;
///////////////////////////		
		
	u8 b28	:1;
		u8 b29	:1;	
		
		u8 step	:3;
		
	}Bit;
}byte32;


typedef enum
{
    BSP_USART0,               
    BSP_USART1,               
    BSP_USART2,               
    BSP_USART3,               
    BSP_UART_MAX = BSP_USART3
}BSP_UART_Port_t;


typedef struct
{
  u8 tickCnt1;  
	u8 tickCnt2;
	u8 tickCnt3;
}sysTick_t;

//////////////��С���////////////////////
extern xdata ST_PushPop gstPushPop;
extern xdata u16 gSysRunTime;
extern xdata u8  gSetSysRunTime;
extern xdata volatile byte	gbFlagData[];
extern xdata volatile sysTick_t gstRDsysTick;
extern xdata Uchar gEventBuffer[EVENT_BUFFER_LENGTH];
extern xdata STFactory gstFactory;
//////////////��С���////////////////////
extern xdata volatile unsigned long gKeyValue;
extern xdata byte gSendData[];

extern xdata u8 gHeatTime;
extern xdata ST_Step gStep ;
extern xdata STKeyType sKey_yyy ;
#if  NTC_CONFIG
extern xdata volatile u8 sTemp_v,sTemp_v_1;
#endif





#define  RDSystickProcess()\ 
	gstRDsysTick.tickCnt2++;\
	gstRDsysTick.tickCnt3++;\
	if(0 == gstRDsysTick.tickCnt2%79){Ev20MSFlag = 1;}\
	if(0 == gstRDsysTick.tickCnt2%200){Ev50MSFlag = 1;gstRDsysTick.tickCnt2  = 0;gstRDsysTick.tickCnt1++;\
	if(0 == (gstRDsysTick.tickCnt1)%4)Ev100MSFlag = 1;\
	if(0 == (gstRDsysTick.tickCnt1)%40){Ev1SFlag = 1;gstRDsysTick.tickCnt1 = 0;}}\	
	if(0 == (gstRDsysTick.tickCnt3)%20){Ev5MSFlag = 1;gstRDsysTick.tickCnt3 = 0;}\
	//LED_Scan();
	
#define LED_0N 0
#define LED_0FF 1	
	
#define  SCUCESS        1
#define  FAIL           0

#define TDS_100 100
#define TDS_300 300
#define TDS_500 500
#define TDS_1000 1000

//#define TDS_Tab_Num  (sizeof(gstJiaoZhun)/sizeof(ST_TDS_JiaoZhun))

#define KEY1_MASK 0x01
#define KEY2_MASK 0x02
#define KEY3_MASK 0x04
#define KEY4_MASK 0x08
#define KEY5_MASK 0x10
#define KEY6_MASK 0x20
#define KEY7_MASK 0x40
#define KEY8_MASK 0x80



#define  _150MS_Per5MS     30
#define  _100MS_Per5MS     20

#define  _100MS_Per20MS    5
#define  _120MS_Per20MS    6
#define  _140MS_Per20MS    7
#define  _200MS_Per20MS    10
#define  _220MS_Per20MS    11
#define  _240MS_Per20MS    12
#define  _260MS_Per20MS    13
#define  _280MS_Per20MS    14
#define  _3S_Per20MS      50*3
#define  _4S_Per20MS      50*4

#define  _500MS_Per50MS  	9
#define  _10S_Per50MS  		200//20*10
#define  _5S_Per50MS   		100//20*5
#define  _3S_Per50MS   		20*3
#define  _2S_Per50MS   		20*2
#define  _1S_Per50MS   		20
#define  _30S_Per50MS  		20*30
#define  _1Min_Per50MS   	20*60
#define  _5Min_Per50MS   	20*300
#define  _20Min_Per50MS   20*1200


#define  _90Min_Per100MS      10*60*90
#define  _15Min_Per100MS      10*60*15
#define  _3S400MS_Per100MS         34
#define  _2S_Per100MS         20
#define  _4S_Per100MS         40
#define  AllTheTime         	0xff

#define  _15S_Per100MS        10*15
#define  _30S_Per100MS        10*30
#define  _3Min_Per100MS       10*60*3
#define  _13Min_Per100MS      10*60*13
#define  _20Min_Per100MS      10*60*20
#define  _30Min_Per100MS      10*60*30
#define  _40Min_Per100MS      10*60*40

#define  _200MS_Per100MS   	2
#define  _500MS_Per100MS   	5
#define  _1S_Per100MS   		10*1
#define  _10S_Per100MS    	50
#define  _20S_Per100MS   		100
#define  _25S_Per100MS  		10*20

#define  _8h_Per1S      3600*8
#define  _30Min_Per1S   60*30
#define  _60Min_Per1S   120*30
#define  _15Min_Per1S   60*15
#define  _20Min_Per1S   60*20
#define  _5Min_Per1S	60*5
#define  _2Min_Per1S	60*2
#define  _4Min_Per1S	60*4
#define  _1Min_Per1S	60*1
#define  _10S_Per1S	    10

#define  _35S_Per1S			35
#define  _50S_Per1S			50
#define  _3Min_Per1S		60*3
#define  _9Min_Per1S		60*9
#define  _8Min_Per1S		60*8
#define  _4Min_Per1S		60*4
#define  _0Min_Per1S		0
#endif
