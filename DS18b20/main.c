/*數字溫度計實驗*/
//使用說明，請換上40M晶振

//如果不顯溫度時請把P22 P7之間的VPP跳線帽取下，
//再給J1重新上電就可以了(取下J1再裝上J1的意思）。

//取下J22 J7 跳線的VPP 是不能燒寫程式的
//實驗注意事項1：請一定要把  RA2 RA3 RA5 分別接到  RS RW EN位置上
//實驗注意事項2：如果想程式自己跑，可以斷開P22 P7 中的 1 VPP跳線帽。
//實驗注意事項3：電壓為5V J1接到1-2 5V位置上。
//配套實驗程式部分原始碼來源網路，只能參考學習之用，不提供原始碼分析。
//慧凈電子：《做人人都買得起的PIC微控制器精品》
//網址：WWW.HLMCU.COM
//QQ:121350852 
//開發板版本：HL-K18 HJPIC V3.2
//實驗版本：V3.2
//我們的產品收入一部分是贈送給慈善機構的,以免影響到你的善心.大家好,才是真的好（雙方好評）
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
LCD_wrstr("wwm.hlmcu.com"); //WWW.HJMCU.COM
LCD_setxy(2,1);
LCD_wrstr("TEMP:");
LCD_setxy(2,14);
LCD_wrchar(USER_CHAR6);/*在LCD屏上顯示單個預定義字元:℃*/
                             /*K18主板初始化*/
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
