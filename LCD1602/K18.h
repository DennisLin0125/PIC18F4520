/*********************************************************************
 *
 *                           K18.H
 *
 *********************************************************************
 * 檔名: K18.H
 ********************************************************************/


#ifndef __k18_h
#define __k18_h
/*變數型別標識的宏定義,通常做法*/
#define uchar unsigned char
#define uint unsigned int
#define OUT 0
#define IN 1

#define Fosc   10000000       		/*定義晶振頻率（單位 Hz）*/

/* K18 引腳定義 */

#define AN   PORTAbits.RA0   		/* AN */
#define TRIS_AN  DDRAbits.RA0

#define COL1   PORTAbits.RA1   		/* COL1 */
#define TRIS_COL1  DDRAbits.RA1

#define COL2   PORTAbits.RA2   		/* COL2 */
#define TRIS_COL2  DDRAbits.RA2

#define COL3   PORTAbits.RA3   		/* COL3 */
#define TRIS_COL3  DDRAbits.RA3

#define COL4   PORTAbits.RA5   		/* COL4 */
#define TRIS_COL4  DDRAbits.RA5

#define COL5   PORTEbits.RE0   		/* COL5 */
#define TRIS_COL5  DDREbits.RE0

#define COL6   PORTEbits.RE1   		/* COL6 */
#define TRIS_COL6  DDREbits.RE1

#define COL7   PORTEbits.RE2   		/* COL7 */
#define TRIS_COL7  DDREbits.RE2

#define COL8   PORTCbits.RC0   		/* COL8 */
#define TRIS_COL8  DDRCbits.RC0

#define B20   PORTCbits.RA4  		/* B20 */
#define TRIS_B20   DDRCbits.RA4

#define BZ   PORTCbits.RC1   		/* BZ */
#define TRIS_BZ  DDRCbits.RC1

#define CS   PORTCbits.RC2   		/* CS */
#define TRIS_CS  DDRCbits.RC2

#define SCK   PORTCbits.RC3   		/* SCK */
#define TRIS_SCK   DDRCbits.RC3

#define SDO   PORTCbits.RC4   		/* SDO */
#define TRIS_SDO   DDRCbits.RC4

#define SDI   PORTCbits.RC5   		/* SDI */
#define TRIS_SDI   DDRCbits.RC5

#define TX1   PORTCbits.RC6   		/* TX1 */
#define TRIS_TX1   DDRCbits.RC6

#define RX1   PORTCbits.RC7   		/* RX1 */
#define TRIS_RX1   DDRCbits.RC7

#define SW0   PORTBbits.RB0   		/* SW0 */
#define TRIS_SW0   DDRBbits.RB0

#define IR   PORTBbits.RB1   		/* IR */
#define TRIS_IR   DDRBbits.RB1

#define SW1   PORTBbits.RB2   		/* SW1 */
#define TRIS_SW1   DDRBbits.RB2

#define SW2   PORTBbits.RB4   		/* SW2 */
#define TRIS_SW2   DDRBbits.RB4

#define SW3   PORTBbits.RB5   		/* SW3 */
#define TRIS_SW3   DDRBbits.RB5


/*為方便使用，部分管腳的多重定義*/

#define M1   COL5   				/* M1 */
#define TRIS_M1  TRIS_COL5

#define M2   COL6   				/* M2 */
#define TRIS_M2  TRIS_COL6

#define M3   COL7   				/* M3 */
#define TRIS_M3  TRIS_COL7

#define M4   COL8   				/* M4 */
#define TRIS_M4  TRIS_COL8

 
/*註：液晶的管腳在LCD1602.H中定義*/

//系統初始化函式
void k18_init(void);


#endif