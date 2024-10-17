#include "clib.h"

#define DIS_INTRUPT     {}//NVIC_INT_Enable()
#define EN_INTRUPT      {}//NVIC_INT_Disable()

void PushEvent(Uchar event)
{	
	Uchar temp;

	if(gstPushPop.WriteEventCount >= EVENT_BUFFER_LENGTH)
	{
		gstPushPop.WriteEventCount = 0;
	}
	for(temp = 0; temp <= gstPushPop.WriteEventCount; temp++)
	{
		if(event == gEventBuffer[temp] /*&& event != ev20MS && event != ev50MS && event != ev100MS && event != ev1S && event != ev5MS*/)
		{
			return;
		}
	}
	gEventBuffer[gstPushPop.WriteEventCount] = event;
	gstPushPop.WriteEventCount++;	
}

Uchar PopEvent(void)
{
    Uchar event;
    DIS_INTRUPT;
    if(gstPushPop.ReadEventCount >= EVENT_BUFFER_LENGTH)
    {
        gstPushPop.ReadEventCount = 0;
        event = gEventBuffer[gstPushPop.ReadEventCount];
    }
		else
		{	
			if(gstPushPop.ReadEventCount >= gstPushPop.WriteEventCount)
			{	
				gstPushPop.ReadEventCount = 0;
				gstPushPop.WriteEventCount = 0;

				event = 0xff;
			}
			else
			{
				event = gEventBuffer[gstPushPop.ReadEventCount];
				gEventBuffer[gstPushPop.ReadEventCount] = 0xff;
				gstPushPop.ReadEventCount++;
			}
		}
	EN_INTRUPT;
    
	return (event);
}
/************************************************************************************************************************************************
 * 描述：向串口注册字节接收回调函数       
 * 参数：UARTPort      -- 串口
				 evt					 --信号量
 *       pRxByteCBFunc -- 要注册的回调函数。    
 * 返回：无
 * 注意：无
*************************************************************************************************************************************************/

void EventCollect(void) 
{

	if(KeyRestFlag)
	{
		KeyRestFlag = 0;
		PushEvent(evSysRest);
	}
	
	else if(Ev5MSFlag)
	{
		Ev5MSFlag = 0;
		PushEvent(ev5MS);
	}
	else if(Ev20MSFlag)
	{
		Ev20MSFlag = 0;
		PushEvent(ev20MS);
	}
	else if(Ev50MSFlag)
	{
		Ev50MSFlag = 0;
		PushEvent(ev50MS);
	}
	else if(Ev100MSFlag)//Ev5MSFlag
	{
		Ev100MSFlag = 0;
		PushEvent(ev100MS);
	}
	
	else if(Ev1SFlag)//Ev5MSFlag
	{
		Ev1SFlag = 0;
		PushEvent(ev1S);
	}
	else
	{
	
	}

}
