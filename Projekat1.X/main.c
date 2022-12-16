#include<p30fxxxx.h>
#include <stdlib.h>
#include "tajmer2.h"
#include "driverGLCD.h"
#include "adc.h"


//_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal//
_FOSC(CSW_ON_FSCM_OFF & HS3_PLL4);
_FWDT(WDT_OFF);
_FGS(CODE_PROT_OFF);

unsigned int X, Y,x_vrednost, y_vrednost;


//const unsigned int ADC_THRESHOLD = 900; 
const unsigned int AD_Xmin =220;
const unsigned int AD_Xmax =3642;
const unsigned int AD_Ymin =520;
const unsigned int AD_Ymax =3450;

unsigned int sirovi0,sirovi1;
unsigned int broj,broj1,broj2,temp0,temp1; 

//#define DRIVE_A PORTBbits.RB10
//#define DRIVE_B PORTCbits.RC13
#define DRIVE_A PORTCbits.RC13
#define DRIVE_B PORTCbits.RC14

void ConfigureTSPins(void)
{
	//ADPCFGbits.PCFG10=1;
	//ADPCFGbits.PCFG7=digital;

	//TRISBbits.TRISB10=0;
	TRISCbits.TRISC13=0;
    TRISCbits.TRISC14=0;
	
	//LATCbits.LATC14=0;
	//LATCbits.LATC13=0;
}

// ------------------------------------------------------  
// GLCD Picture name: tasteri.bmp            
// GLCD Model: KS0108 128x64            
// ------------------------------------------------------  

unsigned char const tasteri_bmp[1024] = {
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



void initUART1(void)
{
    U1BRG=0x0015;//ovim odredjujemo baudrate

    U1MODEbits.ALTIO=0;//biramo koje pinove koristimo za komunikaciju osnovne ili alternativne

    IEC0bits.U1RXIE=1;//omogucavamo rx1 interupt

    U1STA&=0xfffc;

    U1MODEbits.UARTEN=1;//ukljucujemo ovaj modul

    U1STAbits.UTXEN=1;//ukljucujemo predaju
}

void __attribute__((__interrupt__)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
   // tempRX=U1RXREG;

} 

void WriteUART1(unsigned int data)
{
	  while(!U1STAbits.TRMT);

    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

/***********************************************************************
* Ime funkcije      : WriteUART1dec2string                     		   *
* Opis              : Funkcija salje 4-cifrene brojeve (cifru po cifru)*
* Parameteri        : unsigned int data-podatak koji zelimo poslati    *
* Povratna vrednost : Nema                                             *
************************************************************************/
void WriteUART1dec2string(unsigned int data)
{
	unsigned char temp;

	temp=data/1000;
	WriteUART1(temp+'0');
	data=data-temp*1000;
	temp=data/100;
	WriteUART1(temp+'0');
	data=data-temp*100;
	temp=data/10;
	WriteUART1(temp+'0');
	data=data-temp*10;
	WriteUART1(data+'0');
}


unsigned int brojac_ms,stoperica,ms,sekund;

/*******************************************************************
//funkcija za kasnjenje u milisekundama
*********************************************************************/
void Delay_ms (int vreme)//funkcija za kasnjenje u milisekundama
	{
		stoperica = 0;
		while(stoperica < vreme);
	}



void __attribute__ ((__interrupt__)) _T2Interrupt(void) // svakih 1ms
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

void Delay(unsigned int N)
{
	unsigned int i;
	for(i=0;i<N;i++);
}

int vreme=0;
void Touch_Panel (void)
{
// vode horizontalni tranzistori
	DRIVE_A = 1;  
	DRIVE_B = 0;
    
     LATCbits.LATC13=1;
     LATCbits.LATC14=0;

	Delay(500); //cekamo jedno vreme da se odradi AD konverzija
				
	// ocitavamo x	
	x_vrednost = temp0;//temp0 je vrednost koji nam daje AD konvertor na BOTTOM pinu		

	// vode vertikalni tranzistori
     LATCbits.LATC13=0;
     LATCbits.LATC14=1;
	DRIVE_A = 0;  
	DRIVE_B = 1;

	Delay(500); //cekamo jedno vreme da se odradi AD konverzija
	
	// ocitavamo y	
	y_vrednost = temp1;// temp1 je vrednost koji nam daje AD konvertor na LEFT pinu	
	
//Ako želimo da nam X i Y koordinate budu kao rezolucija ekrana 128x64 treba skalirati vrednosti x_vrednost i y_vrednost tako da budu u opsegu od 0-128 odnosno 0-64
//skaliranje x-koordinate

    X=(x_vrednost-161)*0.03629;



//X= ((x_vrednost-AD_Xmin)/(AD_Xmax-AD_Xmin))*128;	
//vrednosti AD_Xmin i AD_Xmax su minimalne i maksimalne vrednosti koje daje AD konvertor za touch panel.


//Skaliranje Y-koordinate
	Y= ((y_vrednost-500)*0.020725);

//	Y= ((y_vrednost-AD_Ymin)/(AD_Ymax-AD_Ymin))*64;
}

void Taster5()
{
    if ((17<X)&&(X<44)&& (47<Y)&&(Y<55))
        { 
        vreme=1;
            LATBbits.LATB5=1;
    Delay_ms(vreme);
    LATBbits.LATB5=0;
    perioda=perioda-vreme;
    Delay_ms(perioda);
    
        }// korak pwm=5%
}

void Taster10()
{
    if ((17<X)&&(X<44)&& (15<Y)&&(Y<25))
    {vreme=2;
    LATBbits.LATB5=1;
    Delay_ms(vreme);
    LATBbits.LATB5=0;
    perioda=perioda-vreme;
    Delay_ms(perioda);
      }
        //LcdSetDot(X,64-Y);// korak pwm=10%
}
	
void __attribute__((__interrupt__)) _ADCInterrupt(void) 
{
							
	
	sirovi0=ADCBUF0;//0
	sirovi1=ADCBUF1;//1

	temp0=sirovi0;
	temp1=sirovi1;

    IFS0bits.ADIF = 0;
} 

void Write_GLCD(unsigned int data)
{
unsigned char temp;

temp=data/1000;
Glcd_PutChar(temp+'0');
data=data-temp*1000;
temp=data/100;
Glcd_PutChar(temp+'0');
data=data-temp*100;
temp=data/10;
Glcd_PutChar(temp+'0');
data=data-temp*10;
Glcd_PutChar(data+'0');
}


unsigned int broj1,broj2,r;


/*void __attribute__((__interrupt__)) _T2Interrupt(void)
{

   	TMR2 =0;
    IFS0bits.T2IF = 0;
}*/

int perioda=20;

void main(void)
{
     Init_T2();
    ADPCFGbits.PCFG5=1;//defini?emo da pin B4 nije analogni vec digitalni

    TRISBbits.TRISB5 = 0;
	ConfigureLCDPins();
	ConfigureTSPins();

	GLCD_LcdInit();

	GLCD_ClrScr();
    initUART1();
	
	ADCinit();
	ConfigureADCPins();
	ADCON1bits.ADON=1;



	while(1)
	{
        
        LATBbits.LATB5=0;
        Delay_ms(2000);
        LATBbits.LATB5=1;
        
	Touch_Panel ();
    
		GLCD_DisplayPicture(tasteri_bmp);
        
	    GoToXY(0,6);
        GLCD_Printf ("X=");
        GoToXY(9,6);
        Write_GLCD(X);
	        
		GoToXY(0,7);
        GLCD_Printf ("Y=");
        GoToXY(9,7);
        /*5% x od 17 do 44
y od 47 do 55

10% x od 17 do 44
y od 15 do 25
         
 strelice gore x od 88 do 100
y od 47 do 55

strelica dole
x od 88 do 100 
y od 15 do 30        
         
         
         */
        
        
        Write_GLCD(Y);
    
        
        
        Taster5();
        Taster10();
        
 if ((88<X)&&(X<100)&& (47<Y)&&(Y<55))
 { 
     vreme=vreme+2;
 }
        //LcdSetDot(X,64-Y);// povecavanje pwm za dati korak
        
 if ((88<X)&&(X<100)&& (15<Y)&&(Y<30))
      vreme=vreme-2;
        ///LcdSetDot(X,64-Y);// smanjivanje pwm za dati korak
        
        
        
        
        
        
        if ((59<X)&&(X<111)&& (6<Y)&&(Y<15))
            {  
             
          	  GLCD_ClrScr();
            }
     
	}//while

}//main

			
		
												
