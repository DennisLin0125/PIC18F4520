/*********************************************************************
 *
 *                           ds18b20.h
 *
 *********************************************************************
 * 檔名: ds18b20.h

 ********************************************************************/
#ifndef __ds18b20_h
#define __ds18b20_h


/*微控制器與18BS20連線數據線定義*/
#define DQ_DIR  DDRAbits.RA4 /*定義18B20D口方向暫存器*/
#define DQ  PORTAbits.RA4/*定義18B20數據埠*/
#define DQ_HIGH() DQ_DIR =1                   /*釋放匯流排*/
#define DQ_LOW() DQ = 0; DQ_DIR = 0           /*下拉匯流排*/

//#define DQ_dir  DDRAbits.RA4 /*定義18B20D口方向暫存器*/


/* 函式原型*/
void reset_ds18b20(void) ;//DS18B20復位
unsigned char ack_ds18b20(void); //DS18B20應答
unsigned int read_ds18b20(void) ; //讀DS18B20            
void write_ds18b20(unsigned int ku); //向DS18B20寫指令         
unsigned int get_temp(void) ;//獲取溫度函式          
void delay_us(unsigned int us);
void delay_ms(unsigned int ms);

       
//unsigned int read_tp(void);                 


/*程式碼命令名稱說明*/
//18B20中使用的是逆序的CRC8 G(x)=8X+5X+4X+1
//#define v_CRC8               0B00110001  //G(x)=X8+X5+X4+1
//#define v_revCRC8            0B10001100

/*----ROM命令----*/
#define     SkipROM         0xCC/*忽略ROM匹配*/
#define     MatchROM        0x55/*符合ROM*/
#define     ReadROM         0x33/*讀ROM*/
#define     SearchROM       0xF0/*搜索ROM*/
#define     AlarmSearch     0xEC/*告警搜索*/

/*----儲存器操作命令----*/
#define     B20Convert      0x44/*Convert T 開始溫度轉換*/
#define     B20WriteScr     0x4E/*Wirte Scratchpad 向RAM中寫數據*/
#define     B20ReadScr      0xBE/*Read Scratchpad 從RAM中讀數據*/
#define     B20CopyScr      0x48/*Copy Scratchpad 將RAM中數據複製到EEPROM中*/
#define     B20RecallEE     0xB8/*Recall EEPROM 與「Copy Scratchpad 命令「功能正好相反*/
#define     B20ReadPower    0xB4/*Read Power Supply 判斷使用的電源模式*/

//設定重複檢測次次數，超出次數則超時
//#define     ReDetectTime    10

#endif











