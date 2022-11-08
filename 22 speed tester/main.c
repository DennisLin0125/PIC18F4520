/*******************************************************************/
/*                      光電數字轉速錶演示程式                      */
/*                                                                 */
/* 描述：在1602液晶中顯示測量得到的轉速                              */ 
/* 開發板設定：開發板上的RP1逆時針旋轉到底，                          */
/* 光電開關的4個引腳用4根杜邦線和開發板P3的4個引腳同名端相連           */
/* 用1根杜邦線連線下述插針對：RC2-AN                                 */
/* 開發平臺: HL-K18+MCC18 
//直流電機、光電開關需要自己接線
//本實驗注意事項：直流電機啟動電流較大，最好用外部的DC5V電源供電，
//如果用電腦USB供電可能完成不了實驗
//如果一定要用電腦USB供電，電機啟動時要手動轉一下，才能啟動電機，否測會澆壞學習板。 
//本實驗動手能力較強，接線時一定要小心，否測會燒壞光電管，還有開發板
//如果因接錯線燒壞配件，開發板的，不在保修範圍內，請你一定要小心接線。                                         */
/*******************************************************************/
//實驗注意事項1：請一定要把  RA2 RA3 RA5 分別接到  RS RW EN位置上
//實驗注意事項2：如果想程式自己跑，可以斷開P22 P7 中的 1 VPP跳線帽。
//實驗注意事項3：電壓為5V J1接到1-2 5V位置上。
//配套實驗程式部分原始碼來源網路，只能參考學習之用，不提供原始碼分析。
//慧凈電子：《做人人都買得起的PIC微控制器精品》
//網址：WWW.HLMCU.COM
//QQ:121350852 
//開發板版本：HL-K18 HJPIC V3.2
//實驗版本：V3.2
//我們的產品收入一部分是贈送給慈善機構的,以免影響到你的善心.大家好,才是真的好（雙方好評）
//本實驗直流電機啟動電流較大，請另用3V電壓單獨給贈送的直流電機供電，這樣微控制器才能穩定工作。
#include <p18F4520.h>
#include "k18.h"
#include "lcd1602.h"

/*當配置位CCP2MX 置1 時， CCP2 與RC1 複用；而當CCP2MX 清零時， CCP2 與RB3 複用*/

#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0 

#define alnico_number 1 /*定義測量園盤上測速磁鋼的個數（霍爾感測器）或測速孔的個數（光電感測器），本例程為1，可根據實際情況修改此值*/

/*---中斷源及其優先順序說明---*/
/*TIMER3作為顯示數據重新整理定時器，具有中斷低優先順序；*/
/*TIMER1作為CCP1的時鐘源，具有中斷高優先順序；*/
/*CCP1具有中斷高優先順序*/

/*---硬體連線---*/
/*速度感測器接K18主板的P3插座，速度感測器訊號從RC2 AN引腳輸入*/


struct TIMER_STRUCT
{
unsigned int Interval;/*定時器3時間間隔計數器，當Interval累計到250，也就是到S時，Enable就被置1*/
unsigned char Enable;/*時間到標記，每當Enable=1時，LCD上的數據就被重新整理1次*/
};
struct TIMER_STRUCT Timer1S;/*定義1S LCD重新整理定時器，用於儲存中間結果（Interval）和最終結果（Enable）*/


struct CAPTURE_STRUCT
{
unsigned char Flag;/*捕捉是否完成標記*/
unsigned char Pointer;/*指示已捕捉到第幾個下降沿，捕捉到第1個下降沿時，定時器1清0並啟動，捕捉到第2個下降沿時，定時器1的值被記錄，捕捉任務完成*/
unsigned long Data;/*儲存完整的捕捉數據*/
};
struct CAPTURE_STRUCT MyTMR1;/*定義捕捉工作暫存器，用於儲存中間結果（Pointer）和最終結果（Flag、LowData、HighData）*/


unsigned char High_TMR1;/*由於被測脈衝週期較長時，TIMER1的16位計數範圍還是欠大，因此增補High_TMR1作為TIMER1的16-23位，此時總的計數範圍16777216*/

void PIC18F_High_isr (void);
void PIC18F_Low_isr (void);
#pragma code high_vector_section=0x8
void high_vector (void){
_asm goto PIC18F_High_isr _endasm
}
#pragma code low_vector_section=0x18
void low_vector (void){
_asm goto PIC18F_Low_isr _endasm
}
#pragma code

/*---高優先順序中斷服務程式---*/
#pragma interrupt PIC18F_High_isr
void PIC18F_High_isr (void)
{
if(TRUE==PIR1bits.TMR1IF)/*判斷是否TMR1中斷*/
	{
	PIR1bits.TMR1IF=FALSE;/*清TMR1中斷標記*/
	High_TMR1++;/*TMR1增補高16-23位計數器+1*/
	}

if(TRUE==PIR1bits.CCP1IF)/*判斷是否CCP1中斷*/
	{
	PIR1bits.CCP1IF=FALSE;/*清CCP1中斷標記*/
	if(FALSE==MyTMR1.Flag)/*---捕捉已完成的時，跳過---*/
		{
		if(0==MyTMR1.Pointer)
			{		/*現在捕捉到的是第1個下降沿*/
			MyTMR1.Pointer++;/*下降沿捕捉數+1*/
			TMR1L=0;/*TMR1清0*/
			TMR1H=0;
			High_TMR1=0;/*TMR1增補高16-23位計數器清0*/
			T1CONbits.TMR1ON=TRUE;/*啟動TMR1*/
			}
		else
			{		/*現在捕捉到的是第2個下降沿*/
			T1CONbits.TMR1ON=FALSE;/*關閉TMR1*/
		
			MyTMR1.Data=High_TMR1;/*High_TMR1、CCPR1H、CCPR1L合併爲32位數*/
			MyTMR1.Data<<=8;
			MyTMR1.Data|=CCPR1H;
			MyTMR1.Data<<=8;
			MyTMR1.Data|=CCPR1L;

			MyTMR1.Pointer=0;/*下降沿捕捉數清0，為下次測量做好準備*/			
			MyTMR1.Flag=TRUE;/*標記捕捉已經完成*/
			}
		}
	}
}
/*---低優先順序中斷服務程式---*/
#pragma interruptlow PIC18F_Low_isr
void PIC18F_Low_isr (void)
{
if(TRUE==PIR2bits.TMR3IF)/*判斷是否TMR3中斷*/
	{
	PIR2bits.TMR3IF=FALSE;/*清TMR3中斷標記*/
	TMR3H=(65536-11962)/256;/*TMR3置初值*/
	TMR3L=(65536-11962)%256;
	Timer1S.Interval++;	
	if(250==Timer1S.Interval)
		{
		Timer1S.Interval=0;
		Timer1S.Enable=TRUE;/*標記LCD重新整理時間到*/
		}
	}
}

void main(void)
{
	unsigned long speed;/*暫存器定義*/
		
	LCD_init();/*LCD屏初始化*/
	k18_init(); /*HL-K18主板初始化*/
	
	COL8=1;/*讓直流電機高速旋轉*/

	LCD_setxy(1,1);/*界面顯示*/
	LCD_wrstr("Rotate Speed:");

	MyTMR1.Pointer=0;/*各暫存器置初值*/
	MyTMR1.Flag=FALSE;
	MyTMR1.Data=0;
	High_TMR1=0;
	Timer1S.Interval=0;
	Timer1S.Enable=FALSE;

	TRIS_CCP1=IN;/*RC2 AN引腳配置為輸入引腳*/

	CCP1CON=0x04;/*設定捕捉模式：每個時鐘的下降沿捕捉*/

	T3CONbits.T3CCP1=0;/*Timer1作為 AN 的時鐘源*/
	T3CONbits.T3CCP2=0;

	PIR1bits.CCP1IF=FALSE;/*捕捉標誌清零*/ 
	PIE1bits.CCP1IE=TRUE;/*允許捕捉中斷*/ 
	IPR1bits.CCP1IP=TRUE;/*高優先順序*/ 
 
	T1CON=0x00;/*TMR1設定：16位定時，預分頻為 1:1，F=FOSC/4*/
	//TMR1L=0;
	//TMR1H=0;
	PIR1bits.TMR1IF=FALSE;/*TMR1溢出標誌清零*/ 
	PIE1bits.TMR1IE=TRUE;/*允許定時器溢出中斷*/
	IPR1bits.TMR1IP=TRUE;/*高優先順序*/
	//T1CONbits1.TMR1ON=TRUE;/*TMR1開始計時*/


	T3CON=0x00;/*TMR3設定：16位定時，預分頻為 1:1，F=FOSC*/
	TMR3H=(65536-11965)/256;/*TMR3置初值*/
	TMR3L=(65536-11965)%256;
	PIR2bits.TMR3IF=FALSE;	/*TMR3溢出標誌清零*/ 
	PIE2bits.TMR3IE=TRUE;/*允許TMR3溢出中斷*/ 
	IPR2bits.TMR3IP=FALSE;/*低優先順序*/
	T3CONbits.TMR3ON=TRUE;/*啟動TMR3*/ 
	INTCONbits.GIEH=TRUE;/*開啟全域性中斷允許*/
	INTCONbits.GIEL=TRUE;
	RCONbits.IPEN=TRUE; 

	while(1)
	{
		while(FALSE==Timer1S.Enable);/*LCD重新整理時間未到時，原地等待*/
		if(TRUE==MyTMR1.Flag)
		{		/*---捕捉已完成---*/
			speed=15*Fosc/alnico_number;/*計算出轉速（轉/分鐘）*/
			speed/=MyTMR1.Data;
			LCD_setxy(2,1);
			LCD_wrstr("                ");/*清除LCD屏第二行所有內容*/
			LCD_setxy(2,10); 
			LCD_wrul(speed);/*在LCD顯示轉速*/
			LCD_setxy(2,12);
			LCD_wrstr("RPM");
		}	
		else
		{
			LCD_setxy(2,1);
			LCD_wrstr("   too slow!    ");
		}
		MyTMR1.Flag=FALSE;	/*標記捕捉未成功，為下次測量做準備*/
		Timer1S.Enable=FALSE;/*標記LCD重新整理時間未到*/
	}
}