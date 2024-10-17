
#include "includeall.h"

//////////////////////////////////////


xdata ST_PushPop gstPushPop;
xdata volatile byte	gbFlagData[3];
xdata volatile sysTick_t gstRDsysTick;
xdata Uchar gEventBuffer[EVENT_BUFFER_LENGTH];
xdata u16 gSysRunTime;
xdata u8  gSetSysRunTime =8;
xdata ST_Step gStep ;
xdata STFactory gstFactory;
 
#if  HEAT_CONFIG
xdata u8 gHeatTime ;
#endif


#if  NTC_CONFIG
xdata volatile u8 sTemp_v,sTemp_v_1;
#endif

#if  Bsp_Phykey_CONFIG
xdata STKeyType sKey_yyy ;
#endif
