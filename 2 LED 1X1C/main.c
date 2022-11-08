/*以下程序8路LED流水燈閃燈程序，晶振频率为10MHz*/
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"
void main(void)
{
	unsigned char a = 0x01;
	unsigned char b;

	k18_init();/*HL-K18主板初始化*/

	TRISD=0X00;/*設置PORTD為输出*/

	COL1=1;/*選點陣管的第一列的LED，點陣管的第一列的LED作為顯示LED*/

	while(1)
	{
		PORTD=0B00000001;//16進制0xfe  2進制寫法0B00000001
		/*點陣管亮或滅*/
		Delay10Ms(5);/*延时50mS*/
		PORTD=0B00000000; //0x00; 0B00000000
		Delay10Ms(5);/*延时50mS*/
	} 
}
