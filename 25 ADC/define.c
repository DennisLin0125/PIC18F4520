#include <p18cxxx.h>
#include "define.h"

const unsigned char DB[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //0~9

const unsigned char ScanSeg[]={0x02,0x04,0x08,0x20}; //七段掃描

void display (uchar* a)
{	
	uchar i;
	for (i=0;i<=3;i++)
	{
		if (i==2)
		{
			PORTD=DB[*(a+i)]|0x80;  //顯示dot
		}
		else
		{
			PORTD=DB[*(a+i)];  //將a陣列資料給七段顯示
		}

		PORTA=*(ScanSeg+i);    //選擇哪個七段要亮
		DelayMs(2);       //延遲2ms		
	}	
}

void ADCinit(void)
{
	CLR(TRISA,(bit7+bit6+bit5+bit4+bit3+bit2+bit1));
	SET(TRISA,bit0);	
	
	CLR(TRISD,(bit7+bit6+bit5+bit4+bit3+bit2+bit1+bit0));
	
	SET(ADCON0,bit0);
	SET(ADCON1,(bit3+bit2+bit1));
	SET(ADCON2,(bit7+bit2+bit0));

	Delay10TCYx(5);
}

uint get_ad(void)
{
	uint adval=0,i;
	float adcVol=0;
	uint sum=0;
	for (i=1;i<=30;i++)    
	{
		ADCON0bits.GO=1;
		while (ADCON0bits.GO);
		adval=ADRESH;
		adval=(adval<<8)|ADRESL;
		sum+=adval;
	}
	sum/=30;       //消除ADC的誤差值
	adcVol=(sum/1023.0)*5.0;  //將0~1023 轉成0~5V
	adcVol*=(1.0+(30000.0/7500.0));  // 知道分壓求VCC
	return (adcVol*100);			
}

void DelayMs(uchar ms)
{
	uint j;
	j=ms*190;
	while(j--);
}
