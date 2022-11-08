#define uchar unsigned char
#define uint unsigned int

#define bit0  (1<<0)
#define bit1  (1<<1)	
#define bit2  (1<<2)
#define bit3  (1<<3)
#define bit4  (1<<4)	
#define bit5  (1<<5)
#define bit6  (1<<6)
#define bit7  (1<<7)

#define SET(reg,b) reg|=b
#define CLR(reg,b) reg&=~b
#define TGL(reg,b) reg^=b

uint get_ad(void);
void display (uchar* a);
void ADCinit(void);
void DelayMs(uchar ms);
