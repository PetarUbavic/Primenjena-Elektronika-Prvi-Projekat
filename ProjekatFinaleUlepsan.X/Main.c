#include <stdio.h>
#include "driverGLCD.h"
#include <stdlib.h>
#include "adc.h"
#include "Tajmeri.h"
#include "timer2.h"
#include "timer3.h"
#include "Funkcije.h"

#define DRIVE_A PORTCbits.RC13
#define DRIVE_B PORTCbits.RC14

#define servo LATDbits.LATD8

#define pocetna 500

#define granicaAlkohola 800


_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal 10MHz
_FWDT(WDT_OFF);
_FGS(CODE_PROT_OFF);

const unsigned int AD_Xmin = 220;
const unsigned int AD_Xmax = 3642;
const unsigned int AD_Ymin = 520;
const unsigned int AD_Ymax = 3450;

unsigned int sirovi0,sirovi1;
unsigned int temp0,temp1;

unsigned int X, Y, x_vrednost, y_vrednost;

unsigned int pir, mq3, foto, enpir, enfoto, enmq3;
unsigned int broj1;

unsigned int brojac_ms, stoperica, ms, sekund;
unsigned int brojac_ms3, stoperica3, ms3, sekund3;

int korak = pocetna/5;
int vreme_on = pocetna;
int vreme_off = pocetna;

unsigned int x, n;
unsigned int stanje, taster;

unsigned char zakljucan = 0;
unsigned char tempRX;

int rec[5];

unsigned char tasteri_bmp[1024] = {
   0,  0,  0,  0,  0,  0,  0,240, 16, 16, 16, 16, 16, 16, 16, 16, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,240,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240, 16, 16, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,144, 16, 16, 16, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,240,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0,  0,  0,  0,  0, 
  30, 18, 18, 18,226,  0,  0, 18,146, 78, 32,200, 36, 34,192,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0, 
   0,  0,  0,  0,  0,  0,  0, 32, 48, 40,228,  2,  1,  1,  2,228, 
  40, 48, 32,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,127, 64, 64, 64, 64, 64, 64, 64, 64, 
  65, 65, 65, 65, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 64, 64, 
  64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,127,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63, 32, 32, 
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 47, 40, 40, 40, 40, 47, 
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 63,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128, 
 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128, 
 128,128,128,128,128,128,128,128,128,128,128,128,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,254,  2,  2,  2,  2,  2,  2,  2,  2, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,254,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,252,  4,  4,  4,  4,252,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,130,130,255,128,128, 
   0,  0,126,129,129,129,102,  0,  0,  9, 73, 39, 16,100,146,145, 
  96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  6, 10, 51, 64,128,  0,128, 67, 50, 
  10,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0, 15,  8,  8,  8,  8,  8,  8,  8,  8, 
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 15,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  8,  8, 
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  9, 10,  9,  8,  8, 
   8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 15,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

unsigned char const belo_bmp[1024] = {
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};



void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX=U1RXREG;
    
    if(tempRX != 0)
    {  
       rec[n] = tempRX;
       if(n < 5)
           n++;
       else n=0;
    }
} 

void __attribute__((__interrupt__, no_auto_psv)) _ADCInterrupt(void) 
{   	
	sirovi0=ADCBUF2;
	sirovi1=ADCBUF3;

	temp0=sirovi0; //sirovi0 i sirovi1 su vrednosti sa TouchScreen-a
	temp1=sirovi1; //cuvaju se u temp0 i temp1 kako bi se dalje njima manipulisalo
       
	pir=ADCBUF0;
	mq3=ADCBUF1;
    foto=ADCBUF4;									

    IFS0bits.ADIF = 0;
} 

void __attribute__ ((__interrupt__, no_auto_psv)) _T2Interrupt(void) // svakih 1ms
{
	TMR2 =0;
     ms=1;//fleg za milisekundu ili prekid;potrebno ga je samo resetovati u funkciji

	brojac_ms++;//brojac milisekundi
    stoperica++;//brojac za funkciju Delay_ms

    if (brojac_ms==1000)//sek
        {
          brojac_ms=0;
          sekund=1;//fleg za sekundu
		 } 
	IFS0bits.T2IF = 0;    
}

void __attribute__ ((__interrupt__, no_auto_psv)) _T3Interrupt(void) // svakih 1ms
{
	TMR3 = 0;
    ms3 = 1; //fleg za milisekundu ili prekid ; potrebno ga je samo resetovati u funkciji

	brojac_ms3++; //brojac milisekundi
    stoperica3++; //brojac za funkciju Delay_ms3

    if (brojac_ms3 == 1000) //sek
        {
            brojac_ms3 = 0;
            sekund3 = 1; //fleg za sekundu
		} 
    
	IFS0bits.T3IF = 0;    
}

void Delay_ms (int vreme)//funkcija za kasnjenje po 0.1ms tajmera 2
{
    stoperica = 0;
	while(stoperica < vreme);
}

void Delay_ms3 (int vreme)////funkcija za kasnjenje po 0.1ms tajmera 3
{
	stoperica3 = 0;
	while(stoperica3 < vreme);
}

void Touch_Panel (void)
{
    // vode horizontalni tranzistori
	DRIVE_A = 1;  
	DRIVE_B = 0;
    
    LATCbits.LATC13=1;
    LATCbits.LATC14=0;

	Delay_ms(50); //cekamo jedno vreme da se odradi AD konverzija
				
	// ocitavamo x	
	x_vrednost = temp0;//temp0 je vrednost koji nam daje AD konvertor na BOTTOM pinu		

	// vode vertikalni tranzistori
    LATCbits.LATC13=0;
    LATCbits.LATC14=1;
	DRIVE_A = 0;  
	DRIVE_B = 1;

	Delay_ms(50); //cekamo jedno vreme da se odradi AD konverzija
	// ocitavamo y	
	y_vrednost = temp1;// temp1 je vrednost koji nam daje AD konvertor na LEFT pinu	
	
    //Ako zelimo da nam X i Y koordinate budu kao rezolucija ekrana 128x64 treba skalirati vrednosti x_vrednost i y_vrednost tako da budu u opsegu od 0-128 odnosno 0-64
    //skaliranje X-koordinate
    X = (x_vrednost-161) * 0.03629;

    //vrednosti AD_Xmin i AD_Xmax su minimalne i maksimalne vrednosti koje daje AD konvertor za touch panel.
    //Skaliranje Y-koordinate
	Y = (y_vrednost-500) * 0.020725;
}

unsigned int detektujPrilaz(unsigned int pir)
{
    if(pir > 2000) // PIR na jedinici daje oko 2500-3000 na AD konverziji
        {
            Delay_ms(7000); // sacekati da se smiri odziv PIR-a
            enpir++;
            if(enpir % 2 == 1)
                enfoto = 1; // enable za obasjavanje fotootpornika
                /// dodati watchdog timer ili nesto slicno
            else
                enfoto = 0;
        }
    return enfoto;
}

void servo0() // salje servo na 0 stepeni
{
    servo = 1;
    Delay_ms(5);
    servo = 0;
    Delay_ms(195);    
}
           
void servo90() // salje servo na 90 stepeni
{
    servo = 1;
    Delay_ms(15);
    servo = 0;
    Delay_ms(185);
}

void servo180() // salje servo na 180 stepeni
{
    servo = 1;
    Delay_ms(38);
    servo = 0;
    Delay_ms(162);
}
/*******************/
/*******************/

void Taster5()
{
    if (17 < X  &&  X < 44  &&  47 < Y  &&  Y < 55)
        korak = pocetna / 10; // korak pwm=5%
}

void Taster10()
{
    if (17 < X  &&  X < 44  &&  15 < Y && Y<25)   
        korak = pocetna / 5; // korak pwm=10%                     
}

void Strelica_gore()
{
	if (78 < X  &&  X < 100  &&  39 < Y  &&  Y < 56 )
 {
        if(vreme_on + korak < pocetna * 2) //ako je vreme_on + korak manje od 100% periode
            vreme_on = vreme_on + korak; //povecaj vreme_on za korak
        else 
            vreme_on = pocetna * 2; //ako je vreme_on + korak vece od 100% periode stavi vreme_on = duzini trajanja periode
 }
}

void Strelica_dole()
{
  if (78 < X && X < 100 && 15 < Y && Y < 30)   
	{                                     
       if(vreme_on - korak > 0) //ako je vreme_on - korak vece od 0% periode
            vreme_on = vreme_on - korak; //smanji vreme_on za korak
       else
            vreme_on = 0; //ako je vreme_on - korak manje od 0% periode stavi vreme_on na nulu
	}
}

void Set_pwm()
{
    if(vreme_on == pocetna * 2 + pocetna * 2 / 5) //omogucava pwm da skoci na 100%
    {
       LATFbits.LATF6 = 1; //sa ovog pina skidamo PWM za osciloskop
       LATAbits.LATA11 = 1; //sa ovog pina PWM ide na zujalicu
       vreme_off = 0;
    }
    else
    {
        vreme_off = pocetna * 2 - vreme_on;

        LATFbits.LATF6 = 1;
        LATAbits.LATA11 = 1;
        Delay_ms3(vreme_on);
        
        if(vreme_on != pocetna*2)
        {    
            LATFbits.LATF6 = 0;
            LATAbits.LATA11 = 0;
            Delay_ms3(vreme_off);
        }
    }    
}
/*
 * 
 */


int main(int argc, char** argv) {
	
        for(broj1=0;broj1<60000;broj1++); 
        
        ConfigureADCPins(); //podesi pinove za AD konverziju
        ConfigureLCDPins(); //podesi pinove za LCD
        ConfigureTSPins(); //podesi pinove za TouchScreen
        GLCD_LcdInit(); //inicijalizuj GLCD
        GLCD_ClrScr(); //obrisi GLCD
		initUART1(); //inicijalizacija UART-a
 		ADCinit(); //inicijalizacija AD konvertora
        
		ADCON1bits.ADON=1;//pocetak Ad konverzije 
        
        Init_T2(); //inicijalizuj tajmer 2
        Init_T3(); //inicijalizuj tajmer 3
        
	while(1)
	{ 
        if(rec[0] == 'D' && rec[1] == 'O' && rec[2] == 'R' && rec[3] == 'O' && rec[4] == 'S')
        {
            for(broj1=0; broj1<5; broj1++)
                rec[broj1] = 'A'; // rec[4]='A' zato sto inace non stop menja stanja, te je taster = 1 te je taster = 0;
            taster++; // promenljiva taster sluzi da li se izvrsava PWM deo koda, ili senzorski deo koda
            if(taster % 2 == 0) 
                taster = 0;
            GLCD_ClrScr();
            GLCD_DisplayPicture(belo_bmp);
            GoToXY(35, 8);
            GLCD_Printf("ZAKLJUCAN");
        }
        
        
        if(taster == 1) //ukoliko je taster == 1 radi PWM deo koda
        {
            Touch_Panel();
            GLCD_DisplayPicture(tasteri_bmp);
    
            /*GoToXY(0,6);
            GLCD_Printf ("X=");
            GoToXY(9,6);
            Write_GLCD(X);
    
            GoToXY(0,7);
            GLCD_Printf ("Y=");
            GoToXY(9,7);
            Write_GLCD(Y);*/
                
            Taster5(); //proverava da li je pritisnut "taster" 5%
            Taster10(); //proverava da li je pritisnut "taster" 10%
            Strelica_gore(); //proverava da li je pritisnut "taster" Strelica na gore
            Strelica_dole(); //proverava da li je pritisnut "taster" Strelica na dole
    
            Set_pwm(); //podesava PWM u zavisnosti u pritisnutih tastera
            RS232_putst("Vreme off: ");
            WriteUART1dec2string(vreme_off);
            RS232_putst("   Vreme on: ");
            WriteUART1dec2string(vreme_on);
            RS232_putst("   Korak: ");
            WriteUART1dec2string(korak);
            WriteUART1(13);
        }
        
        if(taster == 0) //ukoliko je taster = 0 radi senzorski deo koda
        {
            if(zakljucan == 0) //promenljiva zakljucan sluzi da se samo jednom prodje kroz deo koda koji se nalazi u ifu, da se servo ne bi non stop vracao na 0
            {
                
                GLCD_ClrScr();
                GoToXY(35, 8);
                GLCD_Printf("ZAKLJUCAN");
                
                
                enpir = 0; //vracam enpir na 0 da ne bi doslo do overflowa
                for(broj1 = 0; broj1 < 30; broj1++)
                    servo0(); //automobil zakljucan - inicijalno stanje
                zakljucan++; //da promenljiva zakljucan vise nije 0
                
                RS232_putst("ZAKLJUCAN");
                WriteUART1(13);
            }
            
            
            if(detektujPrilaz(pir))
            {   
                if(enfoto == 0)
                    GLCD_ClrScr();
                
                for(broj1 = 0; broj1 < 2; broj1++) //ovde se saceka da se odziv PIR senzora vrati na 0
                    Delay_ms(4000);
                enfoto = 1; //flag za dozvolu fotootpornika ide na jedinicu, dozvoljeno obasjavanje
                
                GoToXY(0, 0);
                GLCD_Printf("PIR DETEKTOVAO PRILAZOBASJAJ FOTO");
                RS232_putst("PIR DETEKTOVAO, OBASJAJ FOTO");
                WriteUART1(13);
            }
                
            if(enfoto == 1 && foto < 200)  //enable fotootoprnika dozvoljen i fotootpornik obasjan
            {
                for(broj1 = 0; broj1 < 30; broj1++)
                    servo90(); // automobil otkljucan
                
                
                enfoto = 0; //spustamo flag
                enmq3 = 1; //dizemo flag i dozvoljavamo naredno stanje
                RS232_putst("OBASJAN SAM");
                WriteUART1(13);
                GLCD_ClrScr();
                GoToXY(35, 8);
                GLCD_Printf("OTKLJUCAN");
                GoToXY(0, 0);
                GLCD_Printf("DUVAJ U PRAVCU MQ3-A");
                
            }
            
            if(enmq3 == 1 ) //dozvoljen MQ3
            {
                for(broj1 = 0; broj1 < 15; broj1++) // sacekaj da se vrednost AD konverzije sa MQ3 poveca usled eventualnog prisustva alkohola
                { 
                    Delay_ms(7000);  /////////////////
                    GoToXY(0, 4);
                    Write_GLCD(14-broj1);
                }
                if(mq3 < granicaAlkohola) //nema alkohola
                {
                    for(broj1 = 0; broj1 < 30; broj1++)
                        servo180(); // automobil dozvoljava paljenje
                    RS232_putst("SRECAN PUT");
                    GLCD_ClrScr();
                    GoToXY(35, 100);
                    GLCD_Printf("SRECAN PUT");
                    WriteUART1(13);
                    
                    for(broj1 = 0; broj1 < 5; broj1++) // sacekaj malo da se servo zadrzi na 180 stepeni
                    Delay_ms(7000);
                    zakljucan = 0; //vrati na pocetno stanje
                }
                else //ima alkohola
                {
                    RS232_putst("Ej druze pijan si");
                    GLCD_ClrScr();
                    GoToXY(0, 0);
                    GLCD_Printf("EJ DRUZE PIJAN SI");
                    WriteUART1(13);
                    for(broj1 = 0; broj1 < 5; broj1++) // sacekaj da se stinge procitati ispis
                        Delay_ms(7000);
                    zakljucan = 0; //vrati na pocetno stanje
                }
                enmq3 = 0; //gasimo enable za MQ3
            }
            
    //  WriteUART1dec2string(enpir);
        
        ispisiPir(pir);
        ispisiMq3(mq3);
        ispisiFoto(foto);
       
        //WriteUART(vreme2)*/
		WriteUART1(13);//enter
        
        Delay_ms(2000);
        }
	}//od whilea

    return (EXIT_SUCCESS);
}