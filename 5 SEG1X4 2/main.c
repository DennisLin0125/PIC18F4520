//第一位數碼管顯示3程式
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"

const unsigned char DB[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //0~9數據

void main()
{
	unsigned char j;

	k18_init();/*HL-K18主板初始化*/

	TRISD=0X00;/*設定D口為輸出*/
	TRISA=0X00;
	TRISE=0X00;
	TRISC=0XFE;

	while(1)
	{

		PORTD=0x3F; //第一位數碼管顯示一個2
		PORTA=0XFF; //個位的位選 RA1
		PORTE=0XFF;
		PORTC=0XFF;
		DelayMs(2);/*延時5mS*/


	}
}

