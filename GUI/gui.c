//#include "gui.h"
//#include <string.h>
//#include "gui_material.h"

//#define LCD_HEIGHT 128
//#define LCD_WIDTH	 64
////u8 DispVirRAM[LCD_HEIGHT / 8][LCD_WIDTH];
//u8 DispVirRAM[LCD_HEIGHT / 8][LCD_WIDTH];
//u8 wallRAM[LCD_HEIGHT / 8 - 1][LCD_WIDTH];
//static const u8  Mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

//#define POINT     DispVirRAM[y/8][x]
//#define PMASK     Mask[y&0x07]

//void Clr_DispRAM(void)
//{
//	memset(DispVirRAM, 0, sizeof(DispVirRAM));
//}
//void Clr_DispRAM_Statusbar(void)
//{
//	memset(DispVirRAM, 0, LCD_WIDTH*2);
//}
//void Clr_DispRAM_Content(void)
//{
//	memset(&DispVirRAM[2][0], 0, sizeof(DispVirRAM) - LCD_WIDTH*2);
//}

//void Fill_DispRAM(u8 a)
//{
//	memset(DispVirRAM, a, sizeof(DispVirRAM));
//}


//void GUI_DrawPoint(short x, short y, u8 color)
//{
//	if(y > LCD_HEIGHT - 1 || x > LCD_WIDTH - 1) {
//		return;
//	}

//	if(color == 1) {
//		POINT |= PMASK;
//	} else if(color == 0) {
//		POINT &= ~PMASK;
//	} else {
//		POINT ^= PMASK;
//	}
//}


//void GUI_HLine(uint16_t x0, uint16_t x1, uint16_t y, u8 color)
//{
//	if(x0 > x1) {
//		while(1);//SWAP(x0, x1);
//	}

//	do {
//		GUI_DrawPoint(x0, y, color);
//		x0++;
//	} while(x1 >= x0);
//}


//void GUI_RLine(uint16_t x, uint16_t y0, uint16_t y1, u8 color)
//{
//	if(y0 > y1) {
//		while(1);//SWAP(y0, y1);
//	}
//	do {
//		GUI_DrawPoint(x, y0, color);
//		y0++;
//	} while(y1 >= y0);
//}

//void GUI_Rectangle_Fill(uint16_t x0, uint16_t y0, uint16_t width, uint16_t high, u8 color)
//{
//	uint16_t x1, y1;

//	x1 = x0 + width - 1;
//	y1 = y0 + high - 1;

//	if(x0 > x1) {
//		while(1);//SWAP(x0, x1);
//	}
//	if(y0 > y1) {
//		while(1);//SWAP(y0, y1);
//	}

//	if(y0 == y1) {
//		GUI_HLine(x0, x1, y0, color);
//		return;
//	}
//	if(x0 == x1) {
//		GUI_RLine(x0, y0, y1, color);
//		return;
//	}

//	while(y0 <= y1) {
//		GUI_HLine(x0, x1, y0, color);
//		y0++;
//	}
//}

