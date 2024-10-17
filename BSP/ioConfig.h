
#ifndef IO_CONFIG_H
#define IO_CONFIG_H


#include "cms8s6990.H"
#include "ADC.h"




extern void  _nop_      (void);

#define NOP 			_nop_
#define Chanel_IO1 P33
#define Chanel_IO2 P35//


#define	Port_STB	P0_4
#define	Port_CLK	P0_3
#define	Port_DIO	P0_2

#define Redled_io     P3_1
#define Blueled_io    P3_1
#define HEAT_io        P0_1  
#define HEAT_io_1      P0_0 
#define HEAT_LED_io   P3_1//P12
#define Phykey_io     P2_5//P25// 8364 用的是P25引脚  
#define ADC_io  	  //P42

#define L1_io P0_0
#define L2_io P0_1
#define L3_io P0_2
#define L4_io P0_3
#define L5_io P0_4
#define L6_io P0_6
#define L7_io P0_7
#define L8_io P2_1

#define P_AiP4952_CLK  P0_5
#define P_AiP4952_SDA  P2_0
#define P_AiP4952_CS   P2_4

#define SDA_Input    	P2_DM2 |=0x01;P2_DM0&=~0x01
#define SDA_Output   	P2_DM0 |=0x01;P2_DM2&=~0x01

#define  IE_Enable    IE_EA = 1
#define  IE_Disable   IE_EA = 0
