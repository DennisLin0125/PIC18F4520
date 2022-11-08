/*使用定時器0實現蜂鳴器發出5KHZ聲音*/
#include <p18cxxx.h>/*18F系列微控制器標頭檔案*/
#include "k18.h"/*HL-K18開發板標頭檔案*/

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
/*利用前處理器指令#pragma interrupt來聲明後面的函式是低優先順序中斷服務函式（中斷服務程式），*/
/*注意：關鍵字是interrupt，和低優先順序中斷時不同*/
/*一旦指定後面的函式是低優先順序中斷服務程式，系統在進入該函式時，會自動保護現場，退出前自動恢復現場，*/
/*同時中斷服務程式執行完畢后，會自動返回斷點,*/
/*中斷服務函式前必須加該語句*/
void PIC18F_High_isr (void)
{
	TMR0L=20;/*TMR0重新置初值*/
	BZ=~BZ;/*s輸出取反*/
	INTCONbits.TMR0IF=0;	/*TMR0溢出標誌清零*/ 
}

/*---低優先順序中斷服務程式---*/
#pragma interruptlow PIC18F_Low_isr
/*注意：關鍵字是interruptlow，和高優先順序中斷時不同*/
void PIC18F_Low_isr (void)
{

}


void main(void)/*主函式*/
{
	INTCONbits.GIE=0;/*關全域性中斷*/
	RCONbits.IPEN=1; /*使能中斷優先順序*/
	k18_init();/*K18主板初始化*/  

	T0CON=0b01001000;/*TMR0設定：停止執行、8位定時，F=FOSC，無預分頻*/

	
	TMR0L=20;/*TMR0置初值*/
		
	INTCONbits.TMR0IF=0;/*Timer0溢出標誌清零*/ 
	INTCONbits.TMR0IE=1;/*允許Timer0溢出中斷*/ 
	INTCON2bits.TMR0IP=1;/*Timer0中斷為高優先順序*/
	
	T0CONbits.TMR0ON=1;/*啟動TMR0*/ 
	INTCONbits.GIE=1;/*開全域性中斷*/
	
	while(1)
	{
					/*現在主程式核心部分是空的*/
	}
}



	

	
	





