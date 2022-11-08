#include"UART.h"


void ComIni(void)
{
	SPBRG = MY_SPBRG;	/*波特率暫存器置值，設定波特率*/
	TXSTAbits.SYNC = 0;/*非同步模式*/
	RCSTAbits.SPEN  = 1;/*使能串列埠（將RX和TX引腳配置為串列埠引腳）*/
	TXSTAbits.BRGH  = SPEED;/*速度模式，具體看標頭檔案定義*/
	TXSTAbits.TXEN  = 1;/*發送使能*/
	RCSTAbits.CREN  = 1;/*接收使能*/
	DDRCbits.RC6 = 0;
	DDRCbits.RC7 = 1;
}

void UartTx(unsigned char ch)
{
	while(! TXSTAbits.TRMT);
	TXREG = ch;
	while(! PIR1bits.TXIF); 
}

unsigned char UartRx()
{
	while(! PIR1bits.RCIF);
	return RCREG;
}

void PrintStr(const rom char * str)
{
	while(*str)
	{
		if(*str == '\n')UartTx(0x0d);
		UartTx(*str);
		str++;
	}
}
