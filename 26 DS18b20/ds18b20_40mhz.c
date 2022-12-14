//===============================================================================
//模組名稱:  DS18B20.c
//簡介:  溫度感測器DS18B20功能函式 

//===============================================================================
#include <p18cxxx.h>
#include <delays.h>
#include"k18.h"
#include "ds18b20.h"

//**********************************************************************
// reset_ds18b20:   DS18B20復位
//功   能  ----DS18B20復位
//入口參數:  ----無
//出口參數:  ----無
//**********************************************************************
void reset_ds18b20(void) 
{ 
     unsigned int i;
     DQ_LOW(); /*主機拉匯流排至低電平*/
     /*=====晶振改變時，修改下句=====*/
	Delay100TCYx(48);/*保持至少480us*/
	DQ_HIGH(); 
} 

 //**********************************************************************
 // ack_ds18b20:  等待DS18B20應答
 //功     能  ----等待DS18B20應答
 //入口參數:  ----無
 //出口參數:  ----0: 沒有DS18B20器件或主機復位失敗
 //              1: 發現DS18B20器件
 //**********************************************************************
unsigned char ack_ds18b20(void) 
{ 
     unsigned char Value=1;
     DQ_HIGH(); /*釋放匯流排等電阻拉高匯流排*/
     while(DQ==1); 
     while(DQ==0)
          Value=0; 
     /*接收到應答訊號*/
     /*=====晶振改變時，修改下句=====*/
     Delay10TCYx(20);/*延時20us*/ 
     if (Value) 
          return 0;
     return 1;
} 

 //**********************************************************************
 //read_ds18b20:  讀DS18B20
 //功     能  ----讀DS18B20
 //入口參數:  ----無 
 //出口參數:  ----DS18B20內部表示的溫度值，雙位元組，16進位制，FC90～0000～07D0
 //**********************************************************************
unsigned int read_ds18b20(void)              
{ 
     int i=0;
     unsigned int u=0;
     for (i=0;i<16;i++)
     {   
          DQ_LOW(); 
          /*=====晶振改變時，修改下句=====*/
          Delay10TCYx(2);/*從高拉至低電平,產生讀時間隙,2us*/
          u>>=1;
          DQ_HIGH(); 
          Delay10TCYx(5);/*此句必須要加，否則由於剛設定為輸入，訊號不穩定，立即讀入時會是錯誤值*/
          if(DQ) 
               u|=0x8000;/*讀入位*/
          /*=====晶振改變時，修改下句=====*/
          Delay10TCYx(56);//56us 
     }
     return (u);
}

 //**********************************************************************
 //write_ds18b20:  向DS18B20寫指令
 //功     能  ----向DS18B20寫指令
 //入口參數:  ----DS18B20操作指令
 //出口參數:  ----無
 //**********************************************************************
void write_ds18b20(unsigned int ku)          
{  
     int i=0;
     for (i=0;i<8;i++)
     { 
          DQ_LOW(); 
          /*=====晶振改變時，修改下句=====*/
          Delay10TCYx(2);/*從高拉至低電平,產生寫時間隙,2us*/
          DQ =ku&0x01;/*最低位移出*/
          /*=====晶振改變時，修改下句=====*/
          Delay10TCYx(50);/*60us，除錯時發現不能大於65us，否則正常工作*/ 
          DQ_HIGH(); /*釋放匯流排*/
          Delay10TCYx(2);/*2us*/
          ku>>=1;
     }
}
 
//**********************************************************************
//get_temp:  讀DS18B20溫度
//功     能  ----讀DS18B20溫度
//入口參數:  ----無
//出口參數:  ----實際溫度的100倍，若為負溫，高兩位置1；其它不變。
//**********************************************************************
unsigned int get_temp(void)                 
{   
     int i;
     unsigned int tp,flag;
     flag=1;
     reset_ds18b20();//復位
     ack_ds18b20();//從機應答
     write_ds18b20(SkipROM);//忽略ROM匹配
     write_ds18b20(B20Convert);//發送溫度轉化命令
     /*-----------------------------------*/
     /*中間沒有進行時間的延時，因此下面這段程式碼得到的溫度數據並不是本次轉換的結果，而是上次轉換的結果*/
     /*在主次序中應該進行兩次測量之間的延時*/
     reset_ds18b20();//復位
     ack_ds18b20();//從機應答
     write_ds18b20(SkipROM);//忽略ROM匹配
     write_ds18b20(B20ReadScr);//發送讀溫度命令
     Delay10TCYx(150);/*150us*/ 
     tp=read_ds18b20();/*讀出溫度*/
     /*-----------------------------------*/         
     if(tp>0x0fff) /*判斷是否為負溫，若是負溫，取反加一，乘6.25*/
     {      
          tp=~tp;
          tp++;
          tp=(unsigned int)(tp*6.25);
          tp|=0xC000;
     }
     else
          tp=(unsigned int)(tp*6.25);/*是正溫*/
     return(tp);
}



