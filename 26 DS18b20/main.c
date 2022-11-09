/*數字溫度計實驗*/
//使用說明，請換上40M晶振

//如果不顯溫度時請把P22 P7之間的VPP跳線帽取下，
//再給J1重新上電就可以了(取下J1再裝上J1的意思）。
#include <p18cxxx.h>
#include "k18.h"
#include "lcd1602.h"
#include "ds18b20.h"
#include"ds1302.h"
/*實驗說明：18B20晶片插入K18開發板P4插座，插入時注意方向，18B20晶片上的型號朝外*/
void main(void)
{
	int tp;		/*暫存器定義*/

	LCD_init();
	k18_init(); 
	LCD_setxy(1,1);
	LCD_wrstr("wwm.Dennis.com"); 
	LCD_setxy(2,1);
	LCD_wrstr("TEMP:");
	LCD_setxy(2,14);
	LCD_wrchar(USER_CHAR6);/*在LCD屏上顯示單個預定義字元:℃*/
			
	while(1)
	{
		tp=get_temp();/*呼叫溫度轉換函式*/
		if(tp>0x3fff) /*判斷是否為負溫，若是負溫，前面顯示負號*/
		{      
			LCD_setxy(2,7);  
			LCD_wrchar('-');
		}
		else
		{      
			LCD_setxy(2,7);  
			LCD_wrchar('+');/*是正溫，前面顯示正號*/
		}
		tp&=0x3fff;/*遮蔽最高兩位符號位*/
		LCD_setxy(2,13);  
		LCD_wrlval(tp,5,2);
	}
}
