
#include  "bsp_ADCollect.h"



#define AD_TO_SELECT_TOP  {}//sADcnt= 0; 


#define ADCHANAL_GetValue()   ((ADC_RESH<<4) | ADC_RESL);ADC_CR0 |= 0x10//ADC_GetConversionValue()
#define ADCHANAL_Select(X)    ADC_CHSEL = X//ADC_ChannelConfig(ADC_CHANNEL_##X,ENABLE);
#define AD_Conversion()					ADC_CR0 |= 0x20 			//ADC_StartConversion()//ADC0_ChannelSelect(ADC_POSINPUT_AIN##X,ADC_NEGINPUT_AIN##X); 
	
	
#define AD_COLLECT_ENABLE  {}//ADC0_Enable() 
#define AD_COLLECT_DIASBLE {}//ADC0_Disable()	
	

xdata u16 AD_ChanalTab[ADMax];
	
unsigned int adc_get_average(u16 *p)            
{
  xdata unsigned int adc_value_max = 0;
  xdata unsigned int adc_value_min = 0xffff;
  xdata unsigned int adc_sum = 0;
  xdata unsigned int adc_current = 0;
  xdata unsigned char i;
  
  for(i = 0;i<10;i++)
  {
    adc_current = p[i];
    if(adc_current > adc_value_max)
    {
      adc_value_max = adc_current;
    }
    if(adc_current < adc_value_min)
    {
      adc_value_min = adc_current;
    }
    adc_sum = adc_sum + adc_current;
  }
  
  adc_sum = adc_sum - adc_value_min;
  adc_sum = adc_sum - adc_value_max;
  adc_sum = adc_sum>>3;
  return adc_sum;
}
/************************************************************************* 
* ????:	sysRuning
* ????:	(gAD_Value[0]/4096)*5.2*10 = 52/4096 = 0.0126953125
* ????:	
* ?    ?: ?	
* ?    ?: ?
*************************************************************************/


#define ADAverage_CH_Num ADMax

xdata  STAD_Collect gstAD;


void ADCollect(void)
{
	switch(gstAD.Run.Bit.step)
	{
		case 0:		
				AD_ChanalTab[AD_ntc] = ADCHANAL_GetValue();			 			
				gstAD.Run.Bit.step++;
				ADCHANAL_Select(1);
				AD_Conversion();
		
		break;	
		
		case 1:
				 AD_ChanalTab[AD_ntc_1] =  ADCHANAL_GetValue();	
				 gstAD.Run.Bit.step++;
				 ADCHANAL_Select(0);
		break;

		default:
			break;
	}
	
}



void ADCollectProcess(void)
{	
	static xdata u8 sADLostCnt =0;		
	gstAD.ADTab[gstAD.Run.Bit.cnt]   = AD_ChanalTab[AD_ntc];		
	gstAD.ADTab_1[gstAD.Run.Bit.cnt] = AD_ChanalTab[AD_ntc_1];		
	if(gstAD.Run.Bit.step >= ADMax)
	{

		 gstAD.Run.Bit.cnt++;

		 if(gstAD.Run.Bit.cnt == 10)
		 {
			gstAD.avergeValue[AD_ntc] =  adc_get_average(gstAD.ADTab);
			gstAD.avergeValue[AD_ntc_1] = adc_get_average(gstAD.ADTab_1);
			gstAD.Run.Bit.cnt = 0;
		 }
		 AD_Conversion();
		 gstAD.Run.Bit.step = 0;
		 sADLostCnt =0;
	}	
	else
	{
		sADLostCnt++;
		if(sADLostCnt > 2)
			AD_Conversion();
	}	
}

u16 Get_ADValue(u8 num)
{		
	return gstAD.avergeValue[num];
}




