


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
���ܣ� TM1629д����
*********************************/
void write(uchar wr_data)
{
  uchar  	 i;
	stb =0;	   //����Ч��Ƭѡ�źţ�Ƭѡ�ź��ǵ͵�ƽ��Ч��
	// _nop_();
	// _nop_();		
	Deleat_6Nop();
	 for(i=0;i<8;i++)//��ʼ����8λ���ݣ�ÿѭ��һ�δ���һλ����
	 {
	    if(wr_data&0x01)
	     dio =1;
	    else dio =0;
	     tmclk =0;
	    // _nop_();
	    // _nop_();
			Deleat_6Nop();
	    tmclk =1; 
	    wr_data >>= 1;//��λ���ݣ���λ��ǰ!
	 }
}
/*********************************
    TM1629����ָ��
���ܣ� ����LED������Ӧ����ʾ
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
  write(0x40);//д���ݵ���ʾ�Ĵ��������õ�ַ�Զ���һ
  stb = 1;
	Deleat_6Nop();
  write(0xc0);//��ʾ�Ĵ�����00H��Ԫ��ʼ 

	for(i=0;i<16;i++)
	{
		write(Disp_buf[i]);
	}
  stb=1;
	Deleat_6Nop();
  write(HuiDu_10_16);//HuiDu_10_16��ʾ���Ʋ���������������Ļ�����ȿ���ͨ���ı����λ����
	stb=1;	Deleat_6Nop();
}