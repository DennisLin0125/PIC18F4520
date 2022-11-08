#include <p18cxxx.h>

#define COL1   PORTAbits.RA1   		
#define TRIS_COL1  DDRAbits.RA1


unsigned char ucLED;

void init();
void delay(unsigned int);

void main(void)
{
	init();
	while(1)
	{
		LATD = ucLED;
		delay(10000);
		if (ucLED == 0x80)
			ucLED = 0x01;
		else
			ucLED <<= 1;
	} 
}

void init()
{
	ADCON1 = 0b00001111;
	TRIS_COL1=0;
	COL1=1;
	TRISD = 0x00;
	LATD = 0x00;
	ucLED = 0b00000001;
}

void delay(unsigned int k)
{
	while(k!=0)
	{
		k--;
	}
}