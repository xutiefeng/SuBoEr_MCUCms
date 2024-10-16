#ifndef	__IO_H__
#define	__IO_H__

#include "..\bsp\globe.h"
#include "..\bsp\config.h"

typedef	struct
{
	u32 In_Put;
	u32 In_Tmp[2];
	unsigned char State;
	
}TYP_IO;

void IO_Init(void);
void Kye_Scan(void);
u8 getKeyValue(void);
#endif
































