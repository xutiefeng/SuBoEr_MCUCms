#ifndef __DispChinese_H
#define __DispChinese_H
#include "types.h"

extern const uint8_t DrawMask[];


short DrawBmp_m_n(short x,short y,uint8_t m,uint8_t n,const uint8_t *pICO);
short DispSmallASC(short x,short y,const uint8_t *p);
short DispBigNum(short x,short y,const uint8_t *p);
char gui_calc_x(const uint8_t *str, char offset, uint8_t normal, uint8_t small, uint8_t center);
void DispStrAtCenter(uint8_t line, uint8_t y_inc, const uint8_t *str);
short DispBigASC(short x,short y,const uint8_t *p);

#endif

