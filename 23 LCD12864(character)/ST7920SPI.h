/*********************************************************************
 *
 *                           ST7920SPI.h
 *
 *********************************************************************
 * 檔名: ST7920SPI.h
 ********************************************************************/
#ifndef ST7920SPI_h
#define ST7920SPI_h


/*微控制器與12864LCD連線IO定義*/
#define RS_CS    PORTAbits.RA2   		/* 片選輸入端 */
#define TRIS_RS_CS   DDRAbits.RA2

#define RW_SID   PORTAbits.RA3   		/* 序列數據輸入、輸出端 */
#define TRIS_RW_SID  DDRAbits.RA3 

#define E_CLK   PORTAbits.RA5   		/* 同步時鐘輸入端 */
#define TRIS_E_CLK  DDRAbits.RA5 


#define PSB   PORTAbits.RA1   		/* 串並選擇輸入端 */
#define TRIS_PSB  DDRAbits.RA1 

#define RST   PORTBbits.RB3   		/* 復位輸入端 */
#define TRIS_RST  DDRBbits.RB3  

/* 函式原型*/


void delay(unsigned int n);


//序列發送一位元組數據
void SendByte(unsigned char dat);

//序列接收一位元組數據
unsigned char ReceieveByte(void);

//讀取標誌位BF
unsigned char ReadBF(unsigned char bf);
  
//寫控制命令
void SendCMD(unsigned char dat);

//寫顯示數據或單位元組字元
void SendDat(unsigned char dat);

void LCD_wrstr(unsigned char x_add,const rom char *s);/*寫入要顯示的字串*/

//初始化 LCM
void initlcm(void);





#endif
