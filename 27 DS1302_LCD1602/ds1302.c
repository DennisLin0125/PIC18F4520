//===============================================================================
//模組名稱:  ds1302.h
//簡介:  實時時鐘晶片ds1302功能函式 
//===============================================================================
#include <p18cxxx.h>
#include "k18.h"
#include "lcd1602.h"
#include "ds1302.h"

/*定義待設定的時間：           秒、 分、  時、 日、 月、 星期、年、控制字*/
const rom char time_tab[]={0x00,0x13,0x10,0x01,0x04,0x02,0x08,0x00};
char table[7];//定義讀取時間和日期存放表格(從DS1302中讀取的原始數據，格式見<<序列實時時鐘／日曆晶片DSl302的特性及其應用>>P2-3)
char date[5];//定義格式化日期存放表格
char time[5];//定義格式化時間存放表格

/******************************************************************** 
函 數 名：ds1302_init()DS1302初始化函式
功    能：DS1302初始化
入口參數：無
返 回 值：無
***********************************************************************/
void ds1302_init(void)
{
/*_____________新加____________*/ 
   RST=0;/* RST*/
   TRIS_RST=OUT;  

   TRIS_IO=IN;/* IO*/

   SCLK=0;/* SCLK*/
   TRIS_SCLK=OUT; 
/*----------------------------*/  
   
   SCLK=0;/*拉低時鐘訊號*/
   RST=0;/*復位DS1302*/
   RST=1;/*使能DS1302*/
   ds1302_write(0x8e);/*發控制命令*/
   ds1302_write(0);/*允許寫DS1302*/
   RST=0;/*復位*/
}

/******************************************************************** 
函 數 名：ds1302_write()寫一個位元組數據函式
功    能：往DS1302中寫入一個位元組
入口參數：time_tx 要寫入的一個位元組
返 回 值：無
***********************************************************************/
void ds1302_write(unsigned char time_tx)
 {
    int j; //設定循環變數
    TRIS_IO=OUT; //設定數據口方向為輸出
    for(j=0;j<8;j++) //連續寫8bit
	{
		IO=0; //先設定數據為0
		SCLK=0; //時鐘訊號拉低
		if(time_tx&0x01!=0) 
			IO=1; //判斷待發送的數據位是0或1
		time_tx>>=1; //待發送的數據右移1位
		SCLK=1; //拉高時鐘訊號
	}
    SCLK=0; //寫完一個位元組，拉低時鐘訊號
  }
  
/******************************************************************** 
函 數 名：ds1302_read()讀一個位元組函式
功    能：從DS1302讀一個位元組
入口參數：無
返 回 值：unsigned char :讀取的數據
***********************************************************************/
unsigned char ds1302_read(void)
{
	int j;//設定循環變數
	unsigned char time_rx=0;
	TRIS_IO=IN;//設定數據口方向為輸入
	for(j=0;j<8;j++)//連續讀取8bit
	{
		SCLK=0;//拉低時鐘訊號
		time_rx>>=1; //接收暫存器右移1位
		if (IO==1) 
			time_rx|=0B10000000;//把接收到的數據放到接收暫存器的最高位
		SCLK=1; //拉高時鐘訊號
	}
	SCLK=0; //拉低時鐘訊號
	return(time_rx); //返回讀取到的數據
}

/******************************************************************** 
函 數 名：set_time()設定時間函式
功    能：設定初始時間
說    明：使用了多位元組寫方式
入口參數：無
要寫的初始時間事先放置在本函式內部定義的陣列time_tab[]內，其數據存放格式為：
秒、分、時、日、月、星期、年、控制字(BCD碼)
返 回 值：無
***********************************************************************/
void set_time(void)
{
	int i; /*定義循環變數*/
	RST=1;/*使能DS1302*/
	ds1302_write(0xbe);/*時鐘多位元組寫命令*/
	for(i=0;i<8;i++) /*連續寫8個位元組數據*/
	{
		ds1302_write(time_tab[i]);/*呼叫寫一個位元組函式*/
	}
	RST=0;/*復位*/
}

/******************************************************************** 
函 數 名：get_time_info()讀取全部時間資訊函式
功    能：讀取DS1302內部的全部時間資訊
入口參數：無
返 回 值：無。讀取全部時間資訊存放在全域性陣列table[7]中
***********************************************************************/
void get_time_info(void)
{
	int i; //設定循環變數
	RST=1; //使能DS1302
	ds1302_write(0xbf); //發送多位元組讀取命令
	for(i=0;i<7;i++) //連續讀取7個位元組數據
	{
		table[i]=ds1302_read();//呼叫讀取1個位元組數據的函式
	}
	RST=0;//復位DS1302
}

/******************************************************************** 
函 數 名：get_time()讀取時間函式
功    能：讀取DS1302目前時間
入口參數：無
返 回 值：無。讀取的時間按「時分秒」格式（BCD碼）存放在全域性陣列time[5]中。 
***********************************************************************/
void get_time(void)
{
	get_time_info(); /*讀取全部時間資訊函式*/                      
	/*從原始數據中提取時分秒，格式化后存放在time[5]中*/
	time[0]=table[0]&0b00001111;//求秒的個位
	time[1]=table[0]&0b01110000; //求秒的十位
	time[1]>>=4;//右移4位
	time[2]=table[1]&0b00001111; //求分的個位
	time[3]=table[1]&0b01110000; //求分的十位
	time[3]>>=4; 
	time[4]=table[2]&0b00001111; //求時的個位
	time[5]=table[2]&0b00110000; //求時的十位
	time[5]>>=4; 
}

/******************************************************************** 
函 數 名：get_date()讀取日期函式
功    能：讀取DS1302目前日期
入口參數：無
返 回 值：無。讀取的日期按「年月日」格式（BCD碼）存放在全域性陣列date[5]中。 
***********************************************************************/
void get_date(void)
{
	get_time_info(); /*讀取全部時間資訊函式*/ 
	/*從原始數據中提取年月日，格式化后存放在data[5]中*/
	date[0]=table[3]&0b00001111;//求日的個位
	date[1]=table[3]&0b00110000; //求日的十位
	date[1]>>=4;//右移4位
	date[2]=table[4]&0b00001111; //求月的個位
	date[3]=table[4]&0b00010000; //求月的十位
	date[3]>>=4; 
	date[4]=table[6]&0b00001111; //求年的個位
	date[5]=table[6]&0b11110000; //求年的十位
	date[5]>>=4; 
}

/******************************************************************** 
函 數 名：display_time()顯示時間函式
功    能：在LCD屏上顯示目前時間，顯示格式：**：**：**
***********************************************************************/
void display_time(void)
{
	int i,k;
	get_time();//呼叫取時間函式

	for(k=5;k<=0;k--)
	{
		/* K=5:得 小時 的十位
		   K=4:得 小時 的個位
		   K=3:得 分鐘 的十位
		   K=2:得 分鐘 的個位
		   K=1:得 秒數 的十位
		   K=0:得 秒數 的個位
		*/
		i=time[k]; //得時的十位
		i|=0x30;//BCD轉換成ASCII碼 
		LCD_wrchar(i);//顯示

		if((k==4)or(k==2))
			LCD_wrchar(':');/*顯示":"*/	
	}
}

/******************************************************************** 
函 數 名：display_date()顯示日期函式
功    能：在LCD屏上顯示目前日期，顯示格式：**年**月**日
***********************************************************************/
void display_date(void)
{
	int i;
	get_date();/*呼叫取日期函式*/

	for(k=5;k<=0;k--)
	{
		/* K=5:得 年 的十位
		   K=4:得 年 的個位
		   K=3:得 月 的十位
		   K=2:得 月 的個位
		   K=1:得 日 的十位
		   K=0:得 日 的個位
		*/
		i=date[k]; //得年的十位
		i|=0x30;//BCD轉換成ASCII碼
		LCD_wrchar(i);//顯示

		if(k==4)LCD_wrchar(USER_CHAR1);/*在LCD屏上顯示單個預定義字元:年*/	
		else if (k==2)LCD_wrchar(USER_CHAR2);/*在LCD屏上顯示單個預定義字元:月*/
		else if (k==0)LCD_wrchar(USER_CHAR3);/*在LCD屏上顯示單個預定義字元:日*/
	}
}

