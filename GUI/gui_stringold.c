#include "gui_string.h"
#include "gui_material.h"
#include "gui.h"
#include <string.h>


const uint8_t DrawMask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

//绘制 m-宽,n-高的图像
short DrawBmp_m_n(short x, short y, uint8_t m, uint8_t n, const uint8_t *pBitmap)
{
	uint16_t i, j;
	uint16_t tmpx = x, tmpy = y;
	uint8_t mtemp = m;

	for(i = 0; i < n; i++) {
		while(mtemp) {
			for(j = 0; j < 8 && j < mtemp; j++, tmpx++) {
				if(*pBitmap & DrawMask[j]) {
					GUI_DrawPoint(tmpx, tmpy, 1);
				}
			}
			pBitmap++;
			if(j == 8) {
				mtemp -= 8;
			} else {
				mtemp = 0;
			}
		}
		mtemp = m;
		tmpy++;
		tmpx = x;
	}
	return x + m;
}




short DispSmallASC(short x, short y, const uint8_t *p)
{
	uint16_t tmpx = x;
	uint16_t tmpy = y;
	const uint8_t *tmpEn;
	

	while(*p>=0x20 && *p <0x80) {
		tmpEn = SmallASC_5x8[*p - 0x20];
		if(*p == ':' || *p == '.' || *p == ' ') {
			DrawBmp_m_n(tmpx - 1, tmpy, 5, 8, tmpEn), x += 2;
		} else {
			DrawBmp_m_n(tmpx, tmpy, 5, 8, tmpEn), x += 5;
		}
		tmpy = y;
		tmpx = x;
		p++;
	}
	return tmpx;
}

//y_inc:换行后的间距
void DispStrAtCenter(uint8_t line, uint8_t y_inc, const uint8_t *str)
{
	uint8_t len, linechar_cnt = 0, end_flag = 0;
	char x;
	uint8_t minchar_cnt = 0, line_cnt = 0, line_total = 0;
	uint8_t buf[128];
	uint8_t *p = buf;
	const uint8_t *p_start = p, *p_bak;
	
	if(str[0] < 0x20 || str[0] > 0x7f) {
		__NOP();
		return;
	} 

	strncpy((char *)buf, (const char *)str, sizeof(buf) - 1);
	buf[sizeof(buf) - 1] = '\0';

	while(*p) {
		if(*p == '\n') {
			line_total++;
		}
		p++;
		if(*p == '\0') {
			line_total++;
		}
	}

	p = buf;

	while(*p && end_flag == 0) {
loop:
		if(*p == '\n' || (*p == '\0' && linechar_cnt)) {
			*p = '\0';
			//------------------------------------------------------
			len = strlen((const char *)p_start);
			len *= 5;
			p_bak = p_start;
			while(*p_start) {
				if(*p_start == ':' || *p_start == '.' || *p_start == ' ') {
					minchar_cnt++;
				}
				p_start++;
			}
			len -= minchar_cnt * 2;
			
			if(len>LCD_WIDTH) {
				x = 0;
			} else {
				x = LCD_WIDTH - len;
				x /= 2;
			}
			DispSmallASC(x, line - (line_total / 2 * y_inc) + line_cnt * y_inc, p_bak);
			//------------------------------------------------------
			line_cnt++;
			linechar_cnt = 0;
			p_start = p + 1;
		} else {
			linechar_cnt++;
		}
		p++;
		if(*p == '\0') {
			end_flag = 1;
			goto loop;
		}
	}
}

short DispBigNum(short x, short y, const uint8_t *p)
{
	uint16_t tmpx = x;
	uint16_t tmpy = y;
	uint8_t idx;

	while(*p) {
		if(*p == '.') {
			idx = 10;
		} else if(*p == 'A') {
			idx = 11;
		} else {
			idx = *p - '0';
		}
		DrawBmp_m_n(tmpx, tmpy, 14, 17, BigNum2[idx]);
		if(*p == '1') {
			x += 9;
		} else if(*p == '.') {
			x += 7;
		} else {
			x += 14;
		}
		tmpy = y;
		tmpx = x;
		p++;
	}
	return tmpx;
}

char testchar = 0;
char testx = 0;
//以center点为中心对齐
char gui_calc_x(const uint8_t *str, char offset, uint8_t normal, uint8_t small, uint8_t center)
{
	uint8_t width = 0;
	char x = 0;

	testchar = offset;
	while(*str >= 0x20) {
		if(*str == ':' || *str == '.' || *str == ' ') {
			width += small;
		} else {
			width += normal;
		}
		str++;
	}
	x = center - width / 2;

	testx = x+offset;
	return x + offset;
}
