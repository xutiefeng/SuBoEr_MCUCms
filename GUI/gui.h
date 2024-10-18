#ifndef __GUI_H
#define __GUI_H

#include "../bsp/includeall.h"

#define LCD_WIDTH	 	128
#define LCD_HEIGHT 		64

extern uint8_t DispVirRAM[LCD_HEIGHT/8][LCD_WIDTH];


void GUI_DrawPoint(short x,short y,uint8_t color);
void Clr_DispRAM(void);
void Clr_DispRAM_Statusbar(void);
void Clr_DispRAM_Content(void);
void Fill_DispRAM(uint8_t dat);
void GUI_Rectangle_Fill(uint16_t x0, uint16_t y0, uint16_t width, uint16_t high, uint8_t color);
void GUI_RLine(uint16_t x, uint16_t y0, uint16_t y1, u8 color);
void GUI_HLine(uint16_t x0, uint16_t x1, uint16_t y, u8 color);
#endif
