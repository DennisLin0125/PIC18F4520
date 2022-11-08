//9999計數器C語言程式 數碼管有點閃動為正常現象，可以自己調整，《你會的》。
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"

const unsigned char DB[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //0~9數據
const unsigned char DB1[]={0x02,0x20,0x48,0x04};

void main()
{
	unsigned char j,k=3;
	unsigned int i,a,bit1000,bit100,bit10,bit1;

	k18_init();/*HL-K18主板初始化*/

	TRISD=0X00;/*設定PORTD為輸出*/
	TRISA=0X00;/*設定PORTA為輸出*/
	i=0;
	while(1)
	{
	   	a=i;
	    
	   	bit1000=a/1000%10;//提取千位
	   		
	   	bit100=a/100%10;//提取百位
	   		
	   	bit10=a/10%10;//提取十位

	   	bit1=a%10;//提取個位
		
	   	PORTD=DB[bit1];
		DelayMs(1);/*延時5mS*/

		PORTA=DB1[k];
		k=k-1;
	   
	   	PORTD=DB[bit10];
	   	DelayMs(1);/*延時5mS*/
				
		PORTA=DB1[k];
		k=k-1;
	   	
	   	PORTD=DB[bit100];
	   	DelayMs(1);/*延時5mS*/
				
		PORTA=DB1[k];
		k=k-1;
	 
	   	PORTD=DB[bit1000];
	   	DelayMs(1);/*延時5mS*/

		PORTA=DB1[k];

		if(k=1)k=3;
  			
   		i=i+1;
	}
}

