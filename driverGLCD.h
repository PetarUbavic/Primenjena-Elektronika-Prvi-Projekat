#if defined (__dsPIC30F__)
#include <p30fxxxx.h>
#endif

#ifndef GLCD_H
#define GLCD_H

#define PAGE_ADRESS	0xB8	/* Adress base for Page 0 */
#define Y_ADRESS	0x40	/* Adress base for Y0	  bilo 40*/
#define START_LINE	0xC0	/* Adress base for line 0 */
#define DISPLAY_ON	0x3F	/* Turn display on	  */
#define DISPLAY_OFF	0x3E	/* Turn display off	  */

/* General use definitions */
#define RIGHT		0
#define LEFT		1
#define BUSY		0x80

#define FONT_LENGHT 5
#define FONT_LENGHT_BIG 16

#define odnos_pravougaonosti_piksela		1.3

#define output 0//koristi se kod definisanja pravca pina ulazni ili izlazni
#define input 1

#define RF5_1 LATF|=0b0000000000100000;//RST
#define RF5_0 LATF&=0b1111111111011111;

#define RF4_1 LATF|=0b0000000000010000;//E
#define RF4_0 LATF&=0b1111111111101111;

#define RF1_1 LATF|=0b0000000000000010;//RW
#define RF1_0 LATF&=0b1111111111111101;

#define RF0_1 LATF|=0b0000000000000001;//RS
#define RF0_0 LATF&=0b1111111111111110;

#define RB5_1 LATB|=0b0000000000100000;//CS2
#define RB5_0 LATB&=0b1111111111011111;

#define RB4_1 LATB|=0b0000000000010000;//CS1
#define RB4_0 LATB&=0b1111111111101111;


#define Nop() {__asm__ volatile ("nop");}

void SetRST(unsigned char vrednost);
void SetE(unsigned char vrednost);
void SetRW(unsigned char vrednost);
void SetRS(unsigned char vrednost);
void SetCS2(unsigned char vrednost);
void SetCS1(unsigned char vrednost);
void ConfigureLCDPins (void);
void ConfigureLcdData(unsigned char direction);
void SetLcdData(unsigned char vrednost);
unsigned char ReadLcdData(void);
void strobe_data(void);
void LcdInstructionWrite (unsigned char u8Instruction);
void LcdDelay(unsigned int u32Duration);
void LcdWaitBusy (void);
void GoToY(unsigned char y);
void GoToX(unsigned char x);
void GoToXY(unsigned char x,unsigned char y);
void LcdSelectStartline(unsigned char startna_linija);
void LcdSelectSide(unsigned char u8LcdSide);
unsigned char LcdDataRead (void);
void GLCD_LcdInit(void);
void LcdDataWrite (unsigned char u8Data);
void GLCD_ClrScr (void);
void GLCD_FillScr (void);
void GLCD_DisplayPicture (unsigned char *slika);
void LcdSetDot (unsigned char u8Xaxis, unsigned char u8Yaxis);
void LcdResDot (unsigned char u8Xaxis, unsigned char u8Yaxis);
void GLCD_Circle (unsigned char u8CenterX, unsigned char u8CenterY, unsigned char u8Radius);
//crtanje pravougaonika  tacka (0,0) je u ornjem levom uglu,a(128,64) je  u donjem desnom, xorizontalno je x,a vertikalno y
//funkcija trazi gornju levu i donju desnu koordinatu
void GLCD_Rectangle (unsigned char u8Xaxis1,unsigned char u8Yaxis1,unsigned char u8Xaxis2,unsigned char u8Yaxis2);

void GLCD_Clr_Rectangle (unsigned char u8Xaxis1,unsigned char u8Yaxis1,unsigned char u8Xaxis2,unsigned char u8Yaxis2);
void Glcd_PutChar (char AskiKod);
void Glcd_PutCharBig (char AskiKod);
void GLCD_Printf (char *au8Text);
void GLCD_ShowGreed(unsigned char razmak_greeda) ;

#endif

