/*4x4動態鍵盤（矩陣鍵盤）實驗*/
//功能簡述：在1個數碼管上顯示按鍵數字
#include <p18cxxx.h>
#include "k18.h"
#include "Delay.h"

const unsigned char LED[16]=
{
	0x3f,     //0
	0x06,     //1   
	0x5b,	  //2
	0x4f,	  //3
	0x66,	  //4
	0x6d,	  //5
	0x7d,	  //6
	0x07,	  //7
	0x7f,	  //8
	0x6f,	  //9
	0x77,	  //A
	0x7C,	  //B
	0x39,	  //C
	0x5E,	  //D
	0x79,	  //E
	0x71,	  //F
};

const unsigned char tbl[4]={0x02,0x04,0x08,0x20};  //掃描訊號

unsigned char key(void)
{
	int i;

	for (i=0;i<=3;i++)
	{
		PORTA=tbl[i];  //掃描訊號

		if		(SW0==0)	return 4*i+1; 	
		else if (SW1==0)	return 4*i+2;
		else if (SW2==0)	return 4*i+3;
		else if (SW3==0)	return 4*i+4;
	}
}

void main(void)
{
	TRISD=0x00;   	//RD設定為輸出 顯示7段用
	TRISA=0x00;  	//RA設定為輸出 鍵盤掃描用
 
	k18_init();/*K18主板初始化*/  
    	COL8=1;	  //使最左邊的7段顯示			 
  	while(1)
  	{    	
		switch (key())
		{
			case 1 :
				PORTD=LED[0];
				break;
			case 2 :
				PORTD=LED[1];
				break;
			case 3 :
				PORTD=LED[2];
				break;
			case 4 :
				PORTD=LED[3];
				break;
			case 5 :
				PORTD=LED[4];
				break;
			case 6 :
				PORTD=LED[5];
				break;
			case 7 :
				PORTD=LED[6];
				break;
			case 8 :
				PORTD=LED[7];
				break;
			case 9 :
				PORTD=LED[8];
				break;
			case 10 :
				PORTD=LED[9];
				break;
			case 11 :
				PORTD=LED[10];
				break;
			case 12 :
				PORTD=LED[11];
				break;
			case 13 :
				PORTD=LED[12];
				break;
			case 14 :
				PORTD=LED[13];
				break;
			case 15 :
				PORTD=LED[14];
				break;
			case 16 :
				PORTD=LED[15];
				break;
			default:
				PORTD=0;
				break;
		} 		  	    	
  	}
}
