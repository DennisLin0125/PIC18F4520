/*以下程序为8路LED流水灯闪动程序，晶振频率为10MHz*/
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"
void main(void)
{
unsigned char a = 0x01;
unsigned char  b;

k18_init();/*HL-K18主板初始化*/

TRISD=0X00;/*设置D口为输出*/

COL1=1;/*选通点阵管的第一列的LED，点阵管的第一列的LED作为显示LED*/

while(1)
	{
	PORTD=0B00000001;//16进制写法0xfe  2进制写法0B00000001
 	/*点阵管亮或灭*/
	Delay10Ms(5);/*延时50mS*/
	PORTD=0B00000000; //0x00; 0B00000000
	Delay10Ms(5);/*延时50mS*/
 	} 
}
