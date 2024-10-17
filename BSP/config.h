#ifndef CONGIG_H
#define CONGIG_H

#include  "..\bsp\globe.h"

#define  LED_CONFIG  1
#define  HEAT_CONFIG 0
#define  Bsp_Phykey_CONFIG 1
#define  NTC_CONFIG 0
#define  AiP4952A_SPI  1
#define  AiP4952_Apply 1
#define  CONFIG_DIAPLAY 1
typedef enum
{
    evReceivecmp = 0,
    evReceiveBMS,
    evReceiveDisplay,
    evReceiveZhuoDu,
    evSysRest = 10,
    evNoKeyProcess,
    evKeyPower,
    evCleanMode,
    evVoiceSwitch,
    evKeyLackWater,
    evAuto,
    evAuto3,
    evAD,
		ev3MS,
    ev5MS,
    ev20MS,
    ev50MS ,
    ev100MS,
    ev1S,
	  evPowerDown
}Evnt_t;



#define  Ev100MSFlag                            gbFlagData[0].Bit.b0 
#define  JieDianDisplayFlag                     gbFlagData[0].Bit.b1
#define  Ev50MSFlag                             gbFlagData[0].Bit.b2 
#define  Ev1SFlag                               gbFlagData[0].Bit.b3 
#define  Ev5MSFlag                              gbFlagData[0].Bit.b4
#define  Ev20MSFlag                              gbFlagData[0].Bit.b5
 

#define  SysRunFlag   												gbFlagData[1].Bit.b0
#define  DaiJiDispalyFlag   									gbFlagData[1].Bit.b1
#define  SysDelayFlag												  gbFlagData[1].Bit.b2
#define  YellowLedFlag                        gbFlagData[1].Bit.b3 
#define  ADCollectFlag                        gbFlagData[1].Bit.b4 
#define  KeyRestFlag													gbFlagData[1].Bit.b5
#define  CheckFinishFlag											gbFlagData[1].Bit.b6


#define  BuzzerFlag															gbFlagData[2].Bit.b0
#define  HaveNTCFlag_1													gbFlagData[2].Bit.b1
#define  HaveNTCFlag														gbFlagData[2].Bit.b2
#define  Auto1Flag                              gbFlagData[2].Bit.b5
#define  Auto2Flag                              gbFlagData[2].Bit.b6
#define  Auto3Flag                              gbFlagData[2].Bit.b7

#define   C_RX_MODE         	1		
#define   C_TX_MODE         	0

#endif
