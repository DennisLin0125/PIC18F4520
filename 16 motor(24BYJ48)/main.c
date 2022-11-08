/*步進電機實驗*/
/*注意：本必須使用10MHZ晶振*/
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"


void main(void)
{
k18_init();/*HL-K18主板初始化*/
PORTD=0X80;/*打開步進電機相序指示器*/
while(1)
	{
	M1=0;
 	M4=1;
   	DelayMs(1);/*延時1mS*/
 	M4=0;
 	M3=1;
   	DelayMs(1);/*延時1mS*/
	M3=0;
	M2=1;
   	DelayMs(1);/*延時1mS*/
 	M2=0;
 	M1=1;
  	DelayMs(1);/*延時1mS*/
	}
} 
