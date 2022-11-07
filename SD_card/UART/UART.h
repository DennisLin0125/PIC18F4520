#ifndef __UART_H__
#define __UART_H__

#include <p18cxxx.h>


#define XTAL 10000000UL		/*系統時鐘10MHZ*/
#define BAUD 9600L		/*設定波特率115200*/
#define SPEED 1			/*1為高速，0為低速*/
#define MY_SPBRG (XTAL/64*(SPEED*3+1)/BAUD-1)/*計算波特率暫存器設定值*/



extern void ComIni(void);
extern void UartTx(unsigned char ch);
extern unsigned char UartRx(void);
extern void PrintStr(const rom char * str);
//it will automaticlly send 0x0d before send 0x0a ('\n')

#endif

