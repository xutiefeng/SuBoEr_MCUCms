/*
 * @Author: xu_tie_feng xu_tie_feng@163.com
 * @Date: 2024-06-02 01:28:30
 * @LastEditors: xu_tie_feng xu_tie_feng@163.com
 * @LastEditTime: 2024-06-02 20:18:19
 * @FilePath: \LanYaDianReTan_8501\BSP\bsp_Heat.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef BSP_HEAT_H
#define BSP_HEAT_H 

#include "..\bsp\globe.h"
#include "..\bsp\config.h"
#include "..\bsp\config.h"


#define ___HeatToatl 2//有多少路加热

typedef struct
{
		u8 id;		//对象 支持256个对象
		u8 action;//动作
		u8 time;//动作时间
		u8 CurMode;
}STHeat;


typedef enum 
{
  HeatUnitLumbarBack,          //腰背
  HeatUnitSeat,                //座部
  HeatUnitCalves,              //小腿
  HeatUnitFeet,                //脚部

  HeatUnitAll                  //所有单元
}HeatUnit_t;
void HeatInit(void);
void HeatModeSwitch(void);
u8 GetHeatUnit(void);
void HeatHandle(void);
void NTC_Process(void);
void  SetLHeatLevel(HeatUnit_t HeatUnit,u8 level);
//void  SetLHeat(u8 id,u8 acction,u8 time);
u8 HeatProcess(u8 id_v);
u8 getHeatLevel(void);


#endif 