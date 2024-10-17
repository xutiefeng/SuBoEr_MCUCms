/* 
 * File:   bsp_uart.h
 * Author: lix
 *
 * Created on 2022?11?16?, ??3:45
 */

#ifndef BSP_UART_H
#define	BSP_UART_H


#include "globe.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define Rx_Data_len				 7//16+3
#define Tx_Data_len				 19//4+3
	
typedef struct
{
	u8 head;
	u8 addr;
	u8 dat[16];
	u8 check;
}ST_UartSendBuf;
u8    RDUART0_RcvByte(unsigned char dat, unsigned char *addr);
void BSP_UART_Init(void);	
void SendArryData(u8 * addr,u8 len);
extern volatile char  TxLen ;
extern ST_UartSendBuf gstUartSendBuf;

#define UART3_SendData(X,D) 	SendArryData(D,16);\
															X = 0xA3; 

#define ISR_UART0_TX(X,D) if(++TxLen < Tx_Data_len) X=D[TxLen];\
													else	TxLen =0

#ifdef	__cplusplus
}
#endif

#endif	/* BSP_UART_H */

