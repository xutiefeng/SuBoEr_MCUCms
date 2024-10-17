/*
 * @Author: xu_tie_feng xu_tie_feng@163.com
 * @Date: 2024-06-02 01:28:30
 * @LastEditors: xu_tie_feng xu_tie_feng@163.com
 * @LastEditTime: 2024-06-02 19:56:31
 * @FilePath: \LanYaDianReTan_8501\BSP\Bsp_Phykey.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "Bsp_Phykey.h"



volatile TYP_IO	 str_IO;

#if Bsp_Phykey_CONFIG


/****************************************************************************************************************************************** 
* 函数名称:	IO_Process
* 功能说明:	周期扫描物理按键
* 输    入: 无
* 输    出: 无

******************************************************************************************************************************************/
void Kye_Scan(void)
{
	
//	u8 key_v = GetAD_Key();//获取AD值
	
	if(str_IO.State < 2)//扫描两次
	{ 
			str_IO.In_Tmp[str_IO.State] = (TKL_GetKey());
	}
	else
	{
		if((str_IO.In_Tmp[0] == str_IO.In_Tmp[1]))//扫描两次，结果相同，为有效值
		{
			str_IO.In_Put = str_IO.In_Tmp[0];
		}
		str_IO.State = 0;
		return;
	}
	str_IO.State ++;
}

/****************************************************************************************************************************************** 
* 函数名称:	getKeyValue
* 功能说明:	获取按键值
* 输    入: 无
* 输    出: 无

******************************************************************************************************************************************/

u8 getKeyValue(void)
{
	if(str_IO.In_Put > 0)
	{
	  	return str_IO.In_Put ;
	}
	
	else
	{
			return 0;
	}

}
#endif
