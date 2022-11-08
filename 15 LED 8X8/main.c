//以下程式在8×8點陣LED上從左到右循環流動顯示「天天向上」四個字，晶振頻率為10MHz。
#include <p18cxxx.h>
#include "k18.h"


/*定義顯示文字「天天向上」的字模數據表*/
/*字模由LEDDOT產生；字模的提取方式為：逐列提取；字模的顯示方式為：單字單行顯示；產生的字模格式：C51十六進制 */
const unsigned char TABLE[]=
{	
    //0xB1,0xB2,0xB4,0xF8,0xBC,0xB6,0xB3,0x1
	0x91,0x92,0x94,0x0F8,0x94,0x92,0x91,0x11,0x00,
	0x91,0x92,0x94,0x0F8,0x94,0x92,0x91,0x11,0x00,
  	0x7F,0x40,0xDC,0x54,0x54,0x5C,0x43,0x7E,0x00,
  	0x1,0x1,0x1,0xFF,0x21,0x21,0x21,0x21,0x00,
};


const rom unsigned char COL_SEL_PORTA[]={0b00000000,0b00000000,0b00000000,0b00000000,0b00100000,0b00001000,0b00000100,0b00000010};
const rom unsigned char COL_SEL_PORTE[]={0b00000000,0b00000100,0b00000010,0b00000001,0b00000000,0b00000000,0b00000000,0b00000000};
/*定義列選通訊號的數據表*/

void delay();

void main()
{
	Uchar i,col;
	Uchar time=0;
	Uchar col_start=0;/*目前顯示起始列標記，儲存目前顯示起始列在顯示文字「天天向上」數據表中的絕對位置*/

	k18_init();/*HL-K18主板初始化*/
	PORTD=0X00;
	TRISD=0X00;//設定D口為輸出


	while(1)
	{
		for (i=0;i<=7;i++)
	 	{
	 		PORTA=COL_SEL_PORTA[i];/*送出掃瞄列選通訊號*/
			PORTE=COL_SEL_PORTE[i];/*送出掃瞄列選通訊號*/

			if (i==0)
			{ 
				COL8=1;/*送出掃瞄列選通訊號*/
			}
			else 
			{
				COL8=0;
			}
	 			
			col=col_start+i;/*得到目前掃瞄列在顯示文字「天天向上」數據表中的絕對位置*/
	 		
			if (col>35)
			{ 
				col=col-36;/*目前掃瞄列絕對位置超出正常範圍，糾正*/
			}

	 		PORTD=TABLE[col];/*送出掃瞄列內容*/
	 				
	 		delay();/*延時1mS*/
	 		
	 		if (i==0)
			{	 
				time++;
			}

	 		if (time==10)
	 		{
				col_start++;
			 	time=0;
			}
	 		if (col_start>35)
			{ 
				col_start=col_start-36;/*目前顯示起始列標記超出正常範圍，糾正*/
			}
		}
	} 
} 
 
void delay()/*延時1mS*/
{
    Uchar i;
    for(i=0;i<142;i++)
    {;}
}


