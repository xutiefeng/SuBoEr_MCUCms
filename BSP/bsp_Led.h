/*
 * @Author: xu_tie_feng xu_tie_feng@163.com
 * @Date: 2024-06-02 01:28:30
 * @LastEditors: xu_tie_feng xu_tie_feng@163.com
 * @LastEditTime: 2024-06-02 20:39:10
 * @FilePath: \LanYaDianReTan_8501\BSP\bsp_Led.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/* 
 * File:   bsp_Led.h
 * Author: lix
 *
 * Created on 2022?11?15?, ??8:23
 */

#ifndef BSP_LED_H
#define	BSP_LED_H
#include "..\bsp\globe.h"
#include "..\bsp\config.h"
#include "..\bsp\includeall.h"
#if  LED_CONFIG

typedef struct
{
		u8 id;		//���� ֧��256������
		u8 action;//����
		//u8 level;//����ǿ��
		u8 time;//����ʱ��
		
}STLED;

typedef struct
{
		u8 id;		//���� ֧��256������
		u8 action;//����
		u8 level;//����ǿ��
		u8 time;//����ʱ��
		
}STLedLink;

typedef enum
{
	 LEDOnOffTimeTabMax = 3,
	 LED_time_500ms = 5,
	 LED_time_1s = 10,
	 LED_time_loop ,	
	 LED_time_ingore = 255,	
}enum_TIEME_Per500ms;

extern u32 GetLedState(void);
extern void SetLed_ShortPress(u8 level);
extern void SetLED_Init(void);
extern void ScanLed_Test( u32 v,u8 pian_yi);
extern void display_Heat(u8 v);
extern void SetIcon_H(u8 v);
extern void SetIcon_C(u8 v);
extern void SetIcon_ChuMan(u8 v);
extern void SetIcon_ShuShui(u8 v);
extern void SetIcon_DingShi(u8 v);
extern void closeAll_display(void);
extern void LED_Key(u8 v);
#endif	/* LED_H */



