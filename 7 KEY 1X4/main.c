/*4位獨立式鍵盤+1位靜態數碼管實驗，按下SW0-SW3時1位數碼管會顯示0123*/
#include <p18cxxx.h>
#include "k18.h"

Uint a[]={0x3f,0x06,0x5b,0x4f};

Uint* p=&a[0];


void main(void)
{
	k18_init(); 
	
	TRISD=0X00;/*設定D口為輸出*/
	PORTD=0X00;
	
	COL1=1;/*將數碼管設定成1位靜態方式*/
	COL2=0;
	COL3=0;
	COL4=0;


	while(1)
	{
		if (SW0==0) PORTD=*p; /*顯示SW0曾經按下*/
		
		if (SW1==0) PORTD=*(p+1);/*顯示SW1曾經按下*/
	
		if (SW2==0) PORTD=*(p+2);/*顯示SW2曾經按下*/
	
		if (SW3==0) PORTD=*(p+3);/*顯示SW3曾經按下*/
	}
}
