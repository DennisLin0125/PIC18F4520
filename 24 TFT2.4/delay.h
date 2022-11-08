
/*********************************************************************
 *
 *                           delay.h
 *
 *********************************************************************
 * 檔名: delay.h
 ********************************************************************/

#ifndef   DELAY_H
#define   DELAY_H
//配套實驗程式部分原始碼來源網路，只能參考學習之用，不提供原始碼分析。
//試用原始碼，請試用24小時後刪除。


/*一些固定延時函式*/


/*-----------------------------------------------------------------------------------------*/
/*1uS延時函式*/
/*2uS延時函式*/
/*5uS延時函式*/
/*10uS延時函式*/
/*20uS延時函式*/
/*50uS延時函式*/
/*100uS延時函式*/
/*FOSC=10、11.0592、20、22.1184、40MHZ時，適用*/
/*其他晶振頻率時，要調整Nop();語句的句數，Nop();語句的句數=FOSC（單位MHZ）*延時時間（單位uS）/4 */
#if FOSC==10000000
	#define delay1us()   {Nop();Nop();Nop();}//3T
	#define delay2us()   {Nop();Nop();Nop();Nop();Nop();}//5T
	#define delay5us()   {Delay10TCYx(1);Nop();Nop();Nop();}//13T
	#define delay10us()  {Delay10TCYx(2);Nop();Nop();Nop();Nop();Nop();}//25T
	#define delay20us()  {Delay10TCYx(5);}//50T
	#define delay50us()  {Delay10TCYx(12);Nop();Nop();Nop();Nop();Nop();}//125T
	#define delay100us() {Delay10TCYx(25);}//250T
#elif FOSC==11059200
	#define delay1us()   {Nop();Nop();Nop();}//3T
	#define delay2us()   {Nop();Nop();Nop();Nop();Nop();Nop();}//6T
	#define delay5us()   {Delay10TCYx(1);Nop();Nop();Nop();Nop();}//14T
	#define delay10us()  {Delay10TCYx(2);Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();}//28T
	#define delay20us()  {Delay10TCYx(5);Nop();Nop();Nop();Nop();Nop();}//55T
	#define delay50us()  {Delay10TCYx(13);Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();}//138T
	#define delay100us() {Delay10TCYx(27);Nop();Nop();Nop();Nop();Nop();Nop();}//276T
#elif FOSC==20000000
	#define delay1us()   {Nop();Nop();Nop();	Nop();Nop();}//5T
	#define delay2us()   {Delay10TCYx(1);}//10T
	#define delay5us()   {Delay10TCYx(2);Nop();Nop();Nop();Nop();Nop();}//25T
	#define delay10us()  {Delay10TCYx(5);}//50T
	#define delay20us()  {Delay10TCYx(10);}//100T
	#define delay50us()  {Delay10TCYx(25);}//250T
	#define delay100us() {Delay10TCYx(50);}//500T
#elif FOSC==22118400
	#define delay1us()   {Nop();Nop();Nop();	Nop();Nop();Nop();}//6T
	#define delay2us()   {Delay10TCYx(1);Nop();}//11T
	#define delay5us()   {Delay10TCYx(2);Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();}//28T
	#define delay10us()  {Delay10TCYx(5);Nop();Nop();Nop();Nop();Nop();}//55T
	#define delay20us()  {Delay10TCYx(11);}//110T
	#define delay50us()  {Delay10TCYx(27);Nop();Nop();Nop();Nop();Nop();Nop();}//276T
	#define delay100us() {Delay10TCYx(55);Nop();Nop();Nop();}//553T
#elif FOSC==40000000
	#define delay1us()   {Delay10TCYx(1);}//10T
	#define delay2us()   {Delay10TCYx(2);}//20T
	#define delay5us()   {Delay10TCYx(5);}//50T
	#define delay10us()  {Delay10TCYx(10);}//100T
	#define delay20us()  {Delay10TCYx(20);}//200T
	#define delay50us()  {Delay10TCYx(50);}//500T
	#define delay100us() {Delay10TCYx(100);}//1000T
#endif
/*-----------------------------------------------------------------------------------------*/

void delay200us();/*200uS延時函式*/
void delay500us();/*500uS延時函式*/
void delay1ms();/*1mS延時函式*/
void delay2ms();/*2mS延時函式*/
void delay5ms();/*5mS延時函式*/
void delay10ms();/*10mS延時函式*/
void delay20ms();/*20mS延時函式*/
void delay50ms();/*50mS延時函式*/
void delay100ms();/*100mS延時函式*/
void delay200ms();/*200mS延時函式*/
void delay500ms();/*500mS延時函式*/
void delay1s();/*1S延時函式*/
void delay2s();/*2S延時函式*/
void delay5s();/*5S延時函式*/
void delay10s();/*10S延時函式*/



/*一些可變延時函式*/

void delay(unsigned int t);/*15us--85ms延時函式(FOSC在10M到40M之間時)*/
void delayms(unsigned char t);/*一個毫秒級可變延時函式*/
void delays(float t);/*一個秒級可變延時函式*/



#endif