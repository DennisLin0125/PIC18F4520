/*********************************************************************
 *
 *                           K18.c
 *
 *********************************************************************
 * 描    述: K18主板初始化函式
 * 開發平臺: HL-K18開發板+C18
 ********************************************************************/
#include <p18cxxx.h>/*包含18F系列微控制器標頭檔案*/ 
#include "k18.h"/*包含K18開發板標頭檔案*/
#include "LCM/ILI9325.h"/*包含ILI9325標頭檔案*/
//配套實驗程式部分原始碼來源網路，只能參考學習之用，不提供原始碼分析。
//試用原始碼，請試用24小時後刪除。

/*K18主板初始化函式*/
void k18_init(void)
{
  	ADCON1=0b00001111;/*設定所有雙用口為普通數字口*/
  	CMCON=0b00000111;/*關閉所有比較器*/
  	INTCON2bits.RBPU=0;/*開啟B口弱上拉*/
  	
  	/* K18 引腳方向、輸出初值定義 */

	TRIS_AN=IN;/* AN*/

	COL1=0;TRIS_COL1=OUT;/*COL1*/
	COL2=0;TRIS_COL2=OUT;/*COL2*/
	COL3=0;TRIS_COL3=OUT;/*COL3*/
	COL4=0;TRIS_COL4=OUT;/*COL4*/
	COL5=0;TRIS_COL5=OUT;/*COL5*/
	COL6=0;TRIS_COL6=OUT;/*COL6*/
	COL7=0;TRIS_COL7=OUT;/*COL7*/
	COL8=0;TRIS_COL8=OUT;/*COL8*/
	BZ=0;TRIS_BZ=OUT;/*BZ*/
	CS=1;TRIS_CS=OUT;/*SD卡使不能*/
	PORTD=0;TRISD=0;/*PORTD*/
	
	TRIS_IR=IN;/*IR*/
	TRIS_SW0=IN;/*SW0*/
	TRIS_SW1=IN;/*SW1*/
	TRIS_SW2=IN;/*SW2*/
	TRIS_SW3=IN;/*SW3*/
	
	/* TFT模組驅動引腳方向、輸出初值定義 */
	TRIS_TFT_RS=OUT;
	TRIS_TFT_CS=OUT;
	TRIS_TFT_WR=OUT;
	TRIS_TFT_RD=IN;
	TRIS_TFT_RST=OUT;
	TFT_DATA=0;TRIS_TFT_DATA=0;/*TFT模組數據埠*/
    
}


