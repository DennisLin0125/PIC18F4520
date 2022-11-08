/*******************************************************************/
/*          SD diriver for  MP3 Player                             */
/*                                                                 */
/* Platform   : MAPLAB + MCC18                                     */
/*              optimize : Enable All                              */
/* Author     : bozai(Zhang Qibo)                                  */
/* E-mail     : sudazqb@163.com                                    */
/* MSN        : zhangqibo_1985@hotmail.com                         */
/* Date       : 2007-12-01                                         */
/*******************************************************************/
/*  2007-12-01: migrate from AVR platform to PIC                   */
/*  2007-10-21: Rewrite some function, now only suply 4 functions  */
/*  2007-10-18: Adjust some time & retry count for compatibility   */
/*              consideration                                      */
/*  2007-06-16: After reading the spec. in detail, I found some    */
/*              of the code don't meet the spec., that is after    */
/*              the last SPI transaction, it need an extra 8 CLK   */
/*              to finish it's work                                */
/*  2007-05-04: add read capacity function                         */
/*  2007-04-21:                                                    */
/*  Enable some code incase that when SD reset                     */
/*  faild program can't jump the loop                              */
/*******************************************************************/

#ifndef __MMC_SD_h__
#define __MMC_SD_h__

#include<p18cxxx.h>

#define uint8  unsigned char
#define  int8    signed char
#define uint16 unsigned int
#define  int16   signed int
#define uint32 unsigned long
#define  int32   signed long

#define MMC_SD_CS			PORTCbits.RC2
#define MMC_SD_CS_TRIS		TRISCbits.TRISC2

#define MMC_SD_SCK			PORTCbits.RC3
#define MMC_SD_SCK_TRIS		TRISCbits.TRISC3

#define MMC_SD_MOSI			PORTCbits.RC5
#define MMC_SD_MOSI_TRIS	TRISCbits.TRISC5

#define MMC_SD_MISO			PORTCbits.RC4
#define MMC_SD_MISO_TRIS	TRISCbits.TRISC4

/****************************************************************/

#define MMC_SD_PORT_INI  {\
							MMC_SD_CS=1;\
							MMC_SD_SCK=1;\
							MMC_SD_MOSI=1;\
							MMC_SD_MISO=1;\
							\
							MMC_SD_CS_TRIS =0;\
							MMC_SD_SCK_TRIS =0;\
							MMC_SD_MOSI_TRIS =0;\
							MMC_SD_MISO_TRIS =1;\
						}							

#define SPI_CS_Assert   MMC_SD_CS=0 
#define SPI_CS_Deassert MMC_SD_CS=1


uint8 MMC_SD_Init(void);
uint8 MMC_SD_ReadSingleBlock(uint32 sector, uint8* buffer);
uint8 MMC_SD_WriteSingleBlock(uint32 sector, uint8* buffer);
uint32 MMC_SD_ReadCapacity(void);

#endif
