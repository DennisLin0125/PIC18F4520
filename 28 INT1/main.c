#include <p18cxxx.h>/*18F系列微控制器標頭檔案*/
#include "k18.h"/*開發板標頭檔案*/
#include "delay.h"/*延時標頭檔案*/
#include "buzzer.h"/*蜂鳴器標頭檔案*/

/*0-F共陰字形碼錶*/
const rom uchar sz[17]={0x3f  , 0x06 , 0x5b , 0x4f , 0x66 ,
		 0x6d ,0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,
		 0x39 , 0x5e , 0x79 , 0x71 , 0x00};

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

/*---高優先順序中斷服務程式---*/
#pragma interrupt PIC18F_High_isr
/*利用前處理器指令#pragma interrupt來聲明後面的函式是高優先順序中斷服務函式（中斷服務程式），*/
/*注意：關鍵字是interrupt，和低優先順序中斷時不同*/
/*一旦指定後面的函式是低優先順序中斷服務程式，系統在進入該函式時，會自動保護現場，退出前自動恢復現場，*/
/*同時中斷服務程式執行完畢后，會自動返回斷點,*/
/*中斷服務函式前必須加該語句*/
void PIC18F_High_isr (void)
{
/*如果只有一個同級中斷源被使能：*/
/*1、執行中斷服務語句部分*/
/*2、清除中斷標記*/
	di(50);/*蜂鳴器發出嘀的一聲*/
	INTCONbits.INT0IF=0;/*清除中斷標記*/


/*如果有多個同級中斷源被使能：*/
/*1、用查詢法確定是哪個中斷源提出了中斷請求*/
/*2、確定是哪個中斷源提出了中斷請求后，執行中斷服務語句部分*/
/*3、最後清除該中斷源中斷標誌*/
}

/*---低優先順序中斷服務程式---*/
#pragma interruptlow PIC18F_Low_isr
/*注意：關鍵字是interruptlow，和高優先順序中斷時不同*/
void PIC18F_Low_isr (void)
{
	da(50);/*蜂鳴器發出答的一聲*/
	INTCON3bits.INT2IF=0;/*清除中斷標記*/
}


void main(void)/*主函式*/
{
	uchar num;/*區域性變數定義*/
	INTCONbits.GIE=0;/*關全域性中斷*/
	
	k18_init();/*K18主板初始化*/  
	COL1=1;/*選中4位數碼管的最右邊一位，並使SW0-SW3可作為獨立按鍵使用*/
	PORTD=sz[16];/*開機后，4位數碼管的最右邊一位無顯示*/
	
	RCONbits.IPEN=1;/*使能中斷優先順序*/

	INTCON2bits.INTEDG0=0;/*設定外部中斷觸發邊沿(下降沿)*/
	INTCONbits.INT0IF=0;/*清除中斷標誌*/  
 	INTCONbits.INT0IE=1;/*使能中斷*/
	
	INTCON2bits.INTEDG2=0;/*設定外部中斷觸發邊沿(下降沿)*/
	INTCON3bits.INT2IF=0;/*清除中斷標誌*/
	INTCON3bits.INT2IE=1;/*使能中斷*/
	INTCON3bits.INT2IP=0;/*設定優先順序*/	
	
	INTCONbits.GIE=1;/*開全域性中斷*/
	INTCONbits.GIEL=1;/*開全域性中斷*/

	/*這裡寫主程式語句*/
	while(1)
	{
		for(num=0;num<=0x0f;num++)
		{
			PORTD=sz[num];/*送出欲顯示數的字形碼*/
			delay(1);/*延時1秒*/
		}
	}
}



	

	
	





