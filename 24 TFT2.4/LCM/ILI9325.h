#ifndef ILI9325_H
#define ILI9325_H
//============================================================
//根據晶片資料定義
#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		0x0021 // GRAM Vertical Address Set
#define GRAMWR 			0x0022 // memory write
#define GUI_LCM_YMAX 319
#define GUI_LCM_XMAX 239

//=============================================================
//定義TFT彩屏模組介面
#define TFT_RS PORTAbits.RA2	//數據/命令選擇
#define TFT_WR PORTAbits.RA3	//寫
#define TFT_RD PORTAbits.RA5	//讀
#define TFT_CS PORTAbits.RA1	//片選
#define TFT_RST PORTBbits.RB3	//復位

#define TFT_DATA PORTD		//數據口

#define TRIS_TFT_RS DDRAbits.RA2
#define TRIS_TFT_WR DDRAbits.RA3
#define TRIS_TFT_RD DDRAbits.RA5
#define TRIS_TFT_CS DDRAbits.RA1
#define TRIS_TFT_RST DDRBbits.RB3

#define TRIS_TFT_DATA TRISD


//=============================================================
//函式聲明
void ILI9325_initial(void);//TFT初始化
void write_cmd(unsigned char CH,unsigned char CL);//寫命令
void write_data(unsigned char DH,unsigned char DL);//寫數據
void write_data_u16(unsigned int dat);//寫16位數據
void write_cmd_data (unsigned char cmd,unsigned int dat);//寫命令數據
void LCD_setwindow(unsigned char x0,unsigned int y0,unsigned char x1,unsigned int y1);//設定視窗
void LCD_setxy(unsigned char x,unsigned int y);//設定當前顯示座標
void LCD_test();//彩條、單色自測程式


#endif











