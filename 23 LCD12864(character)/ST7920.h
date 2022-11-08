/*********************************************************************
 *
 *                           ST7920.h
 *
 *********************************************************************
 * 檔名: ST7920.h
 ********************************************************************/
#ifndef ST7920_h
#define ST7920_h


/*微控制器與12864LCD連線IO定義*/
#define LCD_DB PORTD
#define  LCD_RS  PORTAbits.RA5                      //命令/數據選擇
#define  LCD_RW  PORTAbits.RA4                      //讀/寫選擇
#define  LCD_E   PORTAbits.RA3                      //使能
#define  LCD_RET  PORTAbits.RA0                      //復位


/* 函式原型*/
void Delay(INT16U j);
void Ini_SYSCLK(void);
void Ini_PORT(void);
void Ini_LCD(void);
void LCD_P_Ready(void);
void LCD_P_W_Command(INT8U Command);
void LCD_P_W_Data(INT8U Data);


#endif