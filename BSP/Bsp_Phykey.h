#ifndef	__IO_H__
#define	__IO_H__

#include "..\bsp\globe.h"
#include "..\bsp\config.h"

typedef	struct
{
	u8 In_Put;
	u8 In_Tmp[2];
	u8 KeyValue;
	unsigned char State;
	
}TYP_IO;

void IO_Init(void);
void Kye_Scan(void);
u8 getKeyValue(void);
#endif
































