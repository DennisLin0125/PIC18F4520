/*蜂鳴器發聲實驗*/
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"
//#include <delays.h>

void main(void)
{
k18_init();/*HL-K18主板初始化*/

while(1)
{
  BZ=0XFF;
  Delay10Ms(1);/*延時50mS*/
  BZ=0X00;
  Delay10Ms(1);/*延時50mS*/
  // BZ=!BZ;
   //Delay10us(25);/*延時250uS*/
}	
}
