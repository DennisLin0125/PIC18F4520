//第一位數碼管顯示0123456789程式
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"

const unsigned char DB[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //0~9數據

void main()
{
	unsigned char j;

	k18_init();/*HL-K18主板初始化*/

	TRISD=0X00;/*設定PORTD為輸出*/

	while(1)
	{	
   		for(j=0;j<10;j++) 
   		{
   			PORTD=DB[j];
   			COL1=1;   //個位的位選
   			DelayMs(50);/*延時5mS*/
 		}
	}
}

