#include "AiP4952_Apply.h"

#define MAC_0  0x00
#define MAC_1  0x11
#define MAC_2  0x22
#define MAC_3  0x33
#define MAC_4  0x44
#define MAC_5  0x55
extern void AiP4952_RX_Data(void) ;	
extern xdata uint16 R_TX_Data_Cnt ;
extern void AiP4952_TX_Data(uint8 *TX_Number ,uint8 Len);

xdata uint8 ble_tx_buffer[48] = {0};
xdata uint8 buffer[64] = {0};
code	uint8	chLe[3] = { 37,38,39 };



xdata uint8	R_Check_Header[3] = {0};

uint8 invert_8(uint8 a)
{
	xdata uint8 temp = 0;
	
	if(a & 0x80)	temp |= 0x01;
		
	if(a & 0x40)	temp |= 0x02;
	
	if(a & 0x20)	temp |= 0x04;
		
	if(a & 0x10)	temp |= 0x08;
		
	if(a & 0x08)	temp |= 0x10;
		
	if(a & 0x04)	temp |= 0x20;
		
	if(a & 0x02)	temp |= 0x40;
		
	if(a & 0x01)	temp |= 0x80;

	return temp;
}



void bleCRC( uint8 *dat, uint8 len, uint8 *outputCRC)
{
	xdata uint8 v, t, d;

	while(len--)
	{
		d = *dat ++;
		for(v = 0; v < 8; v++, d >>= 1)  
		{
			t = outputCRC[0] >> 7;
			outputCRC[0] <<= 1;
			if(outputCRC[1] & 0x80)	outputCRC[0] |= 1;
				
				outputCRC[1] <<= 1;
			
			if(outputCRC[2] & 0x80)	outputCRC[1] |= 1;
				
				outputCRC[2] <<= 1;
			
			if(t != (d & 1))
			{
				outputCRC[2] ^= 0x5B;
				outputCRC[1] ^= 0x06;
			}
		}
	}
}




void bleWhiten(uint8 *dat, uint8 len, uint8 whitenCoeff)
{
 xdata	uint8 m;
	
	while(len--)
	{
		for(m = 1; m; m <<= 1)
		{
			if(whitenCoeff & 0x80)
			{
				whitenCoeff ^= 0x11;
				(*dat) ^= m;
			}
			whitenCoeff <<= 1;
		}
		dat++;
	}
}




uint8 bleWhitenStart(uint8 chan)
{
	return invert_8(chan) | 2;
}



void Download_ble_Data(void)
{
	xdata uint8  i = 0;
	xdata uint8  k = 0;
	xdata uint16 Check_TX_Sum = 0;
	
	ble_tx_buffer[i++] = C_TX_Payload_Len;//payloadlen:47 /***0***/	
	ble_tx_buffer[i++] = 0xAA;//前导码	/***1***/
	
	ble_tx_buffer[i++] = 0xD6;//接入地址0x8E89BED6	/***2***/
	ble_tx_buffer[i++] = 0xBE;	/***3***/
	ble_tx_buffer[i++] = 0x89;	/***4***/
	ble_tx_buffer[i++] = 0x8E; 	/***5***/

	ble_tx_buffer[i++] = 0x42;	//PDU Header /***6***/
	ble_tx_buffer[i++] = 37;		//PDU Length /***7***/
	
	ble_tx_buffer[i++] = MAC_0;//0x00	/***8***/
	ble_tx_buffer[i++] = MAC_1;//0x11	/***9***/
	ble_tx_buffer[i++] = MAC_2;//0x22	/***10***/
	ble_tx_buffer[i++] = MAC_3;//0x33	/***11***/
	ble_tx_buffer[i++] = MAC_4;//0x44	/***12***/
	ble_tx_buffer[i++] = MAC_5;//0x55	/***13***/
	
	ble_tx_buffer[i++] = 8;	//Adv_1_Len/***14***/
	ble_tx_buffer[i++] = 0x09;//Adv_1_Type/***15***/
	ble_tx_buffer[i++] = 'A';		/***16***/
	ble_tx_buffer[i++] = 'i';		/***17***/
	ble_tx_buffer[i++] = 'P';		/***18***/
	ble_tx_buffer[i++] = '4';		/***19***/
	ble_tx_buffer[i++] = '9';		/***20***/
	ble_tx_buffer[i++] = '5';		/***21***/
	ble_tx_buffer[i++] = '2';		/***22***/
	
	ble_tx_buffer[i++] = 21;//Adv_2_Len	/***23***/
	ble_tx_buffer[i++] = 0xFF;//Adv_2_Type/***24***/
	
	R_TX_Data_Cnt ++;
	ble_tx_buffer[i++] = (R_TX_Data_Cnt >> 8) & 0xFF;	/***25***/
	ble_tx_buffer[i++] = R_TX_Data_Cnt & 0xFF;	/***26***/
	
	ble_tx_buffer[i++] = 0x00;	//Remoter ID High /***27***/ 
	ble_tx_buffer[i++] = 0x00;	//Remoter ID Low  /***28***/
	
	ble_tx_buffer[i++] = 0xAA;	//device type:Remoter /***29***/
	
	ble_tx_buffer[i++] = 0x02;	//key value /***30***/
	
	ble_tx_buffer[i++] = 0x5A;	//user definition_1 /***31***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_2 /***32***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_3 /***33***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_4 /***34***/
	
	ble_tx_buffer[i++] = 0x5A;	//user definition_5 /***35***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_6 /***36***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_7 /***37***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_8 /***38***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_9 /***39***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_10 /***40***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_11 /***41***/
	ble_tx_buffer[i++] = 0x5A;	//user definition_12 /***42***/
	
	for(k = 0;k < 20;k ++)	//the sum of Adv_2 data include Adv_2_Len
	{
		Check_TX_Sum += ble_tx_buffer[k+23];					
	}
	ble_tx_buffer[i++] = Check_TX_Sum >> 8;	 //the sum of tx data high /***43***/
	ble_tx_buffer[i++] = Check_TX_Sum & 0xFF;//the sum of tx data low	 /***44***/

	ble_tx_buffer[i++] = 0x55;	/***45***/
	ble_tx_buffer[i++] = 0x55;	/***46***/
	ble_tx_buffer[i++] = 0x55;	/***47***/
}

void blePacketEncode( uint8 *packet, uint8 len, uint8 chan)//len = C_TX_Payload_Len + 1
{
	uint8 i, dataLen ;
	
	dataLen = len - 9;//dataLen = C_TX_Payload_Len + 1 - 9
	bleCRC(packet + 6, dataLen, packet + 6 + dataLen);

	for(i = 0; i < 3; i++, dataLen++)
	{
		packet[dataLen + 6] = invert_8(packet[dataLen + 6]); //invert CRC
	}
	
	bleWhiten( packet + 6 , len-9+3, bleWhitenStart(chan) );
}

void copy_white_value(void)
{
	//the value of re-whiten @37ch
	buffer[0] = 0xCF; //0x42
	buffer[1] = 0xF7; //37
	buffer[2] = 0x57; //MAC_0
	buffer[3] = 0xB0; //MAC_1
	buffer[4] = 0x1F; //MAC_2
}
void Download_Recalcu_arry(void)
{
	uint8 i = 0;
	
	buffer[i++] = 0x42;//pdu type	/********0******/
	buffer[i++] = 37;//length	/********1******/
	
	buffer[i++] = MAC_0;//0x00	/********2******/
	buffer[i++] = MAC_1;//0x11	/********3******/ 
	buffer[i++] = MAC_2;//0x22	/********4******trailer ???**/
	buffer[i++] = MAC_3;//0x33	/********5******/
	buffer[i++] = MAC_4;//0x44	/********6******/
	buffer[i++] = MAC_5;//0x55	/********7******/
	
}
void re_calcu_white_value(uint8 ch)//反白化
{

	Download_Recalcu_arry();
	bleWhiten( buffer,8,bleWhitenStart(chLe[ch]) ); 
	
	R_Check_Header[0] = buffer[5];
	R_Check_Header[1] = buffer[6];
	R_Check_Header[2] = buffer[7];
}
extern bit	F_RX_Head ;
void lanya_test(void)
{
	if(0)
	AiP4952_TX_Data(ble_tx_buffer,47);
	else
		AiP4952_RX_Data();
	if(F_RX_Head)
	{
			
			Check_RX_Data();
			F_RX_Head = 0;	
	}
	
	
	
//	if(F_RX_Head)
//	{
//			F_RX_Head = 0;
//			
//	}
	//IE_Enable;
}