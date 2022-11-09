/*DS1302數字鐘實驗*/
#include <p18cxxx.h>
#include "k18.h"
#include "lcd1602.h"
#include"ds1302.h"

void main(void)
{
    k18_init();/*HL-K18主板初始化*/
    LCD_init();
    LCD_setxy(2,10);
    ds1302_init(); /*呼叫DS1302初始化函式*/
    set_time(); /*呼叫設定時間函式*/

    while(1)
    {
        LCD_setxy(1,1);
        display_date();/*顯示年月日*/
        LCD_setxy(2,1);
        display_time();/*顯示時分秒*/
    }
}


	

	
	