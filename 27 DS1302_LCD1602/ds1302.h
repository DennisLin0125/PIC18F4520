/*********************************************************************
 *
 *                           DS1302.H
 *
 *********************************************************************
 * 檔名: DS1302.H
 ********************************************************************/
#ifndef   DS1302_H
#define   DS1302_H

#define RST   PORTEbits.RE0   		/* RST定義DS1302的復位口線*/
#define TRIS_RST  DDREbits.RE0

#define IO   PORTEbits.RE1   		/* IO定義DS1302的數據口線*/
#define TRIS_IO  DDREbits.RE1

#define SCLK   PORTEbits.RE2   		/* SCLK定義DS1302的時鐘口線*/
#define TRIS_SCLK  DDREbits.RE2


void ds1302_init(void);//DS1302初始化函式
void ds1302_write(unsigned char time_tx);//寫一個位元組數據函式
unsigned char ds1302_read(void);//讀一個位元組函式
void set_time(void);//設定時間函式
void get_time_info(void);//讀取全部時間資訊函式
void get_time(void);//讀取時間函式
void get_date(void);//讀取日期函式
void display_date(void);//顯示日期函式
void display_time(void);//顯示時間函式


#endif

