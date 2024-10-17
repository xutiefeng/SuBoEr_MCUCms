#include "PWM.h"
#include "buzzer.h"

#define _100ms_Per5ms 20
#define _30ms_Per5ms  2
#define BUZZER_0N  1
#define BUZZER_0FF 0
#define uint8_t unsigned char
#define uint16_t unsigned short int
#define uint32_t unsigned long  int
#define BUZZER_POWER_ON   	 PWM_CON |= 0x80//P25 = 1;PWM_CmdEX(PWM3_Type,ENABLE)//PWM_CmdEX(PWM0_Type,ENABLE)//PINS_DRV_WritePin(PTD,16,1)
#define BUZZER_POWER_OFF  	 PWM_CON &= 0x7F//P25 = 0//PWM_IndependentModeConfig(PWM02,0);;//PINS_DRV_WritePin(PTD,16,0)
#define BUEEER_SetFrq(X)  	 PWM_Set(3,X)//PWM_Init(PWM3_PRESSEL_FHRC_D1,X*2)//((FTM0)->MOD) = ((((FTM0)->MOD) & ~(0xFFFFu)) | (40000000/X));((FTM0)->SYNC) = ((((FTM0)->SYNC) & ~(0x80)) | (0x80))
#define BUEEER_SetDuty(X)    //PWM_IndependentModeConfig(PWM30,X);//(FTM0)->CONTROLS[0].CnV = 0xF55;										((FTM0)->SYNC) = ((((FTM0)->SYNC) & ~(0x80)) | (0x80))
#define BUZZER_Stop   	     //PWM_CmdEX(PWM3_Type,DISABLE)
//#define BUEEER_SetDuty_OFF()    ;//(FTM0)->CONTROLS[0].CnV = 0x2000;										((FTM0)->SYNC) = ((((FTM0)->SYNC) & ~(0x80)) | (0x80))



typedef struct
{
    uint16_t frq;
    uint8_t OnTime;
    uint8_t OffTime;
}ST_Buzzer;

typedef struct
{
    uint16_t OpenTime;
    uint16_t CloseTime;
    uint8_t   step;
}ST_BuzzerCanShu;

#define Buzzer0N_SingalKey 3300
#define Buzzer0N_6sheng 3700
#define Buzzer0N_3sheng 3400

#define Buzzer0FF_TIME_Per1s  620
#define Buzzer0n_TIME_Per1s    380

#define Buzzer0FF_TIME_Per500Ms  380
#define Buzzer0n_TIME_Per500Ms    120

#define Buzzer0FF_TIME  880
#define Buzzer0n_TIME   120

code ST_Buzzer stBuzzerTab[] =
{
//	  {2400    ,200,120},
//		{2700    ,200,120},
		{2900    ,40,50},
//		{3400    ,200,1200},
    {0xffff  ,0xff,0xff}               
};

uint8_t  BuzzerStart(ST_Buzzer  *stBuzzerTab)
{
	  static xdata uint8_t sBuzzerTime_on = 0;
	  static xdata uint8_t sBuzzerTime_off = 0;
		static xdata uint8_t step =0;

		
		if(sBuzzerTime_on == 0 )
		{
				BUEEER_SetFrq(stBuzzerTab[step].frq);	
				sBuzzerTime_on++;
		}
		
    else if(sBuzzerTime_on < stBuzzerTab[step].OnTime )
    {
			  BUZZER_POWER_ON; 	
				sBuzzerTime_on++;
    }
		
	else if(sBuzzerTime_off < stBuzzerTab[step].OffTime )
    {
			  BUZZER_POWER_OFF; sBuzzerTime_off++;
    }
    else 
    {		
				step++;
				sBuzzerTime_off = 0;
				sBuzzerTime_on = 0;
				
				if(stBuzzerTab[step].frq == 0xffff)
				{
						step = 0;
						return 0;//蜂鸣器 执行周期结束
				}
    }  
    return 1;
}

void BuzzerProcess(void)
{      
	if(BuzzerFlag)
	{
			if(BuzzerStart(stBuzzerTab) == 0)//voliceNum = 3;
			{
					BuzzerFlag = 0;
			}
	}    
}
