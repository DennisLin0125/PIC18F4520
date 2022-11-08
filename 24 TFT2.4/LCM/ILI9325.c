/*********************************************************************
 *
 *                ILI9325 TFT彩屏驅動程式
 *
 *********************************************************************
 * 檔名: ILI9325.c
 ********************************************************************/
#include<p18cxxx.h>
//#include <stdio.h>
#include "ILI9325.h"
#include "delay.h"

/*顏色數值:紅色，綠色，藍色，黃色，黑色，白色，天藍色，紫色*/
unsigned int color[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};

//=============================================================
//TFT初始化
//功能：該函式用於初始化TFT彩屏模組。
//入口參數: 無
//出口參數: 無
void ILI9325_initial(void)
{ 
	TFT_CS=1;
	delayms(5);
	TFT_RST=0;
	delayms(5);
	TFT_RST=1;
	delayms(50);//可以適當調整延時，保障穩定顯示
	write_cmd_data(0x0001,0x0100); //源掃瞄設定SS=0, 輸出的移動方向是從S1到S720
	//（源掃瞄設定SS=1, 輸出的移動方向是從S720到S1）
	//SM=0，逐行掃瞄（SM=1，隔行掃瞄）

	write_cmd_data(0x0002,0x0700); //B/C=1、EOR=1：行倒置（B/C=0：幀/場倒置）
	write_cmd_data(0x0003,0x1030); //AM=0，地址在水平方向自動加1
	//I/D[1:0] = 11：水平垂直方向均增加
	//BGR=1:採用BGR格式
	//TRI=0、DFM=*：8位機、兩次數據傳送
	write_cmd_data(0x0004,0x0000); //比例縮放設定：不縮放
	
	//顯示控制
	write_cmd_data(0x0008,0x0207); //設定後邊沿和前沿 
	write_cmd_data(0x0009,0x0000);//設定非顯示區時間間隔ISC[3:0]
	write_cmd_data(0x000A,0x0000); //幀標記功能

	write_cmd_data(0x000C,0x0000);//RGB顯示介面控制1
	write_cmd_data(0x000D,0x0000);//幀標記位置
	write_cmd_data(0x000F,0x0000);//RGB顯示介面控制2
	
	//電源配置
	write_cmd_data(0x0010,0x0000);   
	write_cmd_data(0x0011,0x0007);  
	write_cmd_data(0x0012,0x0000);  
	write_cmd_data(0x0013,0x0000); 
	//vgh 
	write_cmd_data(0x0010,0x1290);   
	write_cmd_data(0x0011,0x0227);
	//delayms(100);
	//vregiout 
	write_cmd_data(0x0012,0x001d); //0x001b
	//delayms(100); 
	//vom amplitude
	write_cmd_data(0x0013,0x1500);
	//delayms(100); 
	//vom H
	write_cmd_data(0x0029,0x0018); 
	write_cmd_data(0x002B,0x000D); 
	
	//伽馬校正
	write_cmd_data(0x0030,0x0004);
	write_cmd_data(0x0031,0x0307);
	write_cmd_data(0x0032,0x0002);//0006
	write_cmd_data(0x0035,0x0206);
	write_cmd_data(0x0036,0x0408);
	write_cmd_data(0x0037,0x0507); 
	write_cmd_data(0x0038,0x0204);//0200
	write_cmd_data(0x0039,0x0707); 
	write_cmd_data(0x003C,0x0405);//0504
	write_cmd_data(0x003D,0x0F02); 
	
	//視窗設定
	write_cmd_data(0x0050,0x0000);//水平起始位置
	write_cmd_data(0x0051,0x00EF);//水平終止位置
	write_cmd_data(0x0052,0x0000);//垂直起始位置
	write_cmd_data(0x0053,0x013F);//垂直終止位置

	write_cmd_data(0x0060,0xA700);//門掃瞄設定，GS=1：從G320掃瞄到G1，320線
	write_cmd_data(0x0061,0x0001); 
	write_cmd_data(0x006A,0x0000);
	//
	write_cmd_data(0x0080,0x0000); 
	write_cmd_data(0x0081,0x0000); 
	write_cmd_data(0x0082,0x0000); 
	write_cmd_data(0x0083,0x0000); 
	write_cmd_data(0x0084,0x0000); 
	write_cmd_data(0x0085,0x0000); 
	//
	write_cmd_data(0x0090,0x0010); 
	write_cmd_data(0x0092,0x0600); 
	write_cmd_data(0x0093,0x0003); 
	write_cmd_data(0x0095,0x0110); 
	write_cmd_data(0x0097,0x0000); 
	write_cmd_data(0x0098,0x0000);
	write_cmd_data(0x0007,0x0133);
	//write_cmd_data(0x0022);		
}


//=============================================================
//寫命令
//功能：寫一個命令到TFT控制器。
//入口參數: CH,CL分別為命令字的高8位和低8位，指定要執行的命令。
//出口參數: 無
void write_cmd(unsigned char CH,unsigned char CL)
{
	TFT_CS=0;
	TFT_RS=0;
	TFT_DATA=CH;
	TFT_WR=0;
	TFT_WR=1;
	TFT_DATA=CL;
	TFT_WR=0;
	TFT_WR=1;
	TFT_CS=1;
}


//===================================================================
//寫數據
//功能：寫一個數據到TFT控制器。
//入口參數: DH,DL分別為數據字的高8位和低8位，指定要寫入的數據。
//出口參數: 無
void write_data(unsigned char DH,unsigned char DL)
{
	TFT_CS=0;
	TFT_RS=1;
	TFT_DATA=DH;
	TFT_WR=0;
	TFT_WR=1;
	TFT_DATA=DL;	
	TFT_WR=0;
	TFT_WR=1;
	TFT_CS=1;
}


//==============================================================
//寫16位數據
//功能： 寫一個數據到TFT控制器。
//入口參數: dat為要寫入的16位數據。
//出口參數: 無
void write_data_u16(unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_data(m,n);
}


//===============================================================
//寫命令數據
//功能： 寫命令數據到TFT控制器。
//入口參數: cmd為要寫入的命令位元組；dat為要寫入的16位數據。
//出口參數: 無
void write_cmd_data (unsigned char cmd,unsigned int dat)
{
	unsigned char m,n;
	m=dat>>8;
	n=dat;
	write_cmd(0x00,cmd);
	write_data(m,n);
}


//===============================================================
//設定視窗
//入口參數: x0 y0,為顯示視窗左上角座標；x1,y1為顯示視窗右下角座標。
//出口參數: 無
//說明：該函式設定TFT模組的顯示視窗。
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1)
{
	write_cmd_data(WINDOW_XADDR_START,x0);//水平起始位置
	write_cmd_data(WINDOW_XADDR_END,x1);//水平終止位置
	write_cmd_data(WINDOW_YADDR_START,y0);//垂直起始位置
	write_cmd_data(WINDOW_YADDR_END,y1);//垂直終止位置
	write_cmd_data(GRAM_XADDR,x0);//設定X座標位置
	write_cmd_data(GRAM_YADDR,y0);//設定Y座標位置
	write_cmd(0x00,0x22);//LCD_WriteCMD(GRAMWR);
}


//===============================================================
//設定當前顯示座標
//入口參數: x,y為目前顯示座標。
//出口參數: 無
//說明：本函式實際上是LCD_setwindow函式的一個特例，顯示視窗為最小，僅是一個畫素點。
void LCD_setxy(unsigned char x,unsigned int y)
{
	LCD_setwindow(x,y,x,y);	
}

//===============================================================
//彩條、單色自測程式
//入口參數: 無。
//出口參數: 無
//說明：在TFT屏上輪流顯示彩條和各種顏色的單色螢幕。
void LCD_test()
{
	unsigned int temp,num;
	unsigned char n,c;

	//顯示彩條	
	LCD_setwindow(0,0,239,319);
	for(n=0;n<8;n++)
	{
	   temp=color[n];										
		for(num=40*240;num>0;num--)
	   	write_data_u16(temp);
	}
	delays(1);

	//顯示單色彩色
	for(c=0;c<8;c++)
	{
		temp = color[c];
		LCD_setwindow(0,0,239,319);
		for(n=0;n<240;n++)
		{
			for(num=0;num<320;num++)
			  write_data_u16(temp);
	 	}
   	delays(1);
	}
}




