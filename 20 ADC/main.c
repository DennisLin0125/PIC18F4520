/*AD轉換實驗，RAO做為模擬輸入通道，用螺絲刀旋動可調電位器RP1，點陣管最左邊一列8個LED顯示的8位二進制數會在11111111和00000000之間變化，11111111表示輸入的模擬電壓為最大值5V，00000000
表示輸入的模擬電壓為最小值0V*/
/*實驗前，請先在開發板P3座3、4針之間(AD)插入短路帽*/
#include <p18cxxx.h>
#include "k18.h"
#include <delays.h>
int result;

/*函式申明*/
void PORT_init(void);             
void ADC_init(void); 

void main(void)
{ 
	PORT_init(); /*呼叫埠初始化函式*/
	ADC_init(); /*呼叫ADC初始化函式*/
  	while(1)
  	{
	  	ADCON0bits.GO=1; /*開啟AD轉換過程*/
		while( ADCON0bits.GO ); /*等待AD轉換完成*/
		PORTD=ADRESH; /*轉換結果在8位LED上顯示*/
	}
}

/*初始化函式*/
void PORT_init(void)               
{
	TRIS_AN=IN; /*設定RA0為輸入*/
	COL8=1; /*選通點陣管的最左邊第一列LED，點陣管的最左邊一列LED作為顯示LED*/
	TRIS_COL8=OUT;  
	TRISD=0X00; /*設定D口全為輸出*/
}

void ADC_init(void)   
{ 
	/*對AD轉換1器進行配置*/
	ADCON0=0x01; /*選擇RA0通道，AD 模組使能*/
  	ADCON1=0x00; /*參考電壓為系統VDD和GND，所有通道均為模擬輸入*/ 
    ADCON2=0x09; /*轉換結果左對齊，AD 採集時間=2TAD，系統時鐘Fosc/8*/
  	Delay10TCYx(5); /*延時50個機器週期*/
}

