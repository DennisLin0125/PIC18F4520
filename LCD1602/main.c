//實驗注意事項1：請一定要把  RA2 RA3 RA5 分別接到  RS RW EN位置上
//實驗注意事項2：如果想程式自己跑，可以斷開P22 P7 中的 1 VPP跳線帽。
//實驗注意事項3：電壓為5V J1接到1-2 5V位置上。
/*1602液晶屏顯示實驗*/
#include <p18cxxx.h>
#include "k18.h"
#include "lcd1602.h"
void main(void)
{
k18_init(); 
LCD_init();
LCD_setxy(1,1);
LCD_wrstr("-WWW.HJMCU.COM-");/*顯示本站網地址*/
LCD_setxy(2,1);
LCD_wrstr("A");/*顯示單個字元A*/
LCD_wrstr("b");/*顯示單個字元b*/
LCD_wrstr("7");/*顯示單個數字字元7*/

/*顯示自定義字元*/
LCD_setxy(2,9);
LCD_wrchar(USER_CHAR1);		
LCD_wrchar(USER_CHAR2);
LCD_wrchar(USER_CHAR3);	
LCD_wrchar(USER_CHAR4);	
LCD_wrchar(USER_CHAR5);	
LCD_wrchar(USER_CHAR6);	
LCD_wrchar(USER_CHAR7);	
LCD_wrchar(USER_CHAR8);


while(1);

}
