/*********************************************************************
 *
 *                           delay.c
 *
 *********************************************************************
 * 描    述: 延時函式
 * 開發平臺: C18
 ********************************************************************/
 /* 說明：所有延時函式在2008-8-08用軟體模擬手段進行了實際測試，證實這些延時函式是準確可靠的。*/
//#include<p18cxxx.h>/*包含18F系列微控制器標頭檔案*/
#include "delay.h"/*包含延時函式標頭檔案*/
#include <delays.h>
#include "k18.h"/*包含HL-K18開發板標頭檔案*/


/*一些固定延時函式*/

/*----------------------------------------------------------------------*/
//下面這組所謂的延時函式實際上並不是真正的函式，是宏定義，具體定義在delay.h中，
//但它的使用和一般函式沒有不一樣的，呼叫方式：delay1us();delay100us();等
/*1uS延時函式*/
/*2uS延時函式*/
/*5uS延時函式*/
/*10uS延時函式*/
/*20uS延時函式*/
/*50uS延時函式*/
/*100uS延時函式*/
/*----------------------------------------------------------------------*/

/*200uS延時函式*/
void delay200us()
{
	Delay10TCYx( FOSC/1000000*200/40);
}
/*500uS延時函式*/
void delay500us()
{
	delay((0.5*FOSC/1000-152)/52);
}
/*1mS延時函式*/
void delay1ms()
{
	delay((1*FOSC/1000-152)/52);
}
/*2mS延時函式*/
void delay2ms()
{
	delay((2*FOSC/1000-152)/52);
}
/*5mS延時函式*/
void delay5ms()
{
	delay((5*FOSC/1000-152)/52);
}
/*10mS延時函式*/
void delay10ms()
{
	delay((10*FOSC/1000-152)/52);
}
/*20mS延時函式*/
void delay20ms()
{
	delay((20*FOSC/1000-152)/52);
}
/*50mS延時函式*/
void delay50ms()
{
	delay((50*FOSC/1000-152)/52);
}
/*100mS延時函式*/
void delay100ms()
{
	delayms(100);
}
/*200mS延時函式*/
void delay200ms()
{
	delayms(200);
}
/*500mS延時函式*/
void delay500ms()
{
	delays(0.5);
}
/*1S延時函式*/
void delay1s()
{
	delays(1);
}
/*2S延時函式*/
void delay2s()
{
	delays(2);
}
/*5S延時函式*/
void delay5s()
{
	delays(5);
}
/*10S延時函式*/
void delay10s()
{
	delays(10);
}



/*一些可變延時函式*/


/*15us--340ms延時函式(FOSC=10M時)*/
/*13us--308ms延時函式(FOSC=11.0592M時)*/
/*7us--170ms延時函式(FOSC=20M時)*/
/*6us--154ms延時函式(FOSC=22.1184M時)*/
/*3us--85ms延時函式(FOSC=40M時)*/
/*延時時間：(52t+152)/FOSC
/*最大延時：3407972/FOSC	
/*最小延時：152/FOSC		
/*設要延時的時間為T(常量，單位為ms),呼叫方式:delay((T*FOSC/1000-152)/52)*/
/*例如要延時的時間為10ms,呼叫方式:delay((10*FOSC/1000-152)/52)*/
void delay(unsigned int t)
{
	unsigned int i;	
	for(i=t;i;i--);
}


/*一個毫秒級可變延時函式*/
/*功  能：實現與參數直接對應的時間（單位為毫秒）的延時*/
/*參  數：範圍1到255*/
/*返回值：無*/
void delayms(unsigned char t)
{
	unsigned char j;	
	for(j=t;j;j--)	
		delay1ms();/*1ms延時*/
}
  

/*一個秒級可變延時函式*/
/*功  能：實現與參數直接對應的時間（單位為秒）的延時*/
/*參  數：範圍0.01到42949672*/
/*返回值：無*/
void delays(float t)
{
	unsigned int j;
	j=t*100;
   	while(j--)
  	{
		delay10ms();/*10ms延時*/
 	}
}
