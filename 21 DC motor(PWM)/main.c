/*                   直流電機PWM調速實驗參考程式                     */
/*                                                                 */
/* 描述：每隔2秒，直流電機的轉速會增加，增加到最高速后變停轉，然後重新開始。*/
/* 如果沒有直流電機，也可以觀察點陣管左邊第1列的亮度變化，             */
/* 每隔2秒，點陣管的亮度會增加，增加到最高后熄滅，然後重新開始。    */ 
/* 接線方式：用1根杜邦線連線下述插針對：RC2-COL8                      */

#include <p18cxxx.h>
#include "k18.h"
#include "delay.h"

void main(void)
{
	k18_init();/*HL-K18主板初始化*/
	DDRCbits.RC2=0;
	PORTD=0XFF;

	
	CCP1CON=0B00001100;/*定義CCP為PWM調製方式*/
	PR2=0xFF;/*定義週期暫存器*/
	CCPR1L=0X00;/*定義脈寬初值*/ 				
	
	T2CON=0B00000101;/*定義定時器TMR2工作方式：後分頻比1：1，預分頻比1：4，啟用TMR2*/

	while(1)
	{
		CCPR1L=CCPR1L+32;/*脈寬改變*/
		delay(2);/*延時2S*/
	}

}

