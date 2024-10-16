

#include <string.h>
#include "bsp_eeprom.h"
#include "globe.h"

#define _INIT_DADA 0x5b
#define  EEPROM0_ADDR 0ul
#define  EEPROM1_ADDR 0x200UL
#define  EEPROM2_ADDR 0x400UL
#define  EEPROM3_ADDR 0x600UL
#define EEPROM_SIZE 0XFFFF


#define WriteToEEprom(X)   				WriteEEpromData(EEPROM##X##_ADDR,(u8 *)gstAM901.stFilter,sizeof(ST_Filter)) 
#define ReadFromEEprom(X)  				IAP_ReadByteArray(EEPROM##X##_ADDR,(u8 *)gstAM901.stFilter,sizeof(ST_Filter),IAP_MEMTYPE_EEPROM)
#define EraseEEprom(X)            IAP_EEPROMSectorEraseOption(EEPROM##X##_ADDR)

#define EEPROM_DATA_LEN 4
#define Block_Size 0XFFff
/**************************************************
*��������:void IAP_SectorEraseOption(Address,Data,IAP_MemType)
*��������:IAP��������
*��ڲ���:uint32_t:Address:IAP������ַ
*         IAP_MemType_TypeDef:IAP_MemType:IAP��������
*���ڲ���:void
**************************************************/

//u8 testAyy[]={0x60,0x33,0x99,0x90,0x90,0x90,0xD5,0xFA};

//static u8 FromEeppAry[8];


u8 WriteEEpromData(u32 x,u8 *p,u8 len)
{
	u8 i ,FromEepromData;
	u8 *pData = p;
	u32 addr =x;
	
	
	for(i= 0;i < len; i++)
	{	
		IAP_EEPROMProgramByteOption(addr+i,pData[i]);
		FromEepromData =IAP_ReadByte(addr+i,IAP_MEMTYPE_EEPROM);
		if(FromEepromData != pData[i] )
			return 0;
	}
	return 1;
}




void WriteTempEeprom(u8 blolk)
{
	if(blolk ==0)
	{
		if(!gstAM901.Run.Bit.EepromBlok )
		{
				//gstAM901.stFilter->type++;
				if(WriteToEEprom(0) == 0)
				{
						if(WriteToEEprom(0) == 0)
						{
								if(WriteToEEprom(0) == 0)
								{
										WriteToEEprom(0);
								}
						}
				}
		}
	}

	else if(blolk ==1)
	{
		if(!gstAM901.Run.Bit.EepromBlok )
		{
				gstAM901.stFilter->type++;
				if(WriteToEEprom(1) == 0)
				{
						if(WriteToEEprom(1) == 0)
						{
								if(WriteToEEprom(1) == 0)
								{
										WriteToEEprom(1);
								}

						}
				}
		}
	}
 	else
	{
			gstAM901.stFilter->type  = 0;
			WriteToEEprom(1);
	}
 	  
}


void  ReadEEprom(u8 x)
{
	u8 len;
	u8 cnt =0;
loop:
	if(x == 0)
	 len = ReadFromEEprom(0);
	else if(x == 1)
	 len = ReadFromEEprom(1);
	
	if(len != sizeof(ST_Filter) && cnt++ >3)
		goto loop;
}

/****************************************************************************************************************************************** 
* ��������:	 ReadTempEeprom
* ����˵��:  ��ȡEEPROM�ӿ�
* ��    ��: ��	
* ��    ��: ��
******************************************************************************************************************************************/



void EEpromInit(void)
{
		if(ReadFromEEprom(0) == 0)
		{
				ReadFromEEprom(0);
		}
		if(gstAM901.stFilter->type< EEPROM_SIZE)
		{
				gstAM901.Run.Bit.EepromBlok = 0;
				EraseEEprom(0);
				return;
		}
		else
		{
				if(ReadFromEEprom(1) == 0)
				{
						ReadFromEEprom(1);
				}
		}
		
	  if(gstAM901.stFilter->type < EEPROM_SIZE)//5a ��ʾ��һ���õ���EEPROM_ADDR �飬��ǳ�F5;��һ����EEPROM1_ADDR
		{
				gstAM901.Run.Bit.EepromBlok = 1;//gstAM901.Run.Bit.EepromBlok = 1;
				EraseEEprom(1);//EraseEEprom(1);
		}
		else//�״�ʹ��
		{
					gstAM901.Run.Bit.EepromBlok = 0;
					EraseEEprom(1);
					memset((u8 *)gstAM901.stFilter,0,EEPROM_DATA_LEN);
					FirstPownOnFlag = 1;
		}
}








