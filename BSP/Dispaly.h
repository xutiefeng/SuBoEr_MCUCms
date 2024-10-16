#ifndef DISPLAY_H
#define DISPLAY_H


#include "bsp_Led.h"

#define BIT0  0x01
#define BIT1  0x02
#define BIT2  0x04
#define BIT3  0x08
#define BIT4  0x10
#define BIT5  0x20
#define BIT6  0x40
#define BIT7  0x80
#define BIT8  0x0100
#define BIT9  0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000
#define BIT16 0x010000
#define BIT17 0x020000
#define BIT18 0x040000
#define BIT19 0x080000
#define BIT20 0x100000
#define BIT21 0x200000
#define BIT22 0x400000
#define BIT23 0x800000
#define BIT24 0x01000000
#define BIT25 0x02000000
#define BIT26 0x04000000
#define BIT27 0x08000000
#define BIT28 0x10000000
#define BIT29 0x20000000
#define BIT30 0x40000000
#define BIT31 0x80000000

#define S1_A  BIT0
#define S1_B  BIT2
#define S1_C  BIT5
#define S1_D  BIT6
#define S1_E  BIT4
#define S1_F  BIT1
#define S1_G  BIT3
#define S1_H  BIT7

#define CHAR1_0  (S1_A+S1_B+S1_C+S1_D+S1_E+S1_F)
#define CHAR1_1  (S1_B+S1_C)
#define CHAR1_2  (S1_A+S1_B+S1_D+S1_E+S1_G)
#define CHAR1_3  (S1_A+S1_B+S1_C+S1_D+S1_G)
#define CHAR1_4  (S1_B+S1_C+S1_F+S1_G)
#define CHAR1_5  (S1_A+S1_C+S1_D+S1_F+S1_G)
#define CHAR1_6  (S1_A+S1_C+S1_D+S1_E+S1_F+S1_G)
#define CHAR1_7  (S1_A+S1_B+S1_C)
#define CHAR1_8  (S1_A+S1_B+S1_C+S1_D+S1_E+S1_F+S1_G)
#define CHAR1_9  (S1_A+S1_B+S1_C+S1_D+S1_F+S1_G)
#define CHAR1_A  (S1_A+S1_B+S1_C+S1_E+S1_F)
#define CHAR1_b  (S1_C+S1_D+S1_E+S1_F+S1_G)
#define CHAR1_C  (S1_G+S1_D+S1_E)
#define CHAR1_d  (S1_B+S1_C+S1_D+S1_E+S1_G)
#define CHAR1_D  (S1_B+S1_C+S1_D+S1_E+S1_G)
#define CHAR1_E  (S1_A+S1_D+S1_E+S1_F+S1_G)
#define CHAR1_F  (S1_A+S1_E+S1_F+S1_G)
#define CHAR1_H  (S1_B+S1_C+S1_E+S1_F+S1_G)
#define CHAR1_o  (S1_C+S1_D+S1_E+S1_G)
#define CHAR1_P  (S1_B+S1_A+S1_E+S1_F+S1_G)
#define CHAR1_N  (S1_A+S1_B+S1_C+S1_E+S1_F)
#define CHAR1_n  (S1_C+S1_E+S1_G)
#define CHAR1_U  (S1_B+S1_C+S1_E+S1_F+S1_D)
#define CHAR1__		S1_G

extern void SetIcon_DingShi_1628(u8 v);
extern void SetIcon_ShuShui_1628(u8 v);
extern void SetIcon_ChuMan_1628 (u8 v);
extern void display_hex(u8 v);
extern void display_dec(u8 v);
extern void display_process(u8 u);
extern void display_Close(void);
extern u8 GetDisplayValue(u8 v);
extern void test(void);
  void SetIconH_1628(u8 v);
  void SetIconC_1628(u8 v);
#endif