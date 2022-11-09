/*********************************************************************
 *
 *                           LCD1602.C
 *
 *********************************************************************
 * 檔名: LCD1602.C
 * 描述: 2*16液晶模組驅動程式，應用時只需要根據硬體連線方式作適當修改，在主程式中包含其標頭檔案即可以用幾個簡單的函式實現功能，實現了簡化程式設計
 ********************************************************************/

/*函式實現*/
#include <p18cxxx.h>
#include <stdlib.h>
#include"k18.h"
#include"lcd1602.h"
#include "delay.h"
				
const rom char cgtab[64]={0x08,0x0f,0x12,0x0f,0x0a,0x1f,0x02,0x02,
					0x0f,0x09,0x0f,0x09,0x0f,0x09,0x11,0x00,
					0x1f,0x11,0x11,0x1f,0x11,0x11,0x1f,0x00,
					0x11,0x0a,0x04,0x1f,0x04,0x1f,0x04,0x00,
					0x0e,0x00,0x1f,0x0a,0x0a,0x0a,0x13,0x00,
					0x18,0x18,0x07,0x08,0x08,0x08,0x07,0x00,
					0x04,0x0a,0x15,0x04,0x04,0x04,0x04,0x00,
					0x01,0x03,0x1d,0x15,0x1d,0x03,0x01,0x00}; /*年、月、日、￥、元、℃、↑、小喇叭圖示*/
					

		
/*產生一個LCD模組的使能脈衝*/
/*該函式只在本檔案內使用，不會被其他檔案呼叫，因此放在本檔案的最前面，不在H檔案中聲明了*/
void LCD_E_toggle(void)
{
	LCD_EN=0;
	Nop();
	Nop();
	Nop();
	Nop();
 	LCD_EN=1;
	Nop();
	Nop();
	Nop();
	Nop();
}

void LCD_init(void)
{
   	ADCON1=0x0F;/*所有引腳均設定為數字IO腳*/
   	Delay10Ms(10);/*延時100ms*/
   	TRIS_LCD_RW=0;/*設定微控制器LCD控制引腳全為輸出*/
	TRIS_LCD_RS=0;
	TRIS_LCD_EN=0;
   	LCD_wrcmd(LCD_MODE_STD);/*LCD標準工作模式：8位數據傳送，2行顯示，字元點陣5*7*/
   	LCD_wrcmd(DISP_OFF);/*顯示關閉*/
    	LCD_wrcmd(DISP_CLR);/*清屏*/ 
    /*清屏和游標歸位需要較長的時間*/
   	LCD_wrcmd(CUR_AUTO_R);/*設定游標在文字插入后自動右移*/
   	LCD_wrcmd(DISP_ON	& CUR_OFF & BLINK_OFF);/*顯示開，無游標, 游標不閃爍*/
   	//LCD_wrcmd(DISP_ON	& CUR_ON & BLINK_ON);/*顯示開，游標, 游標閃爍*/
   	CG_Write();/*建立自定義字元塊*/
}

//void LCD_wrcmd(Uchar cmd)/*寫入控制命令*/
void LCD_wrcmd(Uchar cmd)/*寫入控制命令*/
{
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	wait_until_LCDready();
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	TRIS_LCD_DATA=0x00;	/*微控制器的LCD數據口設定為全輸出*/
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_EN=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_RS=0;
	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_RW=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_DATA=cmd;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_EN=1;
   	Nop();/****/
   	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
   	LCD_EN=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
}

void LCD_wrchar(char str)/*寫入要顯示的字元*/
{
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	wait_until_LCDready();
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	TRIS_LCD_DATA=0x00;	/*微控制器的LCD數據口設定為全輸出*/
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_EN=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_RS=1;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_RW=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_DATA=str;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_EN=1;
   	Nop();/****/
   	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
   	LCD_EN=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
}

void LCD_setxy(char x,char y) /*設定顯示位置，行x=1/2,列y=1~16的任意整數*/
{
    	char temp;
    	if(x==1)
  	{
	  	temp=0x80+y-1;
  		LCD_wrcmd(temp);
  	}
 	else
  	{
	  	temp=0xC0+y-1;
  		LCD_wrcmd(temp);
  	}
}


void LCD_wrstr(const rom char *s)/*寫入要顯示的字串*/
{
	for(;*s!='\0';s++)
		LCD_wrchar(*s);
}


void LCD_wrul(unsigned long num)/*寫入要顯示的無符號長整型數*/
{
	char str[11];/*無符號長整型數轉換為字串是10個，所以需要11個單元儲存*/
	int i=0;
	int j=0;
	ultoa(num,str);/*將無符號長整型數轉換為字串*/
	LCD_wrcmd(CUR_AUTO_L);/*設定游標在文字插入后自動左移*/
	while(str[i]!='\0')/*搜索字串結束符*/
	{
		i++;	
	}
	while(i>0)/*顯示前面的有效數字*/
	{
		i--;
		LCD_wrchar(str[i]);
		j++;
	}
	while(j<10)/*往前寫滿10位，也就是前面都寫空格*/
	{
		LCD_wrchar(0x20);	
		j++;
	}
	LCD_wrcmd(CUR_AUTO_R);/*設定游標在文字插入后自動右移*/
}


void LCD_wrlval(unsigned long num,unsigned char bits,unsigned char dp)/*寫入要顯示的長變數*/
{
	char str[11];/*無符號長整型數轉換為字串是10個，所以需要11個單元儲存*/
	int i=0;
	int j=0;
	ultoa(num,str);/*將無符號長整型數轉換為字串*/
	LCD_wrcmd(CUR_AUTO_L);/*設定游標在文字插入后自動左移*/
	while(str[i]!='\0')/*搜索字串結束符*/
	{
		i++;	
	}
	if (i>bits)/*要顯示的數據比規定的顯示位數多，數據顯示溢出*/
	{
		while(j<bits)/*往前寫滿規定的位數，也就是前面都寫空格，直到規定的位數*/
		{
			LCD_wrchar('-');	/*規定的位全部寫-，表示數據溢出*/
			j++;
			if (j==dp) LCD_wrchar('.');/*插入小數點*/
		}
	}
	else
	{
		while(i>0)/*顯示前面的有效數字*/
		{
			i--;
			LCD_wrchar(str[i]);
			j++;
			if (j==dp) LCD_wrchar('.');/*插入小數點*/
		}
		while(j<bits)/*往前寫滿規定的位數，也就是前面都寫空格，直到規定的位數*/
		{
			if (j==dp) 
				LCD_wrchar('.');/*插入小數點*/

			if (j<=dp) 
				LCD_wrchar('0');/*小數點前後補0字元*/
			else 
				LCD_wrchar(0x20);	/*小數點前後補空字元*/

			j++;
		}
	}
	LCD_wrcmd(CUR_AUTO_R);/*設定游標在文字插入后自動右移*/
}


void wait_until_LCDready(void) /*檢測忙標誌，忙則等待*/
{
	LCD_EN=0;/*此句必須加，否則後面RS RW輸出電平后，液晶屏出現游標復位的現象*/
	LCD_RS=0;
	TRIS_LCD_DATA=0x0ff;/*設定微控制器LCD數據引腳全為輸入*/
	LCD_RW=1;
	LCD_EN=1;/*讀狀態的時候，E始終保持高電平即可*/
	Nop();
	Nop();
	Nop();
	Nop();
	while(LCD_BUSY==1);/*LCD忙，則原地等待*/
	LCD_EN=0;
}

void CG_Write(void)/*建立自定義字元塊*/
{
	int i;
	LCD_wrcmd(SET_ADDR_CGRAM);/*字元發生器CGRAM地址設定*/
	for(i=0;i<64;i++)
	{
		LCD_wrchar(cgtab[i]);
	};
}