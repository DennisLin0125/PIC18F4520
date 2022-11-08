/*以下程式為8路LED流水燈程式，晶振頻率為10MHz*/
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"

void main(void)
{
	unsigned char a = 0x01;
	unsigned char b;

	k18_init();/*HL-K18主板初始化*/

	TRISD=0X00;/*設定D口為輸出*/

	COL1=1;/*選通點陣管的第一列的LED，點陣管的第一列的LED作為顯示LED*/

	while(1)
	{
		b=a>>7;/*來得到正常左移丟失的位和循環移位后其正確位置*/
		a=a<<1;/*左移1位*/
		a=a|b;
		PORTD=a;
		/*點陣管亮或滅*/
		DelayMs(1);/*延時50mS*/
	} 
}

//六種位運算子: & 按位與 | 按位或 ^ 按位異或 ~ 取反 << 左移 >> 右移 