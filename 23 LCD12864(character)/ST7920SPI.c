/*********************************************************************
 *
 *                          ST7920SPI.C
 *
 *********************************************************************
 * 檔名: ST7920SPI.C
 * 描述: 12864F(ST7920)點陣液晶模組序列模式驅動程式
 ********************************************************************/

/*實驗板配套128x64點陣液晶模組簡介：
背光顏色：黃色
控制器：ST7920
尺寸：93*70mm
字型檔：帶漢字型檔
可以序列，或者並行工作，強烈建議用序列模式工作，接線數量大大減少，而且顯示速度和並行模式完全一致。

工作于序列模式時的引腳定義：
PIN1------------GND，接0V 
PIN2------------VDD，接+5V
PIN3------------不連線 
PIN4------------CS，片選，接18F4520的RA2腳
PIN5------------SID，數據，接18F4520的RA3腳
PIN6------------SCK，脈衝，接18F4520的RA5腳 
PIN7------------NC，不連線
PIN8------------NC，不連線 
PIN9------------NC，不連線
PIN10-----------NC，不連線 
PIN11-----------NC，不連線  
PIN12-----------NC，不連線 
PIN13-----------NC，不連線 
PIN14-----------NC，不連線
PIN15-----------PSB 　並行模式：PSB=1（高電平）；序列模式：PSB=0（低電平），接18F4520的RA1腳，在程式開頭將該腳置0
PIN16 ----------NC，不連線 
PIN17-----------~RST，模組復位（接18F4520的RB3腳，在程式開頭將該腳置1）
PIN18 ----------NC，不連線 
PIN19 ----------LED+ ，背光＋，接+5V （背光源可以直接接5V電源，無需加限流電阻，電流170mA）
PIN20 ----------LED- ，背光－，接GND  

*/


#include <p18cxxx.h>
#include"k18.h"
#include"ST7920SPI.h"

				
void delay(unsigned int n) 
{
	unsigned int i;
	for(i=0; i<n; i++) {;}
}


//序列發送一位元組數據
void SendByte(unsigned char dat)
{
     unsigned char i;
     for(i=0;i<8;i++)
     {
		E_CLK=0;
		Nop();//?
		Nop();//?
		if(dat&0x80)RW_SID=1;else RW_SID=0;
		Nop();//?
		Nop();//?
		E_CLK=1;
		Nop();//?
		Nop();//?
		dat=dat<<1;
		Nop();//?
		Nop();//?
		Nop();//?
     }
}


//序列接收一位元組數據
unsigned char ReceieveByte(void)
{
     unsigned char i,d1,d2;
     for(i=0;i<8;i++)
     {
		E_CLK=0;delay(100);
		E_CLK=1;
		if(RW_SID)d1++;
		d1=d1<<1;
     }
     for(i=0;i<8;i++)
     {
		E_CLK=0;delay(100);
		E_CLK=1;
		if(RW_SID)d2++;
		d2=d2<<1;
     }
     return (d1&0xF0+d2&0x0F);
}


//讀取標誌位BF
unsigned char ReadBF(unsigned char bf)
{
     unsigned char dat;
     SendByte(0xFA);//11111,01,0 RW=1,RS=0
     dat=ReceieveByte();
     if(dat>0x7F)bf=1;else bf=0; //大於7F忙。
     return bf;
}      


//寫控制命令
void SendCMD(unsigned char dat)
{
	//while(ReadBF){;}
	RS_CS=1;
	Nop();//?
	Nop();//?
	SendByte(0xF8);//11111,00,0 RW=0,RS=0   同步標誌
	Nop();//?
	Nop();//?
	SendByte(dat&0xF0);//高四位
	Nop();//?
	Nop();//?
	SendByte((dat&0x0F)<<4);//低四位
	Nop();//?
	Nop();//?
	RS_CS=0;
	Nop();//?
	Nop();//?
}


//寫顯示數據或單位元組字元
void SendDat(unsigned char dat)
{
	//while(ReadBF){;}
	RS_CS=1;
	SendByte(0xFA);//11111,01,0 RW=0,RS=1
	SendByte(dat&0xF0);//高四位
	SendByte((dat&0x0F)<<4);//低四位
	RS_CS=0;
}      
/* 寫漢字到LCD 指定的位置
     x_add顯示RAM的地址
     dat1/dat2顯示漢字編碼
*/
//void display(unsigned char x_add,unsigned char dat1,unsigned char dat2)
//{
//     SendCMD(x_add);//1xxx,xxxx 設定DDRAM 7位地址xxx,xxxx到地址計數器AC
//     SendDat(dat1);
//     SendDat(dat2);
//}

//void PutStr(unsigned char x, unsigned char y, unsigned char *ptr)
//{
// WriteCommand(0x00,0xCD);
// LocateXY(x,y);
// while(*ptr != '\0')
// {
//   WriteData(*ptr);
//   ++ptr;
// } 
//}

void LCD_wrstr(unsigned char x_add,const rom char *s)/*寫入要顯示的字串*/
{
	SendCMD(x_add);//1xxx,xxxx 設定DDRAM 7位地址xxx,xxxx到地址計數器AC
	for(;*s!='\0';s++)SendDat(*s);
}


//初始化 LCM
void initlcm(void)
{
     //RST=0;
     RS_CS=0;
     //PSB=0;/*選擇序列模式*/
     delay(100);
     //RST=1;
     SendCMD(0x30);//功能設定，一次送8位數據，基本指令集
     SendCMD(0x0C);//0000,1100 整體顯示，遊標off，遊標位置off
     SendCMD(0x01);//0000,0001 清DDRAM
     SendCMD(0x02);//0000,0010 DDRAM地址歸位
     SendCMD(0x80);//1000,0000 設定DDRAM 7位地址000，0000到地址計數器AC
	//SendCMD(0x04);//點設定，顯示字元/游標從左到右移位，DDRAM地址加 一
	//SendCMD(0x0F);//顯示設定，開顯示，顯示游標，目前顯示位反白閃動
}





  