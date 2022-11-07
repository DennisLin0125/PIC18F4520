/*******************************************************************/
/*          PIC18 SD卡程式 (18F4520 + SD)  V1.0                 */
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
	printf("             --By DennisLin\r\n\r\n");
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
