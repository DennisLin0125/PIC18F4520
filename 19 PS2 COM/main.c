/*******************************************************************/
/*                 PC鍵盤（PS/2）演示程式  V1.0                     */
/*                                                                 */
/* 說明：時鐘線訊號未使用中斷方式，使本程式具有比較好的通用性，使用者可以將*/
/*       時鐘線改接到任何一個數字引腳                                */
/* 開發平臺: MAPLAB+MCC18                                           */
/*******************************************************************/
//接線方式：時鐘線接RB0,數據線接RB2，串列埠TX1接RC6、RX1接RC7。
//晶振10MHZ 串列埠波特率9600，具體可在UART.H中設定。
//使用串列埠除錯助手（設定為16進位制顯示方式）接收顯示，按下PC鍵盤上一個鍵，顯示通碼，放開顯示斷碼。

#include<p18cxxx.h>
#include"UART/UART.h"
#include<stdio.h>
#include<stdlib.h>
#include<timers.h>
//#include <usart.h>

#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long

#define TRIS_CLK  DDRBbits.RB0
#define CLK PORTBbits.RB0
#define TRIS_DATA  DDRBbits.RB2
#define DATA PORTBbits.RB2


void Delay(uint16 n)/*延時*/
{
	while(n--);
	//asm("nop");
}

void main()
{
	uint8 bits = 0;/*PS2數據幀的位計數器*/
	uint8 REC=0;/*PS2數據幀的記錄暫存器*/
	ADCON1=0b00001111;/*設定所有雙用口為普通數字口*/
	//CMCON=0b00000111;/*關閉所有比較器*/
	INTCON2bits.RBPU=0;/*開啟B口弱上拉*/  
	TRIS_DATA=1;/*微控制器接PC鍵盤數據線、時鐘線的兩個引腳均設定為輸入腳*/
	TRIS_CLK=1;
	ComIni();/*串列埠初始化*/
	
//OpenUSART( USART_TX_INT_ON &	/*允許發送中斷*/
//USART_RX_INT_OFF &				/*禁止接收中斷*/
//USART_ASYNCH_MODE & 			/*非同步模式*/
//USART_EIGHT_BIT &				/*8 位發送接收*/
//USART_BRGH_HIGH,				/*高波特率*/
//25 );/*設定波特率57600,系統時鐘11.0592MHZ*/

//WriteUSART( PORTD ); //write value of PORTD


	Delay(0xffff);

 	while(1)
 		{ 
		while(CLK);/*時鐘線高電平，原地等待*/

		switch ( bits ) /*時鐘線變低，根據PS2數據幀的位計數器的值進行不同的處理*/
			{
			case 0:
    				bits++;
    				break; 
   			case 9: 
     			bits++;
    				break; 
   			case 10: 
     			UartTx(REC);/*通過串列埠發送一個數據幀內容*/
     			bits=0;
    				break; 
			default:
				REC=REC>>1;/*REC循環右移1位*/
				if (DATA==1) REC|=0b10000000;/*讀入數據線數據到REC最高位*/
				bits++;
    				break; 
			}

     	 while(!CLK);/*時鐘線低電平，原地等待*/
		}   
} 