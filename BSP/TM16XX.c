


#include "TM16XX.h"

	
//;--------------------Tm16XX??---------------------------

	
#define  stb			P2_5
#define  dio			P3_5
#define  tmclk 		P2_4
#define  _nop_()     nop_()
byte   A_Disp_buf[16];
	
void Deleat_6Nop(void)
{
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();	
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
}

/*********************************   
功能： TM1629写数据
*********************************/
void write(uchar wr_data)
{
  uchar  	 i;
	stb =0;	   //给有效的片选信号（片选信号是低电平有效）
	// _nop_();
	// _nop_();		
	Deleat_6Nop();
	 for(i=0;i<8;i++)//开始传送8位数据，每循环一次传送一位数据
	 {
	    if(wr_data&0x01)
	     dio =1;
	    else dio =0;
	     tmclk =0;
	    // _nop_();
	    // _nop_();
			Deleat_6Nop();
	    tmclk =1; 
	    wr_data >>= 1;//移位数据，低位在前!
	 }
}
/*********************************
    TM1629控制指令
功能： 驱动LED屏做相应的显示
*********************************/

void xianshi(void)
{
	uchar i=0; 
	uchar		Disp_buf[16];
//-----------------------------------------
	stb = 1;
  tmclk = 1;
  dio = 1;
//-----------------------------------------
	for(i=0;i<16;i++)
	{
			Disp_buf[i]=0;
	}
//-----------------------------------------
	for(i=0;i<16;i++)
	{
			Disp_buf[i]=A_Disp_buf[i].all;
	}

	Deleat_6Nop();
  write(0x40);//写数据到显示寄存器，采用地址自动加一
  stb = 1;
	Deleat_6Nop();
  write(0xc0);//显示寄存器的00H单元开始 

	for(i=0;i<16;i++)
	{
		write(Disp_buf[i]);
	}
  stb=1;
	Deleat_6Nop();
  write(HuiDu_10_16);//HuiDu_10_16显示控制参数，点亮数码屏幕，亮度可以通过改变低三位调节
	stb=1;	Deleat_6Nop();
}