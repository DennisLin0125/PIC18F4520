
/*********************************************************************
 *
 *                           main.c
 *
 *********************************************************************
 * 描    述: 紅外遙控解碼程式(數碼管顯示)
 * 解碼值在IR_buff[2]中，當IrOK=1時解碼有效。
 * 用遙控器對準紅外接收頭，按下遙控器按鍵，在數碼管后兩位上就會顯示對應按鍵的編碼
 * 開發板設定：S2的4位全部上撥，其餘採用出廠預設設定。
 * 開發平臺: HL-K18開發板+C18
 ********************************************************************/
 
#include <p18cxxx.h>/*18F系列微控制器標頭檔案*/
#include "k18.h"/*PIC開發板標頭檔案*/
#include "delay.h"/*包含延時函式標頭檔案*/

/*此處為晶振為10時的取值,如用其它頻率的晶振時,要改變相應的取值。*/
#define Imax 18988
#define Imin 10850
#define Inum1 1967
#define Inum2 949
#define Inum3 4069

unsigned char IR_buff[4]={0x00,0x00,0x00,0x00};/*客戶碼低8位，客戶碼高8位，數據碼，數據反碼*/
unsigned char show[2]={0,0};
unsigned char flag_start;/*找到啟動碼標誌*/
unsigned long m,Tc;
unsigned char IrOK;

/*0-F共陰字形碼錶*/
const rom unsigned char sz[]={0x3f  , 0x06 , 0x5b , 0x4f , 0x66 ,
		 0x6d ,0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,
		 0x39 , 0x5e , 0x79 , 0x71 };

void display(void);

void PIC18F_High_isr(void);/*中斷服務函式聲明*/
void PIC18F_Low_isr(void);

#pragma code high_vector_section=0x8
/*高優先順序中斷響應時，會自動跳轉到0x8處*/
/*利用前處理器指令#pragma code來指定後面的程式在ROM中的起始地址為0x08，*/
/*它是告訴聯結器定位到特定的程式碼段，HIGH_INTERRUPT_VECTOR 是該特定程式碼段的段名*/
void high_vector (void)
{
	_asm goto PIC18F_High_isr _endasm/*通過一條跳轉指令(彙編指令），跳轉到中斷服務函式（中斷服務程式）處*/
}

#pragma code low_vector_section=0x18
/*低優先順序中斷響應時，會自動跳轉到0x18處*/
void low_vector (void)
{
	_asm goto PIC18F_Low_isr _endasm
}

#pragma code
/*這條語句不是多餘的，它是告訴聯結器回到預設的程式碼段，*/
/*如果不加的話，聯結器就會傻傻地把後面的程式碼緊跟著上面的程式碼一直放下去。*/
/*而18f4520.lkr檔案里定義了向量區地址最多到0x29，所以如果沒加此句通常會報錯*/


/*-----*/
#pragma interrupt PIC18F_High_isr
/*利用前處理器指令#pragma interrupt來聲明後面的函式是低優先順序中斷服務函式（中斷服務程式），*/
/*注意：關鍵字是interrupt，和低優先順序中斷時不同*/
/*一旦指定後面的函式是低優先順序中斷服務程式，系統在進入該函式時，會自動保護現場，退出前自動恢復現場，*/
/*同時中斷服務程式執行完畢后，會自動返回斷點,*/
/*中斷服務函式前必須加該語句*/
void PIC18F_High_isr (void)
{
	/*INT1解碼程式*/
	/*提取中斷時間間隔時長。TMR0讀：先讀低位元組，後讀高位元組*/
	Tc=TMR0L;
	Tc=TMR0H*256+Tc;
 
	TMR0H=0;/*TMR0置初值,先寫高位元組，后寫低位元組*/
 	TMR0L=0;
 	INTCON3bits.INT1IF=0;/*INT1溢出標誌清零*/
	
	/*尋找啟始碼*/
	if((Tc>Imin)&&(Tc<Imax))
	{ 
		m=0;
		flag_start=1;
		return;
	}
	
	/*找到啟動碼后，進入解碼流程*/ 
	if(flag_start==1)
	{
		if(Tc>Inum1&&Tc<Inum3) 
		{
			IR_buff[m/8]=IR_buff[m/8]>>1|0x80; m++;/*取碼1*/
		}
		if(Tc>Inum2&&Tc<Inum1) 
		{
			IR_buff[m/8]=IR_buff[m/8]>>1; m++;/*取碼0*/
		}
		
		/*取碼完成後判斷碼是否正確*/
		if(m==32) 
		{
			m=0;  
			flag_start=0;
			if(IR_buff[2]==~IR_buff[3]) 
			{
				IrOK=1; 
			}
			else IrOK=0;   
		}
	}
}
	
/*------*/
#pragma interruptlow PIC18F_Low_isr
/*注意：關鍵字是interruptlow，和高優先順序中斷時不同*/
void PIC18F_Low_isr (void)
{
}

void main(void)/*主程式*/
{
	RCONbits.IPEN=1; /*使能中斷優先順序*/
	k18_init();/*HL-K18開發板初始化*/
	m=0;
 	flag_start=0;
  	
 	T0CON=0b00000000;/*TMR0設定：停止執行、16位定時，預分頻1:2*/
 	TMR0H=0;/*TMR0置初值,先寫高位元組，后寫低位元組*/
 	TMR0L=0;
 	T0CONbits.TMR0ON=1;/*啟動TMR0*/ 
 
	INTCON2bits.INTEDG1=0;/*設定外部中斷1觸發邊沿(下降沿)*/
	INTCON3bits.INT1IP=1;/*設定外部中斷1為高優先順序*/
	INTCON3bits.INT1IE=1;/*INT1中斷使能*/
 	INTCONbits.GIE=1;/*全域性中斷允許*/
 
	while(1)
 	{
		if(IrOK==1) 
		{
			show[0]=IR_buff[2] & 0x0F;//取鍵碼的低四位
			show[1]=IR_buff[2] >> 4; //取鍵碼的高四位 
			IrOK=0;
		}
		display();/*在數碼管后兩位上就會顯示對應按鍵的編碼*/
  	}
}

/*在數碼管后兩位上更新數據碼*/
void display(void)
{
	unsigned char wwm=0;
	COL4=0;/*取消千位的位選*/
	PORTD=sz[show[0]];/*送出個位的字形碼*/
	COL1=1;/*個位的位選*/
	delayms(2);/*延時*/
	
	wwm=show[0];
	PORTD=sz[wwm];
	PORTD=sz[0];
	
	
	PORTD=sz[show[0]];/*送出個位的字形碼*/
	COL1=1;/*個位的位選*/
	delayms(2);/*延時*/
	
	
	COL1=0;/*取消個位的位選*/
	PORTD=sz[show[1]];/*送出十位的字形碼*/
	COL2=1;/*十位的位選*/
	delayms(2);/*延時*/
	
	COL2=0;/*取消十位的位選*/
	PORTD=0x00;/*送出百位的字形碼*/
	COL3=1;/*百位的位選*/
	delayms(2);/*延時*/
	
	COL3=0;/*取消百位的位選*/
	PORTD=0x00;/*送出千位的字形碼*/
	COL4=1;/*千位的位選*/
	delayms(2);/*延時*/
}
