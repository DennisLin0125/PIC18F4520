//實驗注意事項1：請關了S2數碼管開關，打開S4第4位，S3關掉。
//實驗注意事項2：如果想程式自己跑，可以斷開P22 P7 中的 1 VPP跳線帽。
//實驗注意事項3：電壓為5V J1接到1-2 5V位置上。
//配套實驗程式部分原始碼來源網路，只能參考學習之用，不提供原始碼分析。
//慧凈電子：《做人人都買得起的PIC微控制器精品》
//網址：WWW.HLMCU.COM
//QQ:121350852 
//開發板版本：HL-K18 HJPIC V3.2
//實驗版本：V3.2
//我們的產品收入一部分是贈送給慈善機構的,以免影響到你的善心.大家好,才是真的好（雙方好評）
/*******************************************************************/
/*          PIC18 SD卡演示程式 (18F4520 + SD)  V1.0                 */
/*******************************************************************/
#include<p18cxxx.h>/*head files*/
#include"MMC_SD/MMC_SD.h" 
#include"FAT/FAT.h"
#include"UART/UART.h"
#include<stdio.h>
#include<stdlib.h>
#include<timers.h>
#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long
extern uint16 SectorsPerClust;/*每簇扇區數*/
extern uint16 FirstDataSector;/*第一個數據扇區數*/
extern uint8  FAT32_Enable;

struct FileInfoStruct FileInfo;/*檔案資訊*/


#pragma udata directive
#pragma udata BUFFER
unsigned char tmpBuf[512];
#pragma udata

void Delay(uint16 n)/*延時*/
{
	while(n--);
	//asm("nop");
}

void main()
{
	uint8 retry = 0;
	uint8  ls = 2;
	uint8 i;				/*循環變數*/
	ComIni();
	
/*串列埠初始化*/
//OpenUSART( USART_TX_INT_ON &	/*允許發送中斷*/
//USART_RX_INT_OFF &				/*禁止接收中斷*/
//USART_ASYNCH_MODE & 			/*非同步模式*/
//USART_EIGHT_BIT &				/*8 位發送接收*/
//USART_BRGH_HIGH,				/*高波特率*/
//25 );/*設定波特率57600,系統時鐘11.0592MHZ*/

//WriteUSART( PORTD ); //write value of PORTD



	Delay(0xffff);
	printf("*****************************************************\r\n");
	printf("          SD CARD V1.0\r\n");
	printf("             --By 慧凈電子HL-K18\r\n\r\n");
	printf("*****************************************************\r\n");
	printf("\r\n");
	
	while(MMC_SD_Init())/*初始化SD卡*/
	{
		retry++;
		if(retry>20)
		{
			printf("ERROR: SD card initialize fail!\r\n");
			while(1);
	
		}
	}
	printf("SD card initialize OK!\r\n");
	
	printf("SD card capacity is: %ld MB\r\n",MMC_SD_ReadCapacity()/1024/1024);/*通過串列埠列印出SD卡容量*/

	if(FAT_Init())/* 初始化檔案系統 支援FAT16和FAT32 */	
	{
		printf("ERROR: FAT file system initialize fail!\r\n");
		while(1);
	}
	printf("FAT file system initialize OK!");
	
	
	
	if (FAT32_Enable)
	{
	 printf(" -- FAT32\r\n");/*通過串列埠列印出FAT32或FAT16*/
	}
	else
	{
	 printf(" -- FAT16\r\n");
    } 


/*------------------------------------------------------------------------*/
/*寫實驗時，請將該部分的每條語句前面的//去掉，讀實驗時，請將該部分的每條語句前面的//加上*/
tmpBuf[0]='a';
tmpBuf[1]='j';
tmpBuf[2]='d';
tmpBuf[3]='z';

MMC_SD_WriteSingleBlock(512, tmpBuf);//寫一個扇區
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*讀實驗時，請將該部分的每條語句前面的//去掉，寫實驗時，請將該部分的每條語句前面的//加上*/
//MMC_SD_ReadSingleBlock(512, tmpBuf);//讀一個扇區

//for(i=0;i<4;i++)/*通過串列埠顯示檔案內容*/
//{
//	UartTx(tmpBuf[i]);
//}
/*-------------------------------------------------------------------------*/



	while(1);
}