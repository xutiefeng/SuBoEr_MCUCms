

#include "bsp_uart.h"

volatile char  TxLen ;

#define		HEAD_CODE_NORMAL					0x03	
#define		HEAD_CODE_EVENT						0x06	
#define		ZHUKONGBAN_ADDR						0X01
#define		RX_Len                              0X05

//uint8_t     SCICheckout;                             
//uint8_t     RxLen; 

#define ReceiveRestart()	 RxLen = 0, SCICheckout  = 0
#define RECEIVE_CONTROLLER_DATA_LENGTH 2


ST_UartSendBuf gstUartSendBuf =
{
0xA3,
01,
0,
0,
0,
0,
0,
0,
0,
0,
	
0,
0,
0,
0,
	
0,
0,
0,
0,
	
0
	
};

void SendArryData(u8 * addr,u8 len)
{	
		char i,sum;
		char *p =(u8 *)&gstUartSendBuf;
		unsigned long *pto = gstUartSendBuf.dat;
		for (i=2; i< len;i++)
		{
			p[i] = addr[i-2];
		}
		 sum= 0;
		for (i=0; i< Tx_Data_len-1;i++)
	    {
				sum+=p[i];
		}
		p[Tx_Data_len-1] =sum;
}

void SendWordData(unsigned long dat)
{	
		char i,sum;
		char *p =(u8 *)&gstUartSendBuf;
		unsigned long *pto = gstUartSendBuf.dat;
		*pto = dat;
		 sum= 0;
		for (i=0; i< Tx_Data_len-1;i++)
	    {
				sum+=p[i];
		}
		p[Tx_Data_len-1] =sum;
}



const	unsigned	char  code	display_tab[]=  		  					   
{
	0x3f,//0
	0x06,//1
	0x5b,//2
	0x4f,//3	
	0x66,//4 
	0x6d,//5
	0x7d,//6
	0x07,//7
	0x7f, //8
	0x6f,//9
	0x77,//a
	0x7c,	//b	
	0x39,//c 
	0x5e,//d
	0x79, //e
	0x71,	//F
};
/*
此函数
*/



void display_value(u16 v,u8 type)
{
		switch(type)
		{
			case 0:
				gSendData[2].all = (v>>8)&0x0f;
				gSendData[2].all = display_tab[gSendData[2].all];
			
				gSendData[3].all = (v>>4)&0x0f;
				gSendData[3].all = display_tab[gSendData[3].all];
			
				gSendData[4].all = v&0x0f;
				gSendData[4].all = display_tab[gSendData[4].all];
			break;
			
			case 1:
				
				if(v > 999)
					v= 999;
				
				gSendData[2].all = v/100;	
				gSendData[2].all = display_tab[gSendData[2].all];
				gSendData[3].all = (v/10)%10;
				gSendData[3].all = display_tab[gSendData[3].all];
				gSendData[4].all = v%10;
				gSendData[4].all = display_tab[gSendData[4].all];
			break;
			
			default:
				break;
		
		}
}








u8 TDS_ZhiShi_display(void)
{
	static u8 sFactoryModeCnt =0;
	uLED_Dliaplay Udata;
	Udata.all =0;
	if(FactoryModeFlag || FstModeFlag)
	{
			if(sFactoryModeCnt++ >_20S_Per100MS )
			{
					sFactoryModeCnt = 0;
					
			}
			if(sFactoryModeCnt < _10S_Per100MS)
			{
					if(DisplayJieShuiFlag)
					{
						display_value(gstADCollect.fJieShui,0);//display_value(gstADCollect.fYuanShui,0);
					}
					else if(DisplayYuanShuiFlag )
					{
							display_value(gstADCollect.fYuanShui,0);//display_value(gstADCollect.fJieShui,0);
					}
					else if(DisplayLouShuiFlag)
					{
							display_value(gstADCollect.fLouShui,0);
					}
					else
					{
							display_value(gstADCollect.fChunShui,0);
					}
					
					Udata.Bit.Water =1;
			}
			else
			{
					
				  if(DisplayJieShuiFlag)
					{
						 display_value(gstADCollect.tds_JieShui,1);
					}
					else if(DisplayYuanShuiFlag )
					{
						 display_value(gstADCollect.tds_YuanShui,1);
					}
					else if(DisplayLouShuiFlag)
					{
							display_value(gstADCollect.tds_LouShui,1); 
					}
					else
					{
							display_value(gstADCollect.tds_ChunShui,1);
					}
					Udata.Bit.Water = 0;
			}
	}
	else
	{
			display_value(gstADCollect.tds_ChunShui,1);
			
	}	
	
		 if(LED2_L)
		 {			
				Udata.Bit.RO = 1;
		 }
		 else if(LED2_R)
		 {
				Udata.Bit.RO = 2;
		 }
		 else
	 	 {
			  Udata.Bit.RO = 0;
		 }

	  
		 if(LED1_L)
		 {				
				 Udata.Bit.ppc = 1;
		 }
		 else if(LED1_R)
	   {
			  Udata.Bit.ppc = 2;
		 }
		 else
		 {
				Udata.Bit.ppc = 0;
		 }
	
	return Udata.all;
		
	 	
}

void  ZhiShiDengdisplay2(void)//龙头指示灯2
{
		
}

//void    UART0_SendData( void)
//{
//		u8 i;
//		
//		
//	  gSendData[0].all = 0xA5;
//		gSendData[1].all = 8;
//	  
//	  gSendData[5].all  = TDS_ZhiShi_display();
//		//gSendData[6].Bit.b0 = ShuiLongTouOpen;
//	
//		
//	
//	  if(FactoryModeFlag || FstModeFlag)
//		{
//				gSendData[6].Bit.b1 = gSendData[5].Bit.b6;
//		}
//		else
//		{
//				gSendData[6].Bit.b1 = KeySwitchFlag;//chun shui
//		}
//		
//	 	gSendData[7].all = 0;
//		for(i = 0;i<7;i++)
//		{
//				gSendData[7].all +=gSendData[i].all;
//		}
//		
//		SBUF = 0xA5;
//}






u8    RDUART0_RcvByte(unsigned char dat, unsigned char *addr)
{
			    u8 i;
			    static unsigned char RxLen;
			    static unsigned char SCICheckout;
			    static char rx[Rx_Data_len]; 

				if(RxLen >= Rx_Data_len)
					RxLen =0;
			
				if(RxLen == 0)
				{
					if((dat == 0xA3) )
					{
						rx[0] = dat;
						SCICheckout += dat;
						RxLen++;
					}
				}
				
				else if(RxLen == 1)
				{
					if(dat == 1 || dat == 2 || dat == 3)
					{
						
						rx[1]= dat;
						SCICheckout += dat;
						RxLen++;
					}
					else
					{
						 ReceiveRestart();
					}
				}
				else if(RxLen == (Rx_Data_len-1))
				{
					#if 1 // test ping bi 
 					if(dat ==  SCICheckout)
					{ 					
							for(i=2; i< Rx_Data_len-1 ;i++)
						  {
									addr[i-2] = rx[i];
							}
							
							ReceiveRestart();
					}						
					else
					{						
						 ReceiveRestart();
					}
					#else
							for(i=2; i< Rx_Data_len-1 ;i++)
						  {
									addr[i-2] = rx[i];
							}
							ReceiveRestart();
					#endif
				}
				
				else if(RxLen < Rx_Data_len-1)
				{

					rx[RxLen] = dat;
					RxLen++;
					SCICheckout += dat;
				}
				else
				{
						ReceiveRestart();
				}
				
				return SCICheckout;//RxLen;
}

