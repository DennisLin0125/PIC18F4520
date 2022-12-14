/*以下程式為8路LED流水燈閃動程式，晶振頻率為10MHz*/
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"
void main(void)
{
	unsigned char a = 0x01;
	unsigned char b;

	k18_init();/*HL-K18主板初始化*/

	TRISD=0X00;/*設定PORTD為輸出*/

	COL1=1;/*選通點陣管的第一列的LED，點陣管的第一列的LED作為顯示LED*/

	while(1)
	{
		PORTD=0B00000001;//16進位制寫法0xfe  2進位制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000010;//16進位制寫法0xfe  2進位制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000100;//16進位制寫法0xfe  2進位制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延時50mS*/

		PORTD=0B00001000;//16進位制寫法0xfe  2進位制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00010000;//16進位制寫法0xfe  2進位制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00100000;//16進位制寫法0xfe  2進位制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延時50mS*/

		PORTD=0B01000000;//16進位制寫法0xfe  2進位制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B10000000;//16進位制寫法0xfe  2進位制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延時50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延時50mS*/


	} 
}

//六種位運算子: & 按位與 | 按位或 ^ 按位異或 ~ 取反 << 左移 >> 右移 