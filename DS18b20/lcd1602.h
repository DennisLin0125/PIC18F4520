/*********************************************************************
 *
 *                           LCD1602.H
 *
 *********************************************************************
 * 檔名: LCD1602.H
 ********************************************************************/
#ifndef __LCD1602_H
#define __LCD1602_H


/*微控制器與LCD1602連線數據線定義*/
#define LCD_DATA      PORTD
#define TRIS_LCD_DATA TRISD
#define LCD_BUSY  PORTDbits.RD7


#define LCD_RS   PORTAbits.RA2   		/* PORT for RS */
#define TRIS_LCD_RS  DDRAbits.RA2    	/* TRIS for RS */

#define LCD_RW   PORTAbits.RA3   		/* PORT for RW */
#define TRIS_LCD_RW  DDRAbits.RA3    	/* TRIS for RW */

#define LCD_EN    PORTAbits.RA5   		/* PORT for EN */
#define TRIS_LCD_EN   DDRAbits.RA5    	/* TRIS for EN */


/*-------------------1602液晶命令定義-------------------*/

/*初始化命令*/
#define DISP_CLR			0b00000001	/*清顯示,游標復位到第一行首(地址00H）*/
#define CUR_HOME			0b00000010	/*游標復位，游標返回到第一行首*/

/*游標和顯示模式設定*/
#define CUR_AUTO_R			0b00000110	/*設定游標在文字插入后自動右移*/
#define CUR_AUTO_L			0b00000100	/*設定游標在文字插入后自動左移*/
#define DISP_AUTO_R		0b00000111 	/*設定顯示在文字插入后自動右移*/
#define DISP_AUTO_L		0x00000101 	/*設定顯示在文字插入后自動左移*/

/*顯示開關控制*/
#define DISP_ON			0b00001111	/*顯示開*/
#define DISP_OFF			0b00001011	/*顯示關*/
#define CUR_ON			0b00001111	/*游標開*/
#define CUR_OFF			0b00001101	/*游標關*/
#define BLINK_ON			0b00001111	/*游標閃爍開*/
#define BLINK_OFF			0b00001110	/*游標閃爍關*/

/*游標或顯示移位*/
#define CUR_SHIFT_L		0b00010000	/*游標左移*/
#define CUR_SHIFT_R		0b00010100	/*游標右移*/
#define DISP_SHIFT_L		0b00011000	/*顯示左移*/
#define DISP_SHIFT_R		0b00011100	/*顯示右移*/


/*工作模式設定*/
#define LCD_MODE_STD		0x38		/*1602標準工作模式：8位數據傳送，2行顯示，字元點陣5*7*/


/*字元發生器RAM地址設定*/
#define SET_ADDR_CGRAM			0x40	/*設定CGRAM地址*/

/*數據儲存器地址設定*/
#define SET_ADDR_DDRAM			0x80	/*設定DDRAM地址*/

/*自定義字元*/
#define USER_CHAR1				0x00/*自定義字元1:年*/
#define USER_CHAR2				0x01/*自定義字元2:月*/
#define USER_CHAR3				0x02/*自定義字元3:日*/
#define USER_CHAR4				0x03/*自定義字元4:￥*/
#define USER_CHAR5				0x04/*自定義字元5:元*/
#define USER_CHAR6				0x05/*自定義字元6:℃*/
#define USER_CHAR7				0x06/*自定義字元7:↑*/
#define USER_CHAR8				0x07/*自定義字元8:小喇叭圖示*/

/* 函式原型*/
void LCD_init(void)			;/*初始化*/
void wait_until_LCDready(void)	;/*檢測忙標誌，忙則等待*/
void LCD_wrcmd(unsigned char cmd)		;/*寫入控制命令*/
void LCD_setxy(char x,char y)	;/*設定顯示位置，行x=1/2,列y=1~16的任意整數*/
void LCD_wrchar(char str)		;/*寫入要顯示的字元*/
void LCD_wrstr(const rom char *s);/*寫入要顯示的字串常量，該函式相當於C18 庫中的putrsXLCD函式，從程式儲存器寫一個字串到LCD*/
void LCD_wrul(unsigned long num);/*寫入要顯示的無符號長整型數*/
void LCD_wrlval(unsigned long num,unsigned char bits,unsigned char dp);/*寫入要顯示的長變數*/
void CG_Write(void);/*建立自定義字元塊*/


#endif
